/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _KESCENE3DNODESEDITORFIELDS_H_
#define _KESCENE3DNODESEDITORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGNodeCoreFieldDataType.h>
#include "KEKabalaEngineDef.h"

#include "KESceneComponentEditorFields.h"

OSG_BEGIN_NAMESPACE

class Scene3DNodesEditor;

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
//! Scene3DNodesEditorPtr

typedef FCPtr<SceneComponentEditorPtr, Scene3DNodesEditor> Scene3DNodesEditorPtr;

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKabalaEngineFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Scene3DNodesEditorPtr> : 
    public FieldTraitsRecurseMapper<Scene3DNodesEditorPtr, true>
{
    static DataType             _type;                       

    enum                        { StringConvertable = 0x00 };
    enum                        { bHasParent        = 0x01 };

    static DataType   &getType (void) { return _type;        }

    static const char *getSName(void) { return "SFScene3DNodesEditorPtr"; }
    static const char *getMName(void) { return "MFScene3DNodesEditorPtr"; }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<Scene3DNodesEditorPtr, true>
    \hideinhierarchy
 */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpKabalaEngineFieldSingle */

typedef SField<Scene3DNodesEditorPtr> SFScene3DNodesEditorPtr;
#endif

#ifndef KE_COMPILESCENE3DNODESEDITORINST
OSG_DLLEXPORT_DECL1(SField, Scene3DNodesEditorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS)
/*! \ingroup GrpKabalaEngineFieldMulti */

typedef MField<Scene3DNodesEditorPtr> MFScene3DNodesEditorPtr;
#endif

#ifndef KE_COMPILESCENE3DNODESEDITORINST
OSG_DLLEXPORT_DECL1(MField, Scene3DNodesEditorPtr, KE_KABALAENGINELIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#endif /* _KESCENE3DNODESEDITORFIELDS_H_ */