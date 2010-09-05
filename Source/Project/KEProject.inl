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

inline
void Project::handleUpdate(UpdateEventDetails* const details)
{
    if(!_BlockInput && details->getElapsedTime() < 1.0)
    {
        produceUpdate(details);
    }
}

inline
void Project::handleMouseClicked(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseClicked(details);
    }
}

inline
void Project::handleMouseEntered(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseEntered(details);
    }
}

inline
void Project::handleMouseExited(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseExited(details);
    }
}

inline
void Project::handleMousePressed(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMousePressed(details);
    }
}

inline
void Project::handleMouseReleased(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseReleased(details);
    }
}

inline
void Project::handleMouseMoved(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseMoved(details);
    }
}

inline
void Project::handleMouseDragged(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseDragged(details);
    }
}

inline
void Project::handleMouseWheelMoved(MouseWheelEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseWheelMoved(details);
    }
}


inline
void Project::handleKeyPressed(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyPressed(details);
    }
}

inline
void Project::handleKeyReleased(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyReleased(details);
    }
}

inline
void Project::handleKeyTyped(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyTyped(details);
    }
}

inline
void Project::handleWindowOpened(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowOpened(details);
    }
}

inline
void Project::handleWindowClosing(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowClosing(details);
    }
}

inline
void Project::handleWindowClosed(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowClosed(details);
    }
}

inline
void Project::handleWindowIconified(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowIconified(details);
    }
}

inline
void Project::handleWindowDeiconified(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowDeiconified(details);
    }
}

inline
void Project::handleWindowActivated(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowActivated(details);
    }
}

inline
void Project::handleWindowDeactivated(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowDeactivated(details);
    }
}

inline
void Project::handleWindowEntered(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowEntered(details);
    }
}

inline
void Project::handleWindowExited(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowExited(details);
    }
}

OSG_END_NAMESPACE
