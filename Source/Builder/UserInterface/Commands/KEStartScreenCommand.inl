#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

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

OSG_END_NAMESPACE
