#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
QuitAppCommand::QuitAppCommand(MainApplicationPtr TheMainApp) : Inherited(),
_TheMainApp(TheMainApp)
{
}

inline
QuitAppCommand::QuitAppCommand(const QuitAppCommand& source) : Inherited(source),
_TheMainApp(source._TheMainApp)
{
}

inline 
void QuitAppCommand::operator =(const QuitAppCommand& source)
{
	Inherited::operator=(source);
	_TheMainApp = source._TheMainApp;
}

inline 
const CommandType &QuitAppCommand::getClassType(void)
{
	return _Type;
}

KE_END_NAMESPACE
