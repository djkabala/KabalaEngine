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

#ifndef _KEFIELDCONTAINEREDITOR_H_
#define _KEFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGBaseTypes.h>

#include <boost/shared_ptr.hpp>
#include <OpenSG/UserInterface/OSGComponentFields.h>

OSG_BEGIN_NAMESPACE

class FieldContainerEditorType;

class KE_KABALAENGINELIB_DLLMAPPING FieldContainerEditor
{
    /*=========================  PUBLIC  ===============================*/
  public:
    
    virtual const FieldContainerEditorType &getType(void) const = 0;

    virtual ~FieldContainerEditor(void);

    virtual ComponentPtr createInterface(void) = 0;
    virtual void attachTarget(void);
    virtual void detachTarget(void);
    virtual void setTarget(FieldContainerPtr Target);
    virtual void swapTarget(FieldContainerPtr Target);
    
  protected:
    FieldContainerEditor(void);
    FieldContainerPtr _Target;
    bool _isAttached;
};

typedef boost::shared_ptr<FieldContainerEditor> FieldContainerEditorPtr;

OSG_END_NAMESPACE

#include "KEFieldContainerEditor.inl"

#endif /* _KEFIELDCONTAINEREDITOR_H_ */
