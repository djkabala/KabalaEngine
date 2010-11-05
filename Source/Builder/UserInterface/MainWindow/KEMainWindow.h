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

#ifndef _KEMAINWINDOW_H_
#define _KEMAINWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "KEMainWindowBase.h"
#include <OpenSG/OSGPathFields.h>
#include <OpenSG/OSGInternalWindowFields.h>
#include <OpenSG/OSGBackgroundFields.h>
#include <OpenSG/OSGForegroundFields.h>
#include <OpenSG/OSGLightFields.h>
#include <OpenSG/OSGCameraFields.h>
#include <OpenSG/OSGCardLayoutFields.h>
#include <OpenSG/OSGParticleSystemFields.h>
#include <OpenSG/OSGViewportFields.h>
#include <OpenSG/OSGInternalWindowFields.h>
#include <OpenSG/OSGLabelFields.h>
#include <OpenSG/OSGListSelectionEventDetailsFields.h>
#include "Project/Scene/KESceneFields.h"
#include "Project/SceneObject/KESceneObjectFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MainWindow class. See \ref
           PageKabalaEngineMainWindow for a description.
*/

class KE_KABALAENGINE_DLLMAPPING MainWindow : public MainWindowBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MainWindowBase Inherited;
    typedef MainWindow     Self;

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

    InternalWindow* getWindow(void) const;

    void hideEditor(void);
    void showBackgroundEditor(Background* const TheBackground);
    void showBasicEditor(Scene* const TheScene);
    void showForegroundEditor(Foreground* const TheForeground);
    void showLightEditor(Light* const TheLight);
    void showCameraEditor(Camera* const TheCamera);
    void showParticleSystemEditor(ParticleSystem* const TheParticleSystem);
    void showSceneObjectEditor(SceneObject* const TheSceneObject);
    void showViewportEditor(Viewport* const TheViewport);
    void showWindowEditor(InternalWindow* const TheWindow);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MainWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MainWindow(void);
    MainWindow(const MainWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MainWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void createMainWindow(void);
    void loadMainWindow(const BoostPath& WindowDefinitionFile);

    InternalWindowRecPtr _MainWindow;

    //Main Menu
    //Main Toolbar

    //SceneNavitationPanel
    //SceneComponentTree

    //Help Panel
    CardLayoutRecPtr _EditorCardLayout;
    LabelRecPtr _EditorSceneNameLabel;
    LabelRecPtr _EditorTypeLabel;

    void handleSelectedSceneChanged(ListSelectionEventDetails* const details);

    boost::signals2::connection _SceneSelectionConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MainWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MainWindow &source);
};

typedef MainWindow *MainWindowP;

OSG_END_NAMESPACE

#include "KEMainWindowBase.inl"
#include "KEMainWindow.inl"

#endif /* _KEMAINWINDOW_H_ */
