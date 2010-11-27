#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
OpenCreditsCommand::OpenCreditsCommand(void) : Inherited()
{
}

inline 
const CommandType &OpenCreditsCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
