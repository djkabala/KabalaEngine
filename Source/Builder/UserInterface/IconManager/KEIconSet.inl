#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

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

OSG_END_NAMESPACE
