////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of nyx, a lightweight C++ template library for OpenGL    //
//                                                                            //
// Copyright (C) 2010, 2011 Alexandru Duliu                                   //
//                                                                            //
// nyx is free software; you can redistribute it and/or                       //
// modify it under the terms of the GNU Lesser General Public                 //
// License as published by the Free Software Foundation; either               //
// version 3 of the License, or (at your option) any later version.           //
//                                                                            //
// nyx is distributed in the hope that it will be useful, but WITHOUT ANY     //
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS  //
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the //
// GNU General Public License for more details.                               //
//                                                                            //
// You should have received a copy of the GNU Lesser General Public           //
// License along with nyx. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                            //
///////////////////////////////////////////////////////////////////////////////


#pragma once

#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <sstream>
#include <vector>


namespace nyx
{


template<typename Tf, typename Ti, int Dim>
class mesh
{
public:
	// constructors
    mesh();
    virtual ~mesh();

    void load( const std::string& path );

    // data getters
    const std::vector<Tf>& vertices() const { return m_vertices; }
    const std::vector<Tf>& normals() const { return m_normals; }
    const std::vector<Ti>& indices() const { return m_indices; }
    size_t vertices_per_face() const { return m_vertices_per_face; }
    size_t face_count() const { return m_indices.size() / m_vertices_per_face; }


    // simple operations
    void operator +( Tf val );
    void operator +( Tf val[Dim] );
    void operator *( Tf val );
    void operator *( Tf val[Dim] );

protected:
	// mesh processing
    void analyze();

    // loading
    void load_obj( const std::string& path );
    void load_stl( const std::string& path );

    // simple helpers
    void replace_substr( std::string& str, const std::string& src, const std::string& dst );

protected:
    // input mesh
    std::vector<Tf> m_vertices;
    std::vector<Ti> m_indices;
    std::vector<Tf> m_normals;
    size_t m_vertex_count;
    size_t m_index_count;
    size_t m_vertices_per_face;

    // mesh properties
    Tf m_min[Dim];
    Tf m_max[Dim];
    Tf m_center[Dim];
    Tf m_size[Dim];
};


/////
// Implementation
///

template<typename Tf, typename Ti, int Dim>
inline mesh<Tf,Ti,Dim>::mesh()
{
}


template<typename Tf, typename Ti, int Dim>
inline mesh<Tf,Ti,Dim>::~mesh()
{
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::load( const std::string& path )
{
    // get the extension as lowercase
    size_t idx = path.find_last_of( '.' );
    std::string ext = path.substr( idx+1, path.size()-idx -1 );
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // load
    if( ext.compare( "obj" ) == 0 )
        load_obj(path);
    if( ext.compare( "stl" ) == 0 )
        load_stl(path);

    // let's see what we got
    analyze();
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::operator +( Tf val )
{
    for( Tf& v : m_vertices )
        v += val;
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::operator +( Tf val[Dim] )
{
    for( size_t i=0; i<m_vertex_count; i++ )
        for( size_t d=0; d<Dim; d++ )
            m_vertices[ i*Dim+d ] += val[d];
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::operator *( Tf val )
{
    for( Tf& v : m_vertices )
        v *= val;
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::operator *( Tf val[Dim] )
{
    for( size_t i=0; i<m_vertex_count; i++ )
        for( size_t d=0; d<Dim; d++ )
            m_vertices[ i*Dim+d ] *= val[d];
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::analyze()
{
    // init data about the matching surface
    m_vertex_count = int( m_vertices.size() / Dim );
    m_index_count = int( m_indices.size() / Dim );

    // init stuff
    for(int j=0; j<Dim && j<m_vertex_count; j++)
        m_min[j] = m_max[j] = m_vertices[j];

    // look for min and max
    for( int i=0; i<m_vertex_count; i++ )
        for(int j=0; j<Dim; j++)
        {
            m_min[j] = std::min( m_vertices[i*Dim+j], m_min[j] );
            m_max[j] = std::max( m_vertices[i*Dim+j], m_max[j] );
        }

    // save results
    for(int j=0; j<Dim && j<m_vertex_count; j++)
    {
        m_center[j] = (Tf)(0.5)*(m_max[j]+m_min[j]);
        m_size[j] = m_max[j] - m_min[j];
    }
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::load_obj( const std::string& path )
{
    // sanity check
    if( Dim != 3 )
        throw std::runtime_error("nyx::mesh::load_obj: Dim should have been 3.");

    // init stuff
    std::ifstream file;
    file.open(path.c_str());

    // if open continue
    if( file.is_open() )
    {
        // prepare stuff
        std::string buffer;
        m_vertices.clear();
        m_normals.clear();
        Tf vertex[3];
        Tf normal[3];
        m_vertices_per_face = 0;

        while(std::getline(file, buffer))
        {
            // make sure that all faces have the same number of vertices
            size_t fvc = std::count( buffer.begin(), buffer.end(), '/' ) / 2;
            if( m_vertices_per_face == 0 ) m_vertices_per_face = fvc;
            else if( fvc != m_vertices_per_face ) throw std::runtime_error( "nyx::mesh::load_obj: all face must have the same number of vertices." );

            // simple processing of the buffer to make it easyer to parse the face entries
            replace_substr( buffer, " /", " 0;" );
            replace_substr( buffer, "//", "/0/" );
            replace_substr( buffer, "/ ", "/0 " );
            std::replace( buffer.begin(), buffer.end(), '/', ' ');

            // dump it into a string buffer
            std::stringstream ss(buffer);
            std::string entry_type;
            ss >> entry_type;

            // read the entries
            if( entry_type.compare("v") == 0 )
            {
                ss >> vertex[0] >> vertex[1] >> vertex[2];
                m_vertices.push_back( vertex[0] ); m_vertices.push_back( vertex[1] ); m_vertices.push_back( vertex[2] );
            }
            else if( entry_type.compare("vn") == 0 )
            {
                ss >> normal[0] >> normal[1] >> normal[2];
                m_normals.push_back( normal[0] ); m_normals.push_back( normal[1] ); m_normals.push_back( normal[2] );
            }
            else if( entry_type.compare("f") == 0 )
            {
                // count the number of vertices per face (face vertex count)
                std::cout << fvc << ": ";
                std::vector<Ti> vi(fvc),ni(fvc),ti(fvc); // vertex,
                for( size_t i=0; i<fvc; i++ )
                    ss >> vi[i] >> ni[i] >> ti[i];
                if( std::find(vi.begin(), vi.end(), 0) == vi.end() ) m_indices.insert( m_indices.end(), vi.begin(), vi.end() );
                //if( std::find(ni.begin(), ni.end(), 0) == ni.end() ) m_normals.insert( m_normals.end(), ni.begin(), ni.end() ); // TODO: not yet interesting
            }
        }

        // now decrement all vertex indices, as in the standard, they begin at zero
        for( Ti& idx : m_indices ) idx--;
    }
    else
        throw std::runtime_error("nyx::mesh::load_obj: could not open \"" + path + "\".");
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::load_stl( const std::string& path )
{
    // init stuff
    std::ifstream file ( path.c_str(), std::ios::in | std::ios::binary);
    const size_t header_buffer_size = 80;
    char header_buffer[header_buffer_size];
    uint32_t triangle_count;
    m_vertices.clear();
    m_normals.clear();
    m_indices.clear();
    m_vertices_per_face = 3;

    // if open continue
    if( file.is_open() )
    {
        // read the header
        file.read (header_buffer, header_buffer_size);
        std::cout <<"header: " << header_buffer << std::endl;

        // get the triangle count
        file.read ( reinterpret_cast<char*>(&triangle_count), sizeof(uint32_t));
        std::cout <<"n Tri: " << triangle_count << std::endl;

        // awesome, no we can also plan ahead
        m_vertices.reserve( triangle_count*m_vertices_per_face );
        m_normals.reserve( triangle_count ); // TODO: well in order for this to work, I really need to support vertex and face normals

        //now read in all the triangles
        for(int t=0; t<triangle_count; t++)
        {
            // read a traingle
            const size_t triangle_buffer_size = 50;
            char triangle_buffer[triangle_buffer_size];
            file.read (triangle_buffer, triangle_buffer_size);

            // add the face normal
            float* n = reinterpret_cast<float*>( &triangle_buffer[0] );
            for( size_t i=0; i<3; i++ ) m_normals.push_back( n[i] );

            // add the vertices
            float* v = reinterpret_cast<float*>( &triangle_buffer[12] );
            for( size_t i=0; i<9; i++ ) m_vertices.push_back( v[i] );
        }
    }
    else
        throw std::runtime_error("nyx::mesh::load_stl: could not open \"" + path + "\".");
}


template<typename Tf, typename Ti, int Dim>
inline void mesh<Tf,Ti,Dim>::replace_substr( std::string& str, const std::string& src, const std::string& dst )
{
    if( !str.empty() )
    {
        for( size_t i = str.find( src, 0 ); i!=std::string::npos; i = str.find(src,i) )
        {
            str.erase( i, src.size() );
            str.insert( i, dst );
        }
    }
}


}// namespace nyx
