#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ShowHideCommand::ShowHideCommand(NodePtr SelectedNode,ApplicationPlayerPtr ApplicationPlayer) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_SelectedNode(SelectedNode)
{
}

inline
ShowHideCommand::ShowHideCommand(const ShowHideCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_SelectedNode = source._SelectedNode;
}

inline 
const CommandType &ShowHideCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
