#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RedoCommand::RedoCommand(UndoManagerPtr TheUndoManager) : Inherited(),
_UndoManager(TheUndoManager)
{
}

inline
RedoCommand::RedoCommand(const RedoCommand& source) : Inherited(source),
_UndoManager(source._UndoManager)
{
}

inline 
void RedoCommand::operator =(const RedoCommand& source)
{
	Inherited::operator=(source);
	_UndoManager = source._UndoManager;
}

inline 
const CommandType &RedoCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
