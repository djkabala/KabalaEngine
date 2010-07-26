/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include "Application/KEMainApplication.h"

#ifdef WIN32
#include <Windowsx.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    //Get the Command line
    int argc(0);
    LPWSTR* argv_w = CommandLineToArgvW(GetCommandLineW (), &argc);
    
    // Convert the wide string array into an ANSI array (input is ASCII-7)

    LPSTR * argv = new LPSTR [argc];

    for (int i = 0; i < argc; ++i)
    {
        size_t qStrLen = wcslen(argv_w[i]), qConverted = 0;

        argv[i] = new CHAR [qStrLen+1];

        wcstombs_s(&qConverted,argv[i],qStrLen+1, argv_w [i],qStrLen+1);
    }

	//Run the Main Application
    int ReturnValue = OSG::MainApplication::the()->run(argc, argv);

    //Free the memory
    LocalFree(argv);

    return ReturnValue;

}
#else
int main(int argc, char **argv)
{
	//Run the Main Application
    return OSG::MainApplication::the()->run(argc, argv);
}
#endif

