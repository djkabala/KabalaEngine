#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CommandActionListenerForPlayer::CommandActionListenerForPlayer(CommandPtr TheCommand, CommandManagerPtr TheCommandManager) : Inherited(),
_TheCommand(TheCommand),
_TheCommandManager(TheCommandManager)
{
}

inline
CommandActionListenerForPlayer::CommandActionListenerForPlayer(const CommandActionListenerForPlayer& source) : Inherited(source),
_TheCommand(source._TheCommand),
_TheCommandManager(source._TheCommandManager)
{
}

inline 
void CommandActionListenerForPlayer::operator =(const CommandActionListenerForPlayer& source)
{
	Inherited::operator=(source);
	_TheCommand = source._TheCommand;
	_TheCommandManager = source._TheCommandManager;
}

OSG_END_NAMESPACE
