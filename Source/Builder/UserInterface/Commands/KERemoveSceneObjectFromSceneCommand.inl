#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RemoveSceneObjectFromSceneCommand::RemoveSceneObjectFromSceneCommand(Scene* const RootScene,
                                      SceneObject* const RemoveSceneObject) : Inherited(),
        _RootScene(RootScene),
        _RemovedSceneObject(RemoveSceneObject)
{
}

inline 
const CommandType &RemoveSceneObjectFromSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
