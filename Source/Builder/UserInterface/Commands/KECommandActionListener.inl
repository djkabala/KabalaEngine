#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CommandActionListener::CommandActionListener(CommandPtr TheCommand, CommandManagerPtr TheCommandManager) : Inherited(),
_TheCommand(TheCommand),
_TheCommandManager(TheCommandManager)
{
}

inline
CommandActionListener::CommandActionListener(const CommandActionListener& source) : Inherited(source),
_TheCommand(source._TheCommand),
_TheCommandManager(source._TheCommandManager)
{
}

inline 
void CommandActionListener::operator =(const CommandActionListener& source)
{
	Inherited::operator=(source);
	_TheCommand = source._TheCommand;
	_TheCommandManager = source._TheCommandManager;
}

OSG_END_NAMESPACE
