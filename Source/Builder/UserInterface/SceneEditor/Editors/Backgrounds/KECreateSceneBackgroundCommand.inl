#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CreateSceneBackgroundCommand::CreateSceneBackgroundCommand(SceneBackgroundsComboBoxModelPtr TheModel,FieldContainerType* FCType) : Inherited(),
_TheModel(TheModel),
_FCType(FCType)
{
}

inline
CreateSceneBackgroundCommand::CreateSceneBackgroundCommand(const CreateSceneBackgroundCommand& source) : Inherited(source),
_TheModel(source._TheModel),
_FCType(source._FCType)
{
}

inline 
const CommandType &CreateSceneBackgroundCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
