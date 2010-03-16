#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ShowHideCommand::ShowHideCommand(HierarchyPanelPtr HierarchyPanel,ApplicationPlayerPtr ApplicationPlayer) : Inherited(),
_HierarchyPanel(HierarchyPanel),
_ApplicationPlayer(ApplicationPlayer),
_SelectedNode(NullFC)
{
}

inline
ShowHideCommand::ShowHideCommand(const ShowHideCommand& source) : Inherited(source)
{
	_HierarchyPanel = source._HierarchyPanel;
	_ApplicationPlayer = source._ApplicationPlayer;
	_SelectedNode = source._SelectedNode;
}

inline 
const CommandType &ShowHideCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
