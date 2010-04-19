#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
CopyCommand::CopyCommand(ApplicationPlayerPtr ApplicationPlayer,
                         NodePtr CopyNode) : Inherited(),
    _ApplicationPlayer(ApplicationPlayer),
    _CopyNode(CopyNode)
{
}

inline
CopyCommand::CopyCommand(const CopyCommand& source) : Inherited(source),
    _ApplicationPlayer(source._ApplicationPlayer),
    _CopyNode(source._CopyNode)
{
}

inline 
const CommandType &CopyCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
