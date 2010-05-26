#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
IconManager::IconManager(void) : Inherited()
{
}

inline
IconManager::IconManager(const IconManager& source) : Inherited(source)
{
}

inline 
void IconManager::operator =(const IconManager& source)
{
	Inherited::operator=(source);
}

OSG_END_NAMESPACE
