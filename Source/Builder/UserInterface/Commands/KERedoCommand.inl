#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
RedoCommand::RedoCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
RedoCommand::RedoCommand(const RedoCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void RedoCommand::operator =(const RedoCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &RedoCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
