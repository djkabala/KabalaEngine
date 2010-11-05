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

#ifndef _KECAMERAEDITOR_H_
#define _KECAMERAEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KECameraEditorBase.h"
#include <OpenSG/OSGCameraFields.h>
#include <OpenSG/OSGComboBoxFields.h>
#include <OpenSG/OSGTextureSelectChunkFields.h>
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>
#include <OpenSG/OSGNumberSpinnerFieldEditorFields.h>
#include <OpenSG/OSGMatrixTransCompFieldEditorFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief CameraEditor class. See \ref
           PageKabalaEngineCameraEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING CameraEditor : public CameraEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CameraEditorBase Inherited;
    typedef CameraEditor     Self;

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

    void attachCamera(Camera* const TheCamera);
    void dettachCamera(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CameraEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CameraEditor(void);
    CameraEditor(const CameraEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CameraEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    ComboBoxRecPtr                    _TypeComboBox;
    TextureSelectChunkRecPtr          _TypeTextureSelect;
    GenericNameAttachmentEditorRecPtr _NameEditor;

    NumberSpinnerFieldEditorRecPtr    _FOVEditor;
    MatrixTransCompFieldEditorRecPtr  _BeaconTransformEditor;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CameraEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CameraEditor &source);
};

typedef CameraEditor *CameraEditorP;

OSG_END_NAMESPACE

#include "KECameraEditorBase.inl"
#include "KECameraEditor.inl"

#endif /* _KECAMERAEDITOR_H_ */
