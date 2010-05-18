
#ifndef _KABALAENGINE_LUA_BINDINGS_H_
#define _KABALAENGINE_LUA_BINDINGS_H_

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <lua.hpp>
#include <OpenSG/OSGLuaManager.h>

OSG::LuaManager::OpenBoundLuaLibFunctor  KE_KABALAENGINE_DLLMAPPING getKabalaEngineLuaBindingsLibFunctor(void);

#endif
