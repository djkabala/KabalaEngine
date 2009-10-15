
#ifndef _KABALAENGINE_LUA_BINDINGS_H_
#define _KABALAENGINE_LUA_BINDINGS_H_

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <lua.hpp>
#include <OpenSG/Lua/OSGLuaManager.h>

osg::LuaManager::OpenBoundLuaLibFunctor  KE_KABALAENGINELIB_DLLMAPPING getKabalaEngineLuaBindingsLibFunctor(void);

#endif
