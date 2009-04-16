#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
UndoCommand::UndoCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
UndoCommand::UndoCommand(const UndoCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void UndoCommand::operator =(const UndoCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &UndoCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
