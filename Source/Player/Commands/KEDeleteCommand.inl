#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
DeleteCommand::DeleteCommand(ApplicationPlayerPtr ApplicationPlayer,
                             HierarchyPanelPtr HierarchyPanel,
                             NodePtr DeleteNode) : Inherited(),
    _ApplicationPlayer(ApplicationPlayer),
    _HierarchyPanel(HierarchyPanel),
    _DeletedNode(DeleteNode),
    _Parent(NullFC)
{
    addRefCP(_DeletedNode);
}

inline
DeleteCommand::DeleteCommand(const DeleteCommand& source) : Inherited(source),
    _ApplicationPlayer(source._ApplicationPlayer),
    _HierarchyPanel(source._HierarchyPanel),
    _DeletedNode(source._DeletedNode),
    _Parent(NullFC)

{
    addRefCP(_DeletedNode);
}

inline 
const CommandType &DeleteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
