/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
MainApplication::MainWindowListener::MainWindowListener(MainApplication* TheMainApplication) :
        _MainApplication(TheMainApplication)
{
}
        

inline
ApplicationSettingsRefPtr &MainApplication::getSettings(void)
{
    return _Settings;
}

inline
const ApplicationSettingsRefPtr &MainApplication::getSettings(void) const
{
    return _Settings;
}

inline
BoostPath  &MainApplication::getSettingsLoadFile(void)
{
    return _SettingsPath;
}

inline
const BoostPath  &MainApplication::getSettingsLoadFile(void) const
{
    return _SettingsPath;
}

inline
WindowEventProducerRefPtr &MainApplication::getMainWindow(void)
{
    return _MainWindow;
}

inline
const WindowEventProducerRefPtr &MainApplication::getMainWindow(void) const
{
    return _MainWindow;
}

inline
ProjectRefPtr &MainApplication::getProject(void)
{
    return _Project;
}

inline
const ProjectRefPtr &MainApplication::getProject(void) const
{
    return _Project;
}

inline
ApplicationModeRefPtr &MainApplication::getBuilderMode(void)
{
    return _BuilderMode;
}

inline
const ApplicationModeRefPtr  &MainApplication::getBuilderMode(void) const
{
    return _BuilderMode;
}

inline
ApplicationModeRefPtr &MainApplication::getPlayerMode(void)
{
    return _PlayerMode;
}

inline
const ApplicationModeRefPtr &MainApplication::getPlayerMode(void) const
{
    return _PlayerMode;
}

inline
ApplicationModeRefPtr &MainApplication::getStartScreenMode(void)
{
    return _StartScreenMode;
}

inline
const ApplicationModeRefPtr &MainApplication::getStartScreenMode(void) const
{
    return _StartScreenMode;
}

inline
ApplicationModeRefPtr &MainApplication::getCurrentMode(void)
{
    return _CurrentMode;
}

inline
const ApplicationModeRefPtr &MainApplication::getCurrentMode(void) const
{
    return _CurrentMode;
}

OSG_END_NAMESPACE

