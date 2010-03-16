#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CopyCommand::CopyCommand(ApplicationPlayerPtr ApplicationPlayer) : Inherited(),
_ApplicationPlayer(ApplicationPlayer)
{
}

inline
CopyCommand::CopyCommand(const CopyCommand& source) : Inherited(source)
{
	_ApplicationPlayer = source._ApplicationPlayer;
}

inline 
const CommandType &CopyCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
