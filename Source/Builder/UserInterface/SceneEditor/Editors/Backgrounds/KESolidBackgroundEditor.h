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

#ifndef _KESOLID_BACKGROUND_EDITOR_H_
#define _KESOLID_BACKGROUND_EDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGBaseTypes.h>

#include <boost/shared_ptr.hpp>
#include "Builder/UserInterface/Editors/KEFieldContainerEditor.h"
#include "Builder/UserInterface/Editors/KEFieldContainerEditorType.h"
#include "Builder/UserInterface/Editors/KEFieldColorSelectionModel.h"

#include <OpenSG/UserInterface/OSGColorChooser.h>
#include <OpenSG/UserInterface/OSGChangeListener.h>
#include "Builder/KEApplicationBuilder.h"

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class SolidBackgroundEditor;

typedef boost::shared_ptr<SolidBackgroundEditor> SolidBackgroundEditorPtr;

class KE_KABALAENGINELIB_DLLMAPPING SolidBackgroundEditor : public FieldContainerEditor
{
    /*=========================  PUBLIC  ===============================*/
  public:
    typedef FieldContainerEditor Inherited;
    
    virtual const FieldContainerEditorType &getType(void) const;
    
    static const FieldContainerEditorType &getClassType(void);

    virtual ~SolidBackgroundEditor(void);

    virtual ComponentPtr createInterface(void);
    virtual void attachTarget(void);
    virtual void detachTarget(void);
    
    static FieldContainerEditorPtr create(void);
    
    static void initMethod(void);
    
  protected:
    SolidBackgroundEditor(void);

    ColorChooserPtr _Chooser;
    FieldColorSelectionModel _ColorModel;
	

	class ColorChangeListener: public ChangeListener
	{
	  public:
		ColorChangeListener(SolidBackgroundEditorPtr TheSolidBackgroundEditor);

		virtual void stateChanged(const ChangeEvent& e);
	  protected :
		SolidBackgroundEditorPtr _SolidBackgroundEditor;
	};

	friend class ColorChangeListener;

	ColorChangeListener _ColorChangeListener;
    
  private:
     static FieldContainerEditorType _Type;
};


KE_END_NAMESPACE

#include "KESolidBackgroundEditor.inl"

#endif /* _KESOLID_BACKGROUND_EDITOR_H_ */
