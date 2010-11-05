#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CloseProjectCommand::CloseProjectCommand(void) : Inherited()
{
}

inline
CloseProjectCommand::CloseProjectCommand(const CloseProjectCommand& source) : Inherited(source)
{
}

inline 
void CloseProjectCommand::operator =(const CloseProjectCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &CloseProjectCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
