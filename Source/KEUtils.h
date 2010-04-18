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

#ifndef _KE_UTILS_H_
#define _KE_UTILS_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"
#include <OpenSG/OSGAttachmentContainer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGNode.h>

#include <OpenSG/OSGConfig.h>

#include <string>

OSG_USING_NAMESPACE

bool KE_KABALAENGINELIB_DLLMAPPING attachName (AttachmentContainerPtr AttContainer);

void KE_KABALAENGINELIB_DLLMAPPING recurseSetTravMask(NodePtr RootNode, 
                                                      UInt32 TravMask);

void KE_KABALAENGINELIB_DLLMAPPING recurseSetTravMasRecord(NodePtr RootNode, 
                                                           UInt32 TravMask,
                                                           std::vector<std::pair<NodePtr, UInt32> >& NodesChanged);

#endif /* _KE_DEFINES_H_ */


