#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
PasteCommand::PasteCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_HierarchyPanel(HierarchyPanel),
_currentAction(0),
_nodeInCutClipboard(NullFC),
_clonedNodeInCopyClipboard(NullFC),
_SelectedNode(NullFC)
{
}

inline
PasteCommand::PasteCommand(const PasteCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_HierarchyPanel = source._HierarchyPanel;
	_currentAction = source._currentAction;
	_nodeInCutClipboard = source._nodeInCutClipboard;
	_clonedNodeInCopyClipboard = source._clonedNodeInCopyClipboard;
	_SelectedNode = source._SelectedNode;

}

inline 
const CommandType &PasteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
