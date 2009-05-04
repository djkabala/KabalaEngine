#include "KEConfig.h"

KE_BEGIN_NAMESPACE

inline
DefaultIconManager::DefaultIconManager(void) : Inherited()
{
}

inline
DefaultIconManager::DefaultIconManager(const DefaultIconManager& source) : Inherited(source)
{
}

inline 
void DefaultIconManager::operator =(const DefaultIconManager& source)
{
	Inherited::operator=(source);
}

KE_END_NAMESPACE
