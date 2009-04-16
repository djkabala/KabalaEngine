#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
IconSet::IconSet(void) : Inherited()
{
}

inline
IconSet::IconSet(const IconSet& source) : Inherited(source)
{
}

inline 
void IconSet::operator =(const IconSet& source)
{
	Inherited::operator=(source);
}

KE_END_NAMESPACE
