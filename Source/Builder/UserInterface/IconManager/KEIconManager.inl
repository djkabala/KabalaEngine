#include "KEConfig.h"

KE_BEGIN_NAMESPACE

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

KE_END_NAMESPACE
