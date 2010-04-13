#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CutCommand::CutCommand(ApplicationPlayerPtr ApplicationPlayer,SceneGraphTreeModelPtr SceneGraphTreeModel) : Inherited(),
_ApplicationPlayer(ApplicationPlayer),
_SceneGraphTreeModel(SceneGraphTreeModel),
_NodeInClipboardBeforeCut(NullFC),
_NodeInClipboardAfterCut(NullFC),
_ParentOfCutNode(NullFC),
_CurrentAction(0)
{
}

inline
CutCommand::CutCommand(const CutCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
	_SceneGraphTreeModel = source._SceneGraphTreeModel;
	_NodeInClipboardBeforeCut= source._NodeInClipboardBeforeCut;
	_NodeInClipboardAfterCut= source._NodeInClipboardAfterCut;
	_ParentOfCutNode= source._ParentOfCutNode;
	_CurrentAction= source._CurrentAction;

}

inline 
const CommandType &CutCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
