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

#ifndef _KEFIELDCONTAINEREDITOR_TYPE_H_
#define _KEFIELDCONTAINEREDITOR_TYPE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGTypeBase.h>

#include <boost/function.hpp>
#include "KEFieldContainerEditor.h"

OSG_BEGIN_NAMESPACE

class KE_KABALAENGINELIB_DLLMAPPING FieldContainerEditorType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :
    typedef boost::function<FieldContainerEditorPtr (void)> FieldContainerEditorCreationMethod;
    typedef boost::function<void (void)> FieldContainerEditorInitMethod;

    UInt32 getFieldContainerEditorId(void) const;

    /*---------------------------------------------------------------------*/
    FieldContainerEditorType(const Char8  *szName, 
             const Char8  *szParentName,
             FieldContainerEditorCreationMethod CreationMethod,
             FieldContainerEditorInitMethod InitializeMethod,
             const UInt32  uiNameSpace = 0);
    
    /*---------------------------------------------------------------------*/
    virtual ~FieldContainerEditorType(void);

    /*---------------------------------------------------------------------*/
    bool operator ==(const FieldContainerEditorType &other) const;
    bool operator !=(const FieldContainerEditorType &other) const;

    FieldContainerEditorPtr create(void) const;
    void init(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:
    UInt32 _uiFieldContainerEditorTypeId;
    UInt32 _uiFieldContainerEditorTypeRootId;

    FieldContainerEditorCreationMethod _CreationMethod;
    FieldContainerEditorInitMethod _InitializeMethod;

    typedef TypeBase Inherited;

    FieldContainerEditorType(const FieldContainerEditorType &source);

    /*==========================  PRIVATE  ================================*/
  private:

    void operator =(const FieldContainerEditorType &source);
};

typedef FieldContainerEditorType *FieldContainerEditorTypeP;

OSG_END_NAMESPACE
        
#include "KEFieldContainerEditorType.inl"

#endif /* _KEFIELDCONTAINEREDITOR_TYPE_H_ */
