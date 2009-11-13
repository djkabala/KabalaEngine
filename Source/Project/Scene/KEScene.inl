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

OSG_BEGIN_NAMESPACE

inline
void Scene::blockInput(bool block)
{
    _BlockInput = block;
}

inline
bool Scene::isInputBlocked(void) const
{
    return _BlockInput;
}

inline
bool Scene::isStarted(void) const
{
    return _IsStarted;
}

inline
Scene::SceneUpdateListener::SceneUpdateListener(ScenePtr TheScene) : _Scene(TheScene)
{
}

inline
void Scene::SceneUpdateListener::update(const UpdateEventPtr e)
{
    if(!_Scene->_BlockInput && e->getElapsedTime() < 1.0)
    {
        _Scene->_Producer.produceEvent(UpdateMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseClicked(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseClickedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseEntered(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseEnteredMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseExited(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseExitedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mousePressed(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MousePressedMethodId,e);
    }
}
inline
void Scene::SceneUpdateListener::mouseReleased(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseReleasedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseMoved(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseMovedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseDragged(const MouseEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseDraggedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::mouseWheelMoved(const MouseWheelEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(MouseWheelMovedMethodId,e);
    }
}


inline
void Scene::SceneUpdateListener::keyPressed(const KeyEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(KeyPressedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::keyReleased(const KeyEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(KeyReleasedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::keyTyped(const KeyEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(KeyTypedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowOpened(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowOpenedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowClosing(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowClosingMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowClosed(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowClosedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowIconified(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowIconifiedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowDeiconified(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowDeiconifiedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowActivated(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowActivatedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowDeactivated(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowDeactivatedMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowEntered(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowEnteredMethodId,e);
    }
}

inline
void Scene::SceneUpdateListener::windowExited(const WindowEventPtr e)
{
    if(!_Scene->_BlockInput)
    {
        _Scene->_Producer.produceEvent(WindowExitedMethodId,e);
    }
}

OSG_END_NAMESPACE

