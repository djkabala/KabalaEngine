#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
DeleteCommand::DeleteCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel) : Inherited(),
_NodeInCutClipboard(NullFC),
_ClonedNodeInCutClipboard(NullFC),
_ClonedNodeInCopyClipboard(NullFC),
_ApplicationPlayer(ApplicationPlayer),
_HierarchyPanel(HierarchyPanel),
_LastSelectedPathComponent(NullFC),
_LastSelectedPathComponentNode(NullFC),
_Parent(NullFC)
{
}

inline
DeleteCommand::DeleteCommand(const DeleteCommand& source) : Inherited(source)
{
	_NodeInCutClipboard = source._NodeInCutClipboard;
	_ClonedNodeInCutClipboard = source._ClonedNodeInCutClipboard;
	_ClonedNodeInCutClipboard = source._ClonedNodeInCopyClipboard;
	_ApplicationPlayer = source._ApplicationPlayer;
	_HierarchyPanel = source._HierarchyPanel;
	_LastSelectedPathComponent= source._LastSelectedPathComponent;
	_LastSelectedPathComponentNode = source._LastSelectedPathComponentNode;
	_Parent= source._Parent;
}

inline 
const CommandType &DeleteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
