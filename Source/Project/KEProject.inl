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
ScenePtr Project::getActiveScene(void) const
{
	return getInternalActiveScene();
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
    _Project->update(e);
    _Project->_Producer.produceEvent(UpdateMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseClicked(const MouseEventPtr e)
{
    _Project->_Producer.produceEvent(MouseClickedMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseEntered(const MouseEventPtr e)
{
    _Project->_Producer.produceEvent(MouseEnteredMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseExited(const MouseEventPtr e)
{
    _Project->_Producer.produceEvent(MouseExitedMethodId,e);
}

inline
void Project::ProjectUpdateListener::mousePressed(const MouseEventPtr e)
{
    _Project->mousePressed(e);
    _Project->_Producer.produceEvent(MousePressedMethodId,e);
}
inline
void Project::ProjectUpdateListener::mouseReleased(const MouseEventPtr e)
{
    _Project->mouseReleased(e);
    _Project->_Producer.produceEvent(MouseReleasedMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseMoved(const MouseEventPtr e)
{
    _Project->mouseMoved(e);
    _Project->_Producer.produceEvent(MouseMovedMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseDragged(const MouseEventPtr e)
{
    _Project->mouseDragged(e);
    _Project->_Producer.produceEvent(MouseDraggedMethodId,e);
}

inline
void Project::ProjectUpdateListener::mouseWheelMoved(const MouseWheelEventPtr e)
{
    _Project->_Producer.produceEvent(MouseWheelMovedMethodId,e);
}


inline
void Project::ProjectUpdateListener::keyPressed(const KeyEventPtr e)
{
    _Project->keyPressed(e);
    _Project->_Producer.produceEvent(KeyPressedMethodId,e);
}

inline
void Project::ProjectUpdateListener::keyReleased(const KeyEventPtr e)
{
    _Project->keyReleased(e);
    _Project->_Producer.produceEvent(KeyReleasedMethodId,e);
}

inline
void Project::ProjectUpdateListener::keyTyped(const KeyEventPtr e)
{
    _Project->_Producer.produceEvent(KeyTypedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowOpened(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowOpenedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowClosing(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowClosingMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowClosed(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowClosedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowIconified(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowIconifiedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowDeiconified(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowDeiconifiedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowActivated(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowActivatedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowDeactivated(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowDeactivatedMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowEntered(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowEnteredMethodId,e);
}

inline
void Project::ProjectUpdateListener::windowExited(const WindowEventPtr e)
{
    _Project->_Producer.produceEvent(WindowExitedMethodId,e);
}

OSG_END_NAMESPACE

