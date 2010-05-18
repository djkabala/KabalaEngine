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

OSG_BEGIN_NAMESPACE

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
ViewportRefPtr Project::getViewport(UInt32 index) const
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
SceneRefPtr Project::getActiveScene(void) const
{
	return getInternalActiveScene();
}

inline
SceneRefPtr Project::getLastActiveScene(void) const
{
	return _LastActiveScene;
}

inline
Project::ProjectUpdateListener::ProjectUpdateListener(ProjectRefPtr TheProject) : _Project(TheProject)
{
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
void Project::ProjectUpdateListener::update(const UpdateEventUnrecPtr e)
{
    if(e->getElapsedTime() < 1.0)
    {
        if(!_Project->_BlockInput)
        {
            _Project->_Producer.produceEvent(UpdateMethodId,e);
        }
    }
}

inline
void Project::ProjectUpdateListener::mouseClicked(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseClickedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseEntered(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseEnteredMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseExited(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseExitedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mousePressed(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MousePressedMethodId,e);
    }
}
inline
void Project::ProjectUpdateListener::mouseReleased(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseReleasedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseMoved(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseMovedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseDragged(const MouseEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseDraggedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseWheelMovedMethodId,e);
    }
}


inline
void Project::ProjectUpdateListener::keyPressed(const KeyEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyPressedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::keyReleased(const KeyEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyReleasedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::keyTyped(const KeyEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyTypedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowOpened(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowOpenedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowClosing(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowClosingMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowClosed(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowClosedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowIconified(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowIconifiedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowDeiconified(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowDeiconifiedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowActivated(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowActivatedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowDeactivated(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowDeactivatedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowEntered(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowEnteredMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowExited(const WindowEventUnrecPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowExitedMethodId,e);
    }
}

OSG_END_NAMESPACE
