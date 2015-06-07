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

#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <test_mesh.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;

    // try to load the mesh
    test_mesh* m;
    try
    {
        if( argc > 1 )
            m = new test_mesh( std::string(argv[1]) );
        else
            throw std::runtime_error("main: specify 3d model!");
    }
    catch( std::exception& e )
    {
        std::cerr << e.what() << std::endl;
        std::cerr.flush();
        return 1;
    }

    w.setCentralWidget(m);
    w.show();

    return a.exec();
}
