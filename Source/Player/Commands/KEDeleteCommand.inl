#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
DeleteCommand::DeleteCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel) : Inherited(),
_nodeInCutClipboard(NullFC),
_clonedNodeInCutClipboard(NullFC),
_clonedNodeInCopyClipboard(NullFC),
_ApplicationPlayer(ApplicationPlayer),
_HierarchyPanel(HierarchyPanel),
_LastSelectedPathComponent(NullFC),
_LastSelectedPathComponentNode(NullFC),
_parent(NullFC)
{
}

inline
DeleteCommand::DeleteCommand(const DeleteCommand& source) : Inherited(source)
{
	_nodeInCutClipboard = source._nodeInCutClipboard;
	_clonedNodeInCutClipboard = source._clonedNodeInCutClipboard;
	_clonedNodeInCutClipboard = source._clonedNodeInCopyClipboard;
	_ApplicationPlayer = source._ApplicationPlayer;
	_HierarchyPanel = source._HierarchyPanel;
	_LastSelectedPathComponent= source._LastSelectedPathComponent;
	_LastSelectedPathComponentNode = source._LastSelectedPathComponentNode;
	_parent= source._parent;
}

inline 
const CommandType &DeleteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
