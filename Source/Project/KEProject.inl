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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------
#include "Application/KEMainApplication.h"
#include <OpenSG/OSGWindowEventProducer.h>

OSG_BEGIN_NAMESPACE

inline
void Project::setActiveSceneOnEvent(Scene* const TheScene,
                                    ReflexiveContainer* EventProducer,
                                    UInt32 EventId)
{
    _TriggeringSceneChangeEventConnection.disconnect();
    _TriggeringSceneChangeEventConnection = EventProducer->connectEvent(EventId, boost::bind(&Project::handleTriggeringSceneChangeEvent, this, _1, TheScene));
}

inline
void Project::addViewport(const ViewportRefPtr& port)
{
    MainApplication::the()->getMainWindow()->addPort(port);
}

inline
void Project::insertViewport(const ViewportRefPtr& port, UInt32 index)
{
    MainApplication::the()->getMainWindow()->insertPort(index, port);
}

inline
void Project::removeViewport(const ViewportRefPtr& port)
{
    MainApplication::the()->getMainWindow()->subPortByObj(port);
}

inline
void Project::clearViewports(void)
{
    MainApplication::the()->getMainWindow()->clearPorts();
}

inline
UInt32 Project::numViewports(void) const
{
    return MainApplication::the()->getMainWindow()->getMFPort()->size();
}

inline
Viewport* Project::getViewport(UInt32 index) const
{
    return MainApplication::the()->getMainWindow()->getPort(index);
}


inline
void Project::blockInput(bool block)
{
    _BlockInput = block;
}

inline
bool Project::isInputBlocked(void) const
{
    return _BlockInput;
}

inline
Scene* Project::getActiveScene(void) const
{
	return getInternalActiveScene();
}

inline
Scene* Project::getLastActiveScene(void) const
{
	return _LastActiveScene;
}

inline
bool Project::getPauseActiveUpdates(void) const
{
    return _PauseActiveUpdates;
}

inline
void Project::pauseActiveUpdates(void)
{
    _PauseActiveUpdates = true;
}

inline
void Project::unpauseActiveUpdates(void)
{
    _PauseActiveUpdates = false;
}

inline
void Project::togglePauseActiveUpdates(void)
{
    _PauseActiveUpdates = !_PauseActiveUpdates;
}

OSG_END_NAMESPACE
