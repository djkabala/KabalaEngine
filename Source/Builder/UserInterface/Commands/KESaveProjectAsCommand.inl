#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
SaveProjectAsCommand::SaveProjectAsCommand(void) : Inherited()
{
}

inline
SaveProjectAsCommand::SaveProjectAsCommand(const SaveProjectAsCommand& source) : Inherited(source)
{
}

inline 
void SaveProjectAsCommand::operator =(const SaveProjectAsCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &SaveProjectAsCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
