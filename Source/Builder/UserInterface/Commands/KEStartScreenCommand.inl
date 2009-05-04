#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
StartScreenCommand::StartScreenCommand(void) : Inherited()
{
}

inline
StartScreenCommand::StartScreenCommand(const StartScreenCommand& source) : Inherited(source)
{
}

inline 
const CommandType &StartScreenCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
