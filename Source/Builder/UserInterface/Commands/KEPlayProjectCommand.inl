#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
PlayProjectCommand::PlayProjectCommand(MainApplicationPtr TheMainApp) : Inherited(),
_TheMainApp(TheMainApp)
{
}

inline
PlayProjectCommand::PlayProjectCommand(const PlayProjectCommand& source) : Inherited(source),
_TheMainApp(source._TheMainApp)
{
}

inline 
void PlayProjectCommand::operator =(const PlayProjectCommand& source)
{
	Inherited::operator=(source);
	_TheMainApp = source._TheMainApp;
}

inline 
const CommandType &PlayProjectCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
