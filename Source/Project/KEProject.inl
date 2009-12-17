/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

#include <OpenSG/OSGConfig.h>
#include "Application/KEMainApplication.h"

OSG_BEGIN_NAMESPACE


inline
void Project::addViewport(const ViewportPtr& port)
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(port);
}

inline
void Project::insertViewport(const ViewportPtr& port, UInt32 index)
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->insertPort(index, port);
}

inline
void Project::removeViewport(const ViewportPtr& port)
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(port);
}

inline
void Project::clearViewports(void)
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->clearPorts();
}

inline
UInt32 Project::numViewports(void) const
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().size();
}

inline
ViewportPtr Project::getViewport(UInt32 index) const
{
    MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort(index);
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
ScenePtr Project::getActiveScene(void) const
{
	return getInternalActiveScene();
}

inline
ScenePtr Project::getLastActiveScene(void) const
{
	return _LastActiveScene;
}

inline
Project::ProjectUpdateListener::ProjectUpdateListener(ProjectPtr TheProject) : _Project(TheProject)
{
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
void Project::ProjectUpdateListener::update(const UpdateEventPtr e)
{
    if(e->getElapsedTime() < 1.0)
    {
        _Project->update(e);
        if(!_Project->_BlockInput)
        {
            _Project->_Producer.produceEvent(UpdateMethodId,e);
        }
    }
}

inline
void Project::ProjectUpdateListener::mouseClicked(const MouseEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseClickedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseEntered(const MouseEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseEnteredMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseExited(const MouseEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseExitedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mousePressed(const MouseEventPtr e)
{
    _Project->mousePressed(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MousePressedMethodId,e);
    }
}
inline
void Project::ProjectUpdateListener::mouseReleased(const MouseEventPtr e)
{
    _Project->mouseReleased(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseReleasedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseMoved(const MouseEventPtr e)
{
    _Project->mouseMoved(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseMovedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseDragged(const MouseEventPtr e)
{
    _Project->mouseDragged(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseDraggedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::mouseWheelMoved(const MouseWheelEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(MouseWheelMovedMethodId,e);
    }
}


inline
void Project::ProjectUpdateListener::keyPressed(const KeyEventPtr e)
{
    _Project->keyPressed(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyPressedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::keyReleased(const KeyEventPtr e)
{
    _Project->keyReleased(e);
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyReleasedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::keyTyped(const KeyEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(KeyTypedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowOpened(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowOpenedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowClosing(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowClosingMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowClosed(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowClosedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowIconified(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowIconifiedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowDeiconified(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowDeiconifiedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowActivated(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowActivatedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowDeactivated(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowDeactivatedMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowEntered(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowEnteredMethodId,e);
    }
}

inline
void Project::ProjectUpdateListener::windowExited(const WindowEventPtr e)
{
    if(!_Project->_BlockInput)
    {
        _Project->_Producer.produceEvent(WindowExitedMethodId,e);
    }
}

OSG_END_NAMESPACE

