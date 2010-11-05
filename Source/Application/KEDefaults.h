/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _KEDEFAULTS_H_
#define _KEDEFAULTS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEConfig.h"

#include "Project/KEProjectFields.h"
#include "Project/Scene/KESceneFields.h"
#include <OpenSG/OSGViewportFields.h>

OSG_BEGIN_NAMESPACE
    
SceneTransitPtr KE_KABALAENGINE_DLLMAPPING createDefaultScene(void);

ProjectTransitPtr KE_KABALAENGINE_DLLMAPPING createDefaultProject(void);

ViewportTransitPtr KE_KABALAENGINE_DLLMAPPING createDefaultLoadingViewport(void);

OSG_END_NAMESPACE

#include "KEDefaults.inl"


#endif /* _KEDEFAULTS_H_ */
