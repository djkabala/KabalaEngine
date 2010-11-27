#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RemoveSceneCommand::RemoveSceneCommand(Scene* const SceneToRemove) : Inherited(),
_RemovedScene(SceneToRemove)
{
}

inline
RemoveSceneCommand::RemoveSceneCommand(const RemoveSceneCommand& source) : Inherited(source),
_RemovedScene(source._RemovedScene)
{
}

inline 
void RemoveSceneCommand::operator =(const RemoveSceneCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &RemoveSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
