#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RenameSceneBackgroundCommand::RenameSceneBackgroundCommand(SceneBackgroundsComboBoxModelPtr TheModel,UInt32 Index, std::string NewName) : Inherited(),
_TheModel(TheModel),
_Index(Index),
_NewName(NewName)
{
}

inline
RenameSceneBackgroundCommand::RenameSceneBackgroundCommand(const RenameSceneBackgroundCommand& source) : Inherited(source),
_TheModel(source._TheModel),
_Index(source._Index),
_NewName(source._NewName)
{
}

inline 
const CommandType &RenameSceneBackgroundCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
