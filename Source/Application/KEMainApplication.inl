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
ApplicationSettingsPtr &MainApplication::getSettings(void)
{
    return _Settings;
}

inline
const ApplicationSettingsPtr &MainApplication::getSettings(void) const
{
    return _Settings;
}

inline
Path  &MainApplication::getSettingsLoadFile(void)
{
    return _SettingsPath;
}

inline
const Path  &MainApplication::getSettingsLoadFile(void) const
{
    return _SettingsPath;
}

inline
WindowEventProducerPtr &MainApplication::getMainWindowEventProducer(void)
{
    return _MainWindowEventProducer;
}

inline
const WindowEventProducerPtr &MainApplication::getMainWindowEventProducer(void) const
{
    return _MainWindowEventProducer;
}

inline
ProjectPtr &MainApplication::getProject(void)
{
    return _Project;
}

inline
const ProjectPtr &MainApplication::getProject(void) const
{
    return _Project;
}

inline
ApplicationModePtr &MainApplication::getBuilderMode(void)
{
    return _BuilderMode;
}

inline
const ApplicationModePtr  &MainApplication::getBuilderMode(void) const
{
    return _BuilderMode;
}

inline
ApplicationModePtr &MainApplication::getPlayerMode(void)
{
    return _PlayerMode;
}

inline
const ApplicationModePtr &MainApplication::getPlayerMode(void) const
{
    return _PlayerMode;
}

inline
ApplicationModePtr &MainApplication::getStartScreenMode(void)
{
    return _StartScreenMode;
}

inline
const ApplicationModePtr &MainApplication::getStartScreenMode(void) const
{
    return _StartScreenMode;
}

inline
ApplicationModePtr &MainApplication::getCurrentMode(void)
{
    return _CurrentMode;
}

inline
const ApplicationModePtr &MainApplication::getCurrentMode(void) const
{
    return _CurrentMode;
}

OSG_END_NAMESPACE

