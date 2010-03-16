#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CutCommand::CutCommand(ApplicationPlayerPtr ApplicationPlayer,HierarchyPanelPtr HierarchyPanel) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_HierarchyPanel(HierarchyPanel),
_nodeInClipboardBeforeCut(NullFC),
_nodeInClipboardAfterCut(NullFC),
_parentOfCutNode(NullFC),
_currentAction(0)
{
}

inline
CutCommand::CutCommand(const CutCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_HierarchyPanel = source._HierarchyPanel;
	_nodeInClipboardBeforeCut= source._nodeInClipboardBeforeCut;
	_nodeInClipboardAfterCut= source._nodeInClipboardAfterCut;
	_parentOfCutNode= source._parentOfCutNode;
	_currentAction= source._currentAction;

}

inline 
const CommandType &CutCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
