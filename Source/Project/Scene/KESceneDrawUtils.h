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

#ifndef _KE_SCENE_DRAW_UTILS_H_
#define _KE_SCENE_DRAW_UTILS_H_

#ifdef __sgi
#pragma once
#endif
 
#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include "KESceneFields.h"
#include <OpenSG/OSGTextureObjChunkFields.h>
#include <OpenSG/OSGWindowFields.h>
#include <OpenSG/OSGRenderAction.h>

OSG_USING_NAMESPACE

void KE_KABALAENGINE_DLLMAPPING renderSceneToTexture(Scene* const TheScene,
                                                     TextureObjChunk* const ColorTexture,
                                                     Window* const TheWindow,
                                                     RenderAction* TheRenderAction);

#endif /* _KE_SCENE_DRAW_UTILS_H_ */


