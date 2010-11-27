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

#ifndef _KEBACKGROUNDEDITOR_H_
#define _KEBACKGROUNDEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KEBackgroundEditorBase.h"
#include <OpenSG/OSGComboBoxFields.h>
#include <OpenSG/OSGTextureSelectChunkFields.h>
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>
#include <OpenSG/OSGColorFieldEditorFields.h>
#include <OpenSG/OSGBackgroundFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief BackgroundEditor class. See \ref
           PageKabalaEngineBackgroundEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING BackgroundEditor : public BackgroundEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef BackgroundEditorBase Inherited;
    typedef BackgroundEditor     Self;

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

    void attachBackground(Background* const TheBackground);
    void dettachBackground(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in BackgroundEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BackgroundEditor(void);
    BackgroundEditor(const BackgroundEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BackgroundEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    ComboBoxRecPtr                    _TypeComboBox;
    TextureSelectChunkRecPtr               _TypeTextureSelect;
    GenericNameAttachmentEditorRecPtr _NameEditor;

    ColorFieldEditorRecPtr            _SolidColorEditor;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BackgroundEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BackgroundEditor &source);
};

typedef BackgroundEditor *BackgroundEditorP;

OSG_END_NAMESPACE

#include "KEBackgroundEditorBase.inl"
#include "KEBackgroundEditor.inl"

#endif /* _KEBACKGROUNDEDITOR_H_ */
