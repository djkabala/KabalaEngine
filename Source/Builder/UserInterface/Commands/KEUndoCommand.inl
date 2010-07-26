#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

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

OSG_END_NAMESPACE
