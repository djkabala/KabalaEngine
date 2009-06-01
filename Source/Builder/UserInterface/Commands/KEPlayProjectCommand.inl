#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

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

OSG_END_NAMESPACE
