#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
StartScreenCommand::StartScreenCommand(MainApplicationPtr TheMainApp) : Inherited(),
_TheMainApp(TheMainApp)
{
}

inline
StartScreenCommand::StartScreenCommand(const StartScreenCommand& source) : Inherited(source),
_TheMainApp(source._TheMainApp)
{
}

inline 
void StartScreenCommand::operator =(const StartScreenCommand& source)
{
	Inherited::operator=(source);
	_TheMainApp = source._TheMainApp;
}

inline 
const CommandType &StartScreenCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
