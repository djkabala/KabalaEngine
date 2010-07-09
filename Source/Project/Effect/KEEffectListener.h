/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Sound                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala, Robert Goetz              *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGEFFECTISTENER_H_
#define _OSGEFFECTISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "KEKabalaEngineDef.h"

#include "OSGEventListener.h"
#include "KEEffectEvent.h"

OSG_BEGIN_NAMESPACE

//const EffectEvent& e
class EffectEvent;
class KE_KABALAENGINE_DLLMAPPING EffectListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void effectBegan(const EffectEventUnrecPtr e) = 0;
   virtual void effectStopped(const EffectEventUnrecPtr e) = 0;
   virtual void effectPaused(const EffectEventUnrecPtr e) = 0;
   virtual void effectUnpaused(const EffectEventUnrecPtr e) = 0;
   virtual void effectFinished(const EffectEventUnrecPtr e) = 0;
};

typedef EffectListener* EffectListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGEFFECTISTENER_H_ */
