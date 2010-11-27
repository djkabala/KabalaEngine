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

#ifndef _KESCENEOBJECTEDITOR_H_
#define _KESCENEOBJECTEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneObjectEditorBase.h"
#include "Project/SceneObject/KESceneObjectFields.h"
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>
#include <OpenSG/OSGMatrixTransCompFieldEditorFields.h>
#include <OpenSG/OSGCheckboxButtonFields.h>
#include <OpenSG/OSGMenuButtonFields.h>

#include <OpenSG/OSGButtonSelectedEventDetailsFields.h>
#include <OpenSG/OSGNumberSpinnerFieldEditorFields.h>
#include <OpenSG/OSGBoolFieldEditorFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief SceneObjectEditor class. See \ref
           PageKabalaEngineSceneObjectEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneObjectEditor : public SceneObjectEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneObjectEditorBase Inherited;
    typedef SceneObjectEditor     Self;

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

    void attachSceneObject(SceneObject* const TheSceneObject);
    void dettachSceneObject(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneObjectEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneObjectEditor(void);
    SceneObjectEditor(const SceneObjectEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneObjectEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void handleCollidableCheckboxSelected(ButtonSelectedEventDetails* const details);
    void handleCollidableCheckboxDeselected(ButtonSelectedEventDetails* const details);

    boost::signals2::connection _CollidableCheckboxSelectedConnection;
    boost::signals2::connection _CollidableCheckboxDeselectedConnection;

    GenericNameAttachmentEditorRecPtr _NameEditor;

    MenuButtonRecPtr _ModelMenuButton;
    CheckboxButtonRecPtr   _EnabledCheckbox;
    MatrixTransCompFieldEditorRecPtr  _BeaconTransformEditor;

    NumberSpinnerFieldEditorRecPtr   _MassEditor;
    CheckboxButtonRecPtr _CollidableCheckbox;
    BoolFieldEditorRecPtr _GravityModeEditor;

    SceneObjectRecPtr _EditingSceneObject;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneObjectEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneObjectEditor &source);
};

typedef SceneObjectEditor *SceneObjectEditorP;

OSG_END_NAMESPACE

#include "KESceneObjectEditorBase.inl"
#include "KESceneObjectEditor.inl"

#endif /* _KESCENEOBJECTEDITOR_H_ */
