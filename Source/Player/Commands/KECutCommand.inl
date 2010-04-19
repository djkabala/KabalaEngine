#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CutCommand::CutCommand(ApplicationPlayerPtr ApplicationPlayer,
                       SceneGraphTreeModelPtr SceneGraphTreeModel,
                       NodePtr CutNode) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_SceneGraphTreeModel(SceneGraphTreeModel),
_CutNode(CutNode),
_Parent(NullFC)
{
}

inline
CutCommand::CutCommand(const CutCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_SceneGraphTreeModel = source._SceneGraphTreeModel;
    _CutNode = source._CutNode;
}

inline 
const CommandType &CutCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
