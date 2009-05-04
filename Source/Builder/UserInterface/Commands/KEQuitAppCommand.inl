#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
QuitAppCommand::QuitAppCommand(void) : Inherited()
{
}

inline
QuitAppCommand::QuitAppCommand(const QuitAppCommand& source) : Inherited(source)
{
}

inline 
const CommandType &QuitAppCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
