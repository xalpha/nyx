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

protected:
    // input mesh
    std::vector<Tf> m_vertices;
    std::vector<Ti> m_indices;
    std::vector<Tf> m_normals;
    size_t m_vertex_count;
    size_t m_index_count;
    size_t m_face_count;

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
    m_face_count = int(m_indices.size()) / 3;
    m_vertex_count = int( m_vertices.size() / Dim );
    m_index_count = int( m_indices.size() / Dim );

    // init stuff
    for(int j=0; j<Dim; j++)
        m_min[j] = m_max[j] = m_vertices[j];

    // look for min and max
    for( int i=0; i<m_vertex_count; i++ )
        for(int j=0; j<Dim; j++)
        {
            m_min[j] = std::min( m_vertices[i*Dim+j], m_min[j] );
            m_max[j] = std::max( m_vertices[i*Dim+j], m_max[j] );
        }

    // save results
    for(int j=0; j<Dim; j++)
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

        while(std::getline(file, buffer))
        {
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
        }
    }
    else
        throw std::runtime_error("nyx::mesh::load_obj: could not open \"" + path + "\".");
}



}// namespace nyx
