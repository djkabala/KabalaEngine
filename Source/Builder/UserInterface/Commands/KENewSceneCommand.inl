#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
NewSceneCommand::NewSceneCommand(void) : Inherited()
{
}

inline
NewSceneCommand::NewSceneCommand(const NewSceneCommand& source) : Inherited(source)
{
}

inline 
void NewSceneCommand::operator =(const NewSceneCommand& source)
{
	Inherited::operator=(source);
}

inline 
const CommandType &NewSceneCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
