

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include "Application/KEMainApplication.h"

//Bindings for the OSGToolbox libraries
#include <OpenSG/ToolboxLuaBindings/OSGToolbox_wrap.h>

//Kabala Engine Lua Bindings
#include "LuaBindings/KELuaBindings.h"

int main(int argc, char **argv)
{
    // OSG init
	osg::osgInit(argc,argv);

    //Toolbox Bindings
    osg::LuaManager::the()->openLuaBindingLib(getOSGToolboxLuaBindingsLibFunctor());
    
    //Kabala Engine Bindings
    osg::LuaManager::the()->openLuaBindingLib(getKabalaEngineLuaBindingsLibFunctor());

	//Start the Main Application
    osg::Int32 AppReturnValue = osg::MainApplication::the()->run(argc, argv);

	//OSG exit
    osg::osgExit();

    return AppReturnValue;
}
