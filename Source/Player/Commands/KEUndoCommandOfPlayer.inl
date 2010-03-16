#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
UndoCommandOfPlayer::UndoCommandOfPlayer(ApplicationPlayerPtr  ApplicationPlayer) : Inherited(),
_ApplicationPlayer(ApplicationPlayer)
{
}

inline
UndoCommandOfPlayer::UndoCommandOfPlayer(const UndoCommandOfPlayer& source) : Inherited(source),
_ApplicationPlayer(source._ApplicationPlayer)
{
}

inline 
void UndoCommandOfPlayer::operator =(const UndoCommandOfPlayer& source)
{
	Inherited::operator=(source);
	_ApplicationPlayer = source._ApplicationPlayer;
}

inline 
const CommandType &UndoCommandOfPlayer::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
