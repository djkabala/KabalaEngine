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

OSG_BEGIN_NAMESPACE

inline
Project* Scene::getParentProject(void) const
{
    return dynamic_cast<Project*>(_sfParentProject.getValue());
}

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
void Scene::handleUpdate(UpdateEventDetails* const details)
{
    if(!_BlockInput && details->getElapsedTime() < 1.0)
    {
        produceUpdate(details);
    }
}

inline
void Scene::handleMouseClicked(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseClicked(details);
    }
}

inline
void Scene::handleMouseEntered(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseEntered(details);
    }
}

inline
void Scene::handleMouseExited(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseExited(details);
    }
}

inline
void Scene::handleMousePressed(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMousePressed(details);
    }
}

inline
void Scene::handleMouseReleased(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseReleased(details);
    }
}

inline
void Scene::handleMouseMoved(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseMoved(details);
    }
}

inline
void Scene::handleMouseDragged(MouseEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseDragged(details);
    }
}

inline
void Scene::handleMouseWheelMoved(MouseWheelEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceMouseWheelMoved(details);
    }
}


inline
void Scene::handleKeyPressed(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyPressed(details);
    }
}

inline
void Scene::handleKeyReleased(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyReleased(details);
    }
}

inline
void Scene::handleKeyTyped(KeyEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceKeyTyped(details);
    }
}

inline
void Scene::handleWindowOpened(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowOpened(details);
    }
}

inline
void Scene::handleWindowClosing(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowClosing(details);
    }
}

inline
void Scene::handleWindowClosed(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowClosed(details);
    }
}

inline
void Scene::handleWindowIconified(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowIconified(details);
    }
}

inline
void Scene::handleWindowDeiconified(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowDeiconified(details);
    }
}

inline
void Scene::handleWindowActivated(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowActivated(details);
    }
}

inline
void Scene::handleWindowDeactivated(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowDeactivated(details);
    }
}

inline
void Scene::handleWindowEntered(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowEntered(details);
    }
}

inline
void Scene::handleWindowExited(WindowEventDetails* const details)
{
    if(!_BlockInput)
    {
        produceWindowExited(details);
    }
}

OSG_END_NAMESPACE

