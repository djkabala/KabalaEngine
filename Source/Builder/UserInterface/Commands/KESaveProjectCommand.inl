#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
SaveProjectCommand::SaveProjectCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
SaveProjectCommand::SaveProjectCommand(const SaveProjectCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void SaveProjectCommand::operator =(const SaveProjectCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &SaveProjectCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
