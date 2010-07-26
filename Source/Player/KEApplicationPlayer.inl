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

OSG_BEGIN_NAMESPACE

inline
ApplicationPlayer::PlayerKeyListener::PlayerKeyListener(ApplicationPlayerRefPtr TheApplicationPlayer) :
        _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::BasicListener::BasicListener(ApplicationPlayerRefPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::BasicListener::~BasicListener()
{
}

inline
ApplicationPlayer::GotoSceneItemListener::GotoSceneItemListener(ApplicationPlayerRefPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::GotoSceneItemListener::~GotoSceneItemListener()
{
}

inline
ApplicationPlayer::ProjectListener::ProjectListener(ApplicationPlayerRefPtr TheApplicationPlayer) : _ApplicationPlayer(TheApplicationPlayer)
{
}

inline
ApplicationPlayer::ProjectListener::~ProjectListener()
{
}

inline
bool ApplicationPlayer::isDebugging(void) const
{
    return _IsDebugActive;
}

inline 
CommandManagerPtr ApplicationPlayer::getCommandManager(void)
{
	return _TheCommandManager;
}

inline
void ApplicationPlayer::setClonedNodeInCopyClipboard(NodeRefPtr node)
{
	_ClonedNodeInCopyClipboard = node;
}

inline
NodeRefPtr ApplicationPlayer::getClonedNodeInCopyClipboard(void)
{
	return _ClonedNodeInCopyClipboard;
}

inline 
UndoManagerPtr ApplicationPlayer::getUndoManager(void)
{
	return _TheUndoManager;
}

inline 
NodeRefPtr ApplicationPlayer::getHighlightNode(void)
{
	return _HighlightNode;
}

inline 
void ApplicationPlayer::setHighlightNode(NodeRefPtr selectedNode)
{
	_HighlightNode = selectedNode;
}

inline 
ViewportRefPtr ApplicationPlayer::getDebugViewport(void)
{
	return _DebugViewport;
}

inline 
void ApplicationPlayer::setDebugViewport(ViewportRefPtr viewport)
{
	_DebugViewport = viewport;
}

inline 
HelperPanelRefPtr ApplicationPlayer::getHelperPanel(void)
{
	return _HelperPanel;
}

inline 
void ApplicationPlayer::setHelperPanel(HelperPanelRefPtr helperPanel)
{
	_HelperPanel = helperPanel;
}

inline 
NodeRefPtr ApplicationPlayer::getSelectedNode(void)
{
	return _SelectedNode;
}

inline 
void ApplicationPlayer::setSelectedNode(NodeRefPtr selectedNode)
{
    if(_SelectedNode != selectedNode)
    {
        _SelectedNode = selectedNode;
        updateHighlightNode();
        updateWireframeNode();
    }
}

inline 
ContentPanelRefPtr ApplicationPlayer::getContentPanel(void)
{
	return _ContentPanel;
}

inline 
void ApplicationPlayer::setContentPanel(ContentPanelRefPtr contentPanel)
{
	_ContentPanel = contentPanel;
}

inline 
Navigator& ApplicationPlayer::getDebugSceneNavigator(void)
{
    return _DebugSceneNavigator;
}

OSG_END_NAMESPACE
