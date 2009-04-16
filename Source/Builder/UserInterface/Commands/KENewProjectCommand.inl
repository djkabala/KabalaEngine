#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
NewProjectCommand::NewProjectCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
NewProjectCommand::NewProjectCommand(const NewProjectCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void NewProjectCommand::operator =(const NewProjectCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &NewProjectCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
