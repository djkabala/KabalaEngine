#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
NewProjectCommand::NewProjectCommand(void) : Inherited()
{
}

inline
NewProjectCommand::NewProjectCommand(const NewProjectCommand& source) : Inherited(source)
{
}

inline 
void NewProjectCommand::operator =(const NewProjectCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &NewProjectCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
