#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
PasteCommand::PasteCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_HierarchyPanel(HierarchyPanel),
_CurrentAction(0),
_NodeInCutClipboard(NullFC),
_ClonedNodeInCopyClipboard(NullFC),
_SelectedNode(NullFC)
{
}

inline
PasteCommand::PasteCommand(const PasteCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_HierarchyPanel = source._HierarchyPanel;
	_CurrentAction = source._CurrentAction;
	_NodeInCutClipboard = source._NodeInCutClipboard;
	_ClonedNodeInCopyClipboard = source._ClonedNodeInCopyClipboard;
	_SelectedNode = source._SelectedNode;

}

inline 
const CommandType &PasteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
