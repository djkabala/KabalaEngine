#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ShowHideCommand::ShowHideCommand(NodePtr SelectedNode, bool Show,bool Recursive) : Inherited(),
_SelectedNode(SelectedNode),
_Show(Show),
_Recursive(Recursive)
{
}

inline
ShowHideCommand::ShowHideCommand(const ShowHideCommand& source) : Inherited(source),
_SelectedNode(source._SelectedNode),
_Show(source._Show),
_Recursive(source._Recursive)

{
}

inline 
const CommandType &ShowHideCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
