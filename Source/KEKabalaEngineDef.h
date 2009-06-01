#ifndef _KEKABALAENGINEDEF_H_
#define _KEKABALAENGINEDEF_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(KE_BUILD_DLL)
#   ifdef KE_COMPILEKABALAENGINELIB
#       define KE_KABALAENGINELIB_DLLMAPPING     __declspec(dllexport)
#       define KE_KABALAENGINELIB_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define KE_KABALAENGINELIB_DLLMAPPING     __declspec(dllimport)
#       define KE_KABALAENGINELIB_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define KE_KABALAENGINELIB_DLLMAPPING
#define KE_KABALAENGINELIB_DLLTMPLMAPPING
#endif

#endif /* _KEKABALAENGINEDEF_H_ */

