#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
CloseProjectCommand::CloseProjectCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
CloseProjectCommand::CloseProjectCommand(const CloseProjectCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void CloseProjectCommand::operator =(const CloseProjectCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &CloseProjectCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
