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


#ifndef _KEFIELDCONTAINEREDITOR_FACTORY_H_
#define _KEFIELDCONTAINEREDITOR_FACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGTypeFactory.h>
#include "KEFieldContainerEditor.h"
#include "KEFieldContainerEditorType.h"

OSG_BEGIN_NAMESPACE

class KE_KABALAENGINELIB_DLLMAPPING FieldContainerEditorFactory : public TypeFactory
{
    /*==========================  PUBLIC  =================================*/

  public :
    static FieldContainerEditorFactory *the(void);

    FieldContainerEditorPtr createEditor(const TypeBase * TheType);
    FieldContainerEditorPtr createEditor(const std::string& TypeName);
    FieldContainerEditorPtr createEditor(const UInt32 TypeID);

    
    FieldContainerEditorPtr createDefaultEditor(FieldContainerType* FCType);

    
    const FieldContainerEditorType* findEditor(const std::string& TypeName);
    const FieldContainerEditorType* findEditor(const UInt32 TypeID);
    virtual TypeBase* findType(UInt32 uiTypeId);

    void setDefaultEditor(FieldContainerType* FCType, FieldContainerEditorType* EditorType);

    void setDefaultGenericEditor(FieldContainerEditorType* EditorType);
    FieldContainerEditorType* getDefaultGenericEditor(void) const;

    
    void init(void);

    virtual UInt32 registerType(TypeBase *pType);

    /*=========================  PROTECTED  ===============================*/

  protected:
    typedef TypeFactory Inherited;
  
    FieldContainerEditorFactory(void);
    
    /*---------------------------------------------------------------------*/
    virtual ~FieldContainerEditorFactory(void);
    
    static FieldContainerEditorFactory   *_the;

    std::map<UInt32, UInt32> _DefaultEditorMap;

    UInt32 _DefaultGenericEditor;

    bool _IsInitialized;
    
    /*==========================  PRIVATE  ================================*/
  private:
    FieldContainerEditorFactory(const FieldContainerEditorFactory &source);
    void operator =(const FieldContainerEditorFactory &source);
};

typedef FieldContainerEditorFactory *FieldContainerEditorFactoryP;

OSG_END_NAMESPACE

#endif /* _KEFIELDCONTAINEREDITOR_FACTORY_H_ */
