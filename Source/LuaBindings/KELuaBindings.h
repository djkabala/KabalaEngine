
#ifndef _KABALAENGINE_LUA_BINDINGS_H_
#define _KABALAENGINE_LUA_BINDINGS_H_

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <lua.hpp>
#include <OpenSG/OSGLuaManager.h>
#include "Project/SceneObject/KEBehavior.h"

OSG::LuaManager::OpenBoundLuaLibFunctor  KE_KABALAENGINE_DLLMAPPING getKabalaEngineLuaBindingsLibFunctor(void);
void KE_KABALAENGINE_DLLMAPPING push_Behavior_on_lua(lua_State* L, OSG::BehaviorRefPtr value);

#endif
