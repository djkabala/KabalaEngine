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

#ifndef _KEAPPLICATIONBUILDER_H_
#define _KEAPPLICATIONBUILDER_H_
#ifdef __sgi
#pragma once
#endif

#include "KEApplicationBuilderBase.h"
#include <OpenSG/OSGCommandManager.h>
#include <OpenSG/OSGUndoManager.h>
#include <OpenSG/OSGPathFields.h>
#include <OpenSG/OSGUIDrawingSurfaceFields.h>
#include <OpenSG/OSGUIForegroundFields.h>
#include <OpenSG/OSGViewportFields.h>
#include <OpenSG/OSGDialogWindowFields.h>
#include "Builder/UserInterface/KEInterfaceFields.h"
#include "Builder/UserInterface/MainWindow/KEMainWindowFields.h"
#include <OpenSG/OSGListSelectionModel.h>
#include "Project/Scene/KESceneFields.h"

#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
#include "InputLogging/KEInputLog.h"
#endif

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationBuilder class. See \ref
           PageKabalaEngineApplicationBuilder for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ApplicationBuilder : public ApplicationBuilderBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ApplicationBuilderBase Inherited;
    typedef ApplicationBuilder     Self;

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
	virtual void attachApplication(void);
	virtual void dettachApplication(void);
	virtual void attachInterface(void);
	virtual void detachInterface(void);
	virtual void start(void);
	virtual void stop(void);
    virtual void reset(void);

	UndoManagerPtr getUndoManager(void) const;
	CommandManagerPtr getCommandManager(void) const;
	Interface* getInterface(void) const;

	bool saveProject(void);
	bool saveProjectAs(void);


    UIDrawingSurface* getDrawingSurface(void) const;
    UIForeground* getForeground(void) const;
    Viewport* getViewport(void) const;
    
    void selectScene(Scene* const TheScene);
    Scene* getSelectedScene(void) const;

    //SelectionChanged
    boost::signals2::connection connectSelectionChanged(const ListSelectionModel::SelectionChangedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    boost::signals2::connection connectSelectionChanged(const ListSelectionModel::SelectionChangedEventType::group_type &group,
                                                       const ListSelectionModel::SelectionChangedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    void   disconnectSelectionChanged       (const ListSelectionModel::SelectionChangedEventType::group_type &group);
    void   disconnectAllSlotsSelectionChanged(void);
    bool   isEmptySelectionChanged          (void) const;
    UInt32 numSlotsSelectionChanged         (void) const;
    

    AttachmentContainer* findContainer(const std::string& RefName);

    void openEditor(void);

    void openEditor(FieldContainer* FCToEdit);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ApplicationBuilderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationBuilder(void);
    ApplicationBuilder(const ApplicationBuilder &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationBuilder(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ApplicationBuilder *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

	bool saveProject(const BoostPath& ProjectFile);
    void createInterface(void);
    void createGenericEditor(void);

    void updateWindowTitle(void);
    bool isProjectSaveUpToDate(void) const;

    void createBuilderDrawingSurface(void);


    
	UndoManagerPtr _UndoManager;
	CommandManagerPtr _CommandManager;
    UIDrawingSurfaceRecPtr _BuilderDrawingSurface;
    UIForegroundRecPtr _BuilderForeground;
    ViewportRecPtr _BuilderViewport;

    MainWindowRecPtr _MainWindow;

    DialogWindowRecPtr _GenericEditorDialog;

#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
    InputLogPtr _InputLogger;
#endif
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ApplicationBuilderBase;
    friend class Interface;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ApplicationBuilder &source);
};

typedef ApplicationBuilder *ApplicationBuilderP;

OSG_END_NAMESPACE

#include "KEApplicationBuilderBase.inl"
#include "KEApplicationBuilder.inl"

#endif /* _KEAPPLICATIONBUILDER_H_ */
