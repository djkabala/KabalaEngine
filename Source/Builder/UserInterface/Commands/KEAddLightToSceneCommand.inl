#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
AddLightToSceneCommand::AddLightToSceneCommand(const FieldContainerType& LightType, Scene* RootScene) : Inherited(),
        _RootScene(RootScene),
        _LightType(LightType)
{
}

inline 
const CommandType &AddLightToSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
