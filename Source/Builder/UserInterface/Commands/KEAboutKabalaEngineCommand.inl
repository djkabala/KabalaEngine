#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
AboutKabalaEngineCommand::AboutKabalaEngineCommand(void) : Inherited()
{
}

inline 
const CommandType &AboutKabalaEngineCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
