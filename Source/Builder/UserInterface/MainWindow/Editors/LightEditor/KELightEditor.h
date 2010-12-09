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

#ifndef _KELIGHTEDITOR_H_
#define _KELIGHTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KELightEditorBase.h"
#include <OpenSG/OSGLightFields.h>
#include <OpenSG/OSGComboBoxFields.h>
#include <OpenSG/OSGTextureSelectChunkFields.h>
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>
#include <OpenSG/OSGMatrixTransCompFieldEditorFields.h>
#include <OpenSG/OSGBoolFieldEditorFields.h>
#include <OpenSG/OSGColorFieldEditorFields.h>
#include <OpenSG/OSGComboBoxSelectionEventDetailsFields.h>
#include <OpenSG/OSGCommandManager.h>

OSG_BEGIN_NAMESPACE

/*! \brief LightEditor class. See \ref
           PageKabalaEngineLightEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING LightEditor : public LightEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LightEditorBase Inherited;
    typedef LightEditor     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual void createInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void destroyInterface(ApplicationBuilder* const TheApplicationBuilder);

	virtual void attachInterface(ApplicationBuilder* const TheApplicationBuilder);
	virtual void dettachInterface(ApplicationBuilder* const TheApplicationBuilder);

    virtual UInt32 getCardIndex(void) const;
    virtual std::string getEditorTypeText(void) const;

    void attachLight(Light* const TheLight);
    void dettachLight(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LightEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LightEditor(void);
    LightEditor(const LightEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LightEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void handleTypeComboSelectionChanged(ComboBoxSelectionEventDetails* const details);
    boost::signals2::connection _TypeComboSelectionChangedConnection;

    LightRecPtr _EditingLight;

    ComboBoxRecPtr                    _TypeComboBox;
    TextureSelectChunkRecPtr          _TypeTextureSelect;
    GenericNameAttachmentEditorRecPtr _NameEditor;
    BoolFieldEditorRecPtr             _EnabledEditor;
    MatrixTransCompFieldEditorRecPtr  _BeaconTransformEditor;
    
    ColorFieldEditorRecPtr            _AmbientColorEditor;
    ColorFieldEditorRecPtr            _DiffuseColorEditor;
    ColorFieldEditorRecPtr            _SpecularColorEditor;
    
    CommandManagerPtr _TheCommandManager;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LightEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LightEditor &source);
};

typedef LightEditor *LightEditorP;

OSG_END_NAMESPACE

#include "KELightEditorBase.inl"
#include "KELightEditor.inl"

#endif /* _KELIGHTEDITOR_H_ */
