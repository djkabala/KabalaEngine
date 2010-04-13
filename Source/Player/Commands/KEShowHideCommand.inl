#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ShowHideCommand::ShowHideCommand(NodePtr _SelectedNode,MenuItemPtr ShowHideItem) : Inherited(),
_ShowHideItem(ShowHideItem),
_SelectedNode(_SelectedNode)
{
}

inline
ShowHideCommand::ShowHideCommand(const ShowHideCommand& source) : Inherited(source)
{
	_ShowHideItem = source._ShowHideItem;
	_SelectedNode = source._SelectedNode;
}

inline 
const CommandType &ShowHideCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
