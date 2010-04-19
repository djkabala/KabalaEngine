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
#include "KEApplicationPlayer.h"

OSG_BEGIN_NAMESPACE

inline
ApplicationPlayer::PlayerKeyListener::PlayerKeyListener(ApplicationPlayerPtr TheApplicationPlayer) :
        _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::BasicListener::BasicListener(ApplicationPlayerPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::BasicListener::~BasicListener()
{
}

inline
ApplicationPlayer::GotoSceneItemListener::GotoSceneItemListener(ApplicationPlayerPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::GotoSceneItemListener::~GotoSceneItemListener()
{
}

inline
ApplicationPlayer::ProjectListener::ProjectListener(ApplicationPlayerPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::ProjectListener::~ProjectListener()
{
}

inline 
CommandManagerPtr ApplicationPlayer::getCommandManager(void)
{
	return _TheCommandManager;
}

inline
void ApplicationPlayer::setClonedNodeInCopyClipboard(NodePtr node)
{
	_ClonedNodeInCopyClipboard = node;
}

inline
NodePtr ApplicationPlayer::getClonedNodeInCopyClipboard(void)
{
	return _ClonedNodeInCopyClipboard;
}

inline 
UndoManagerPtr ApplicationPlayer::getUndoManager(void)
{
	return _TheUndoManager;
}

inline 
NodePtr ApplicationPlayer::getHighlightNode(void)
{
	return _HighlightNode;
}

inline 
void ApplicationPlayer::setHighlightNode(NodePtr selectedNode)
{
	_HighlightNode = selectedNode;
}

inline 
ViewportPtr ApplicationPlayer::getDebugViewport(void)
{
	return _DebugViewport;
}

inline 
void ApplicationPlayer::setDebugViewport(ViewportPtr viewport)
{
	_DebugViewport = viewport;
}

inline 
HelperPanelPtr ApplicationPlayer::getHelperPanel(void)
{
	return _HelperPanel;
}

inline 
void ApplicationPlayer::setHelperPanel(HelperPanelPtr helperPanel)
{
	_HelperPanel = helperPanel;
}

inline 
NodePtr ApplicationPlayer::getSelectedNode(void)
{
	return _SelectedNode;
}

inline 
void ApplicationPlayer::setSelectedNode(NodePtr selectedNode)
{
    if(_SelectedNode != selectedNode)
    {
        _SelectedNode = selectedNode;
        updateHighlightNode();
        updateWireframeNode();
    }
}

inline 
ContentPanelPtr ApplicationPlayer::getContentPanel(void)
{
	return _ContentPanel;
}

inline 
void ApplicationPlayer::setContentPanel(ContentPanelPtr contentPanel)
{
	_ContentPanel = contentPanel;
}

inline 
Navigator& ApplicationPlayer::getDebugSceneNavigator(void)
{
    return _DebugSceneNavigator;
}

OSG_END_NAMESPACE

