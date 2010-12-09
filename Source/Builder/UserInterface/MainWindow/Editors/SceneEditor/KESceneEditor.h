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

#ifndef _KESCENEEDITOR_H_
#define _KESCENEEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "KESceneEditorBase.h"
#include "Project/Scene/KESceneFields.h"
#include <OpenSG/OSGGenericNameAttachmentEditorFields.h>

#include <OpenSG/OSGVectorSpinnerFieldEditorFields.h>
#include <OpenSG/OSGBoolFieldEditorFields.h>
OSG_BEGIN_NAMESPACE

/*! \brief SceneEditor class. See \ref
           PageKabalaEngineSceneEditor for a description.
*/

class KE_KABALAENGINE_DLLMAPPING SceneEditor : public SceneEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SceneEditorBase Inherited;
    typedef SceneEditor     Self;

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

    void attachScene(Scene* const TheScene);
    void dettachScene(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SceneEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SceneEditor(void);
    SceneEditor(const SceneEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SceneEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    GenericNameAttachmentEditorRecPtr _NameEditor;

    BoolFieldEditorRecPtr _PhysicsEnabledEditor;
    VectorSpinnerFieldEditorRecPtr _GravityEditor;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SceneEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SceneEditor &source);
};

typedef SceneEditor *SceneEditorP;

OSG_END_NAMESPACE

#include "KESceneEditorBase.inl"
#include "KESceneEditor.inl"

#endif /* _KESCENEEDITOR_H_ */
