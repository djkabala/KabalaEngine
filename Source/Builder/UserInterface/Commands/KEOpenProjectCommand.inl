#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
OpenProjectCommand::OpenProjectCommand(void) : Inherited()
{
}

inline
OpenProjectCommand::OpenProjectCommand(const OpenProjectCommand& source) : Inherited(source)
{
}

inline 
void OpenProjectCommand::operator =(const OpenProjectCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &OpenProjectCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
