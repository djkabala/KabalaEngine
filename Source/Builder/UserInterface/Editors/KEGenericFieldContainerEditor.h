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

#ifndef _KEGENERIC_FIELD_CONTAINER_EDITOR_H_
#define _KEGENERIC_FIELD_CONTAINER_EDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include "KEFieldContainerEditor.h"
#include "KEFieldContainerEditorType.h"

#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/OSGField.h>

OSG_BEGIN_NAMESPACE

class KE_KABALAENGINELIB_DLLMAPPING GenericFieldContainerEditor : public FieldContainerEditor
{
    /*=========================  PUBLIC  ===============================*/
  public:
    typedef FieldContainerEditor Inherited;
    
    virtual const FieldContainerEditorType &getType(void) const;
    
    static const FieldContainerEditorType &getClassType(void);

    virtual ~GenericFieldContainerEditor(void);

    virtual ComponentPtr createInterface(void);
    virtual void attachTarget(void);
    virtual void detachTarget(void);

    static FieldContainerEditorPtr create(void);
    
    static void initMethod(void);
    
  protected:
    GenericFieldContainerEditor(void);
    
    static ComponentPtr createEditor(Field*  TheField);

    PanelPtr _MainPanel;
    
  private:
     static FieldContainerEditorType _Type;
};

typedef boost::shared_ptr<GenericFieldContainerEditor> GenericFieldContainerEditorPtr;

OSG_END_NAMESPACE

#include "KEGenericFieldContainerEditor.inl"

#endif /* _KEGENERIC_FIELD_CONTAINER_EDITOR_H_ */
