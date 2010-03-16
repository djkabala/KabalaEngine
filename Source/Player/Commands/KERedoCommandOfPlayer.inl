#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
RedoCommandOfPlayer::RedoCommandOfPlayer(ApplicationPlayerPtr  ApplicationPlayer) : Inherited(),
_ApplicationPlayer(ApplicationPlayer)
{
}

inline
RedoCommandOfPlayer::RedoCommandOfPlayer(const RedoCommandOfPlayer& source) : Inherited(source),
_ApplicationPlayer(source._ApplicationPlayer)
{
}

inline 
void RedoCommandOfPlayer::operator =(const RedoCommandOfPlayer& source)
{
	Inherited::operator=(source);
	_ApplicationPlayer = source._ApplicationPlayer;
}

inline 
const CommandType &RedoCommandOfPlayer::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
