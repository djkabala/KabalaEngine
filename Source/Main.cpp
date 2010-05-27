/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include "Application/KEMainApplication.h"

//Bindings for the OSGToolbox libraries
#include <OpenSG/OSGToolbox_wrap.h>

//Kabala Engine Lua Bindings
#include "LuaBindings/KELuaBindings.h"

int main(int argc, char **argv)
{
    //OSG::preloadSharedObject("OSGCluster");
    //OSG::preloadSharedObject("OSGContribBackgroundloader");
    //OSG::preloadSharedObject("OSGContribComputeBase");
    //OSG::preloadSharedObject("OSGContribGUI");
    //OSG::preloadSharedObject("OSGContribLuaToolbox");
    //OSG::preloadSharedObject("OSGContribParticleSystem");
    //OSG::preloadSharedObject("OSGContribPhysics");
    //OSG::preloadSharedObject("OSGContribPLY");
    //OSG::preloadSharedObject("OSGContribSound");
    //OSG::preloadSharedObject("OSGContribTrapezoidalShadowMaps");
    //OSG::preloadSharedObject("OSGContribUserInterface");
    //OSG::preloadSharedObject("OSGContribVideo");
    //OSG::preloadSharedObject("OSGDynamics");
    //OSG::preloadSharedObject("OSGEffectGroup");
    //OSG::preloadSharedObject("OSGFileIO");
    //OSG::preloadSharedObject("OSGGroup");
    //OSG::preloadSharedObject("OSGImageFileIO");
    //OSG::preloadSharedObject("OSGTBAnimation");
    // OSG init
	OSG::osgInit(argc,argv);

    //Toolbox Bindings
    OSG::LuaManager::the()->openLuaBindingLib(getOSGToolboxLuaBindingsLibFunctor());
    
    //Kabala Engine Bindings
    OSG::LuaManager::the()->openLuaBindingLib(getKabalaEngineLuaBindingsLibFunctor());

	//Start the Main Application
    OSG::Int32 AppReturnValue = OSG::MainApplication::the()->run(argc, argv);

	//OSG exit
    OSG::osgExit();

    return AppReturnValue;
}

