#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RemoveLightFromSceneCommand::RemoveLightFromSceneCommand(Scene* const RootScene,
                                                         Node* const  RemoveLightNode) : Inherited(),
        _RootScene(RootScene),
        _RemovedLightNode(RemoveLightNode)
{
}

inline 
const CommandType &RemoveLightFromSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
