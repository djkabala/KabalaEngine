#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
AddSceneObjectToSceneCommand::AddSceneObjectToSceneCommand(Scene* const RootScene) : Inherited(),
        _RootScene(RootScene)
{
}

inline 
const CommandType &AddSceneObjectToSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
