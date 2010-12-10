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

#ifndef _KE_UTILS_H_
#define _KE_UTILS_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"
#include <OpenSG/OSGAttachmentContainerFields.h>
#include <OpenSG/OSGCameraFields.h>
#include <OpenSG/OSGViewportFields.h>
#include <OpenSG/OSGNodeFields.h>

#include <string>

OSG_USING_NAMESPACE

bool KE_KABALAENGINE_DLLMAPPING attachName (AttachmentContainer* const AttContainer);

void KE_KABALAENGINE_DLLMAPPING recurseSetTravMask(Node* const RootNode, 
                                                      UInt32 TravMask);

void KE_KABALAENGINE_DLLMAPPING recurseSetTravMasRecord(Node* const RootNode, 
                                                        UInt32 TravMask,
                                                        std::vector<std::pair<NodeRefPtr, UInt32> >& NodesChanged);

void KE_KABALAENGINE_DLLMAPPING calcCameraShowAll(Camera* const LocalCamera,
                                                  Viewport* const LocalViewport,
                                                  const std::vector<Node*>& NodesToShow,
                                                  Matrix& ResultCameraBeacon);

#endif /* _KE_DEFINES_H_ */


