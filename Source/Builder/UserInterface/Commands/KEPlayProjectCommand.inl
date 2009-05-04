#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
PlayProjectCommand::PlayProjectCommand(void) : Inherited()
{
}

inline
PlayProjectCommand::PlayProjectCommand(const PlayProjectCommand& source) : Inherited(source)
{
}

inline 
const CommandType &PlayProjectCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
