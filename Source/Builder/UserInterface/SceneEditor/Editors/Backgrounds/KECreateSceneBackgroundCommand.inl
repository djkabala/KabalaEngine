#include "KEConfig.h"

KE_BEGIN_NAMESPACE

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

KE_END_NAMESPACE
