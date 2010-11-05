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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "Project/KEProject.h"
#include "KEApplicationBuilder.h"

#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTransform.h>

#include <OpenSG/OSGWindowEventProducer.h>

#include <OpenSG/OSGGraphics2D.h>
#include <OpenSG/OSGUIForeground.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include <OpenSG/OSGContainerUtils.h>
#include <OpenSG/OSGDefaultListSelectionModel.h>

#include <OpenSG/OSGFieldContainerEditorDialog.h>
#include <OpenSG/OSGFCPtrFieldEditor.h>
#include <OpenSG/OSGFCPtrEditorRootedStore.h>
#include <OpenSG/OSGUIDrawUtils.h>

#include "Project/KEProject.h"
#include "Application/KEMainApplication.h"
#include "Builder/UserInterface/KEInterface.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"
#include "Builder/UserInterface/MainWindow/Editors/KEEditors.h"

//#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <boost/filesystem/convenience.hpp>
//#endif

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGApplicationBuilderBase.cpp file.
// To modify it, please change the .fcd file (OSGApplicationBuilder.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationBuilder::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

AttachmentContainer* ApplicationBuilder::findContainer(const std::string& RefName)
{
    return dynamic_pointer_cast<AttachmentContainer>(getFieldContainer(RefName.c_str()));
}

void ApplicationBuilder::reset(void)
{
	getMainWindow()->dettachInterface(this);

    setEditingProject(MainApplication::the()->getProject());
    
	getMainWindow()->attachInterface(this);
}

bool ApplicationBuilder::saveProject(void)
{
	if(getEditingProject() != NULL)
	{
		getEditingProject()->save();
		return true;
	}
	return false;
}

bool ApplicationBuilder::saveProjectAs(void)
{
	return saveProject(BoostPath());
}

bool ApplicationBuilder::saveProject(const BoostPath& ProjectFile)
{
	if(getEditingProject() != NULL)
	{
		getEditingProject()->save(ProjectFile);
		return true;
	}
	return false;
}

void ApplicationBuilder::updateWindowTitle(void)
{
    std::string MainWindowTitle("");
    MainWindowTitle += " - " + MainApplication::the()->getProject()->getMainWindowTitle();
    MainWindowTitle += " - " + MainApplication::the()->getProject()->getFilePath().string();
    if(isProjectSaveUpToDate())
    {
        MainWindowTitle += " (modified)";
    }
    MainApplication::the()->getMainWindow()->setTitle(MainWindowTitle);
}

bool ApplicationBuilder::isProjectSaveUpToDate(void) const
{
    //TODO: Implement
    return true;
}

void ApplicationBuilder::createBuilderDrawingSurface(void)
{
    MainWindowRecPtr TheMainWindow = MainWindow::create();
    setMainWindow(TheMainWindow);

    getMainWindow()->createInterface(this);

    Graphics2DRecPtr BuilderUIGraphics = Graphics2D::create();


    _BuilderDrawingSurface = UIDrawingSurface::create();
    _BuilderDrawingSurface->setGraphics(BuilderUIGraphics);

    _BuilderDrawingSurface->openWindow(getMainWindow()->getWindow());
}

void ApplicationBuilder::attachApplication(void)
{
	Inherited::attachApplication();

    createInterface();

    MainApplication::the()->getMainWindow()->subPortByObj(_BuilderViewport);
    MainApplication::the()->getMainWindow()->addPort(_BuilderViewport);

    attachInterface();

    //Update the window title
    updateWindowTitle();

    setEditingProject(MainApplication::the()->getProject());

//#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
//    _InputLogger = InputLog::create();
//    _InputLogger->setEventProducer(MainApplication::the()->getMainWindow());
//    
//     BoostPath InputLogDir = MainApplication::the()->getUserAppDataDir()
//                 / "World Builder";
//    try
//    {
//        boost::filesystem::create_directories(InputLogDir);
//    }
//    catch(std::exception& ex)
//    {
//        SWARNING << "Failed to create directory: " << InputLogDir 
//                 << ", error: " << ex.what() << std::endl;
//    }
//
//     BoostPath InputLogFilePath = InputLogDir
//                 / BoostPath(boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time()) + ".input.log");  //ISO date/time format
//    _InputLogger->setLogFile(InputLogFilePath);
//#endif
}

void ApplicationBuilder::dettachApplication(void)
{
    MainApplication::the()->getMainWindow()->subPortByObj(_BuilderViewport);

    detachInterface();

	Inherited::dettachApplication();
}

void ApplicationBuilder::createInterface(void)
{
    //Check if the interface is already created
    if(_BuilderViewport != NULL)
    {
        return;
    }

	//Camera Beacon
	Matrix TransformMatrix;
	TransformPtr CameraBeaconTransform = Transform::create();
    CameraBeaconTransform->setMatrix(TransformMatrix);

	NodePtr CameraBeaconNode = Node::create();
    CameraBeaconNode->setCore(CameraBeaconTransform);

    // Make Main Scene Node empty
    NodePtr DefaultRootNode = Node::create();
    DefaultRootNode->setCore(Group::create());
    DefaultRootNode->addChild(CameraBeaconNode);
	
	//Camera
	PerspectiveCameraRecPtr DefaultCamera = PerspectiveCamera::create();
	DefaultCamera->setBeacon(CameraBeaconNode);
	DefaultCamera->setFov   (deg2rad(60.f));
	DefaultCamera->setNear  (0.1f);
	DefaultCamera->setFar   (10000.f);

	//Background
	SolidBackgroundRecPtr DefaultBackground = SolidBackground::create();
    DefaultBackground->setColor(Color3f(0.0f,0.0f,0.0f));
	
    

    //Create the Drawing Surface
    createBuilderDrawingSurface();

	//User Interface
    _BuilderForeground = UIForeground::create();
    _BuilderForeground->setDrawingSurface(_BuilderDrawingSurface);

	//Viewport
	_BuilderViewport = Viewport::create();
	_BuilderViewport->setCamera     (DefaultCamera);
	_BuilderViewport->setRoot       (DefaultRootNode);
	_BuilderViewport->setSize       (0.0f,0.0f, 1.0f,1.0f);
	_BuilderViewport->setBackground (DefaultBackground);
	_BuilderViewport->addForeground (_BuilderForeground);

}

void ApplicationBuilder::start(void)
{
//#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
//    _InputLogger->start();
//#endif
}

void ApplicationBuilder::stop(void)
{
//#ifdef BUILD_WITH_WORLD_BUILDER_INPUT_LOGGING
//    _InputLogger->stop();
//#endif
}

void ApplicationBuilder::attachInterface(void)
{
    //Select the starting scene
    SceneUnrecPtr SelectScene(MainApplication::the()->getProject()->getActiveScene());
    if(SelectScene == NULL)
    {
        SelectScene = MainApplication::the()->getProject()->getInitialScene();
    }
    if(SelectScene == NULL)
    {
        SelectScene = MainApplication::the()->getProject()->getMFScenes()->front();
    }

    selectScene(SelectScene);

    _BuilderDrawingSurface->setEventProducer(MainApplication::the()->getMainWindow());

    getMainWindow()->attachInterface(this);
}

void ApplicationBuilder::detachInterface(void)
{
    _BuilderDrawingSurface->setEventProducer(NULL);

    getMainWindow()->dettachInterface(this);
}

void ApplicationBuilder::selectScene(Scene* const TheScene)
{
    //Get the index of the scene
    for(UInt32 i(0) ; i<MainApplication::the()->getProject()->getMFScenes()->size() ; ++i)
    {
        if(MainApplication::the()->getProject()->getScenes(i) == TheScene)
        {
            getSelectionModel()->setSelectionInterval(i,i);
        }
    }
}
    
Scene* ApplicationBuilder::getSelectedScene(void) const
{
    Int32 Index(getSelectionModel()->getMinSelectionIndex());
    if(Index >= 0 && Index < MainApplication::the()->getProject()->getMFScenes()->size() )
    {
        return MainApplication::the()->getProject()->getScenes(Index);
    }
    else
    {
        return NULL;
    }
}

void ApplicationBuilder::openEditor(FieldContainer* FCToEdit)
{
    if(_GenericEditorDialog == NULL)
    {
        createGenericEditor();
    }
    if(getFCEditedContainer(_GenericEditorDialog) != FCToEdit)
    {
        setFCEditedContainer(_GenericEditorDialog, FCToEdit);
        Pnt2f CenteredPosition = calculateAlignment(Pnt2f(0.0f,0.0f), _BuilderDrawingSurface->getSize(), _GenericEditorDialog->getPreferredSize(), 0.5f, 0.5f);
        _GenericEditorDialog->setPosition(CenteredPosition);
    }

    _GenericEditorDialog->setTitle(std::string("Edit ") + FCToEdit->getType().getCName());

    _BuilderDrawingSurface->openWindow(_GenericEditorDialog);
}

void ApplicationBuilder::openEditor(void)
{
    if(_GenericEditorDialog == NULL)
    {
        createGenericEditor();
    }

    if(getFCEditedContainer(_GenericEditorDialog) == NULL)
    {
        openEditor(MainApplication::the()->getProject());
    }
    else
    {
        _BuilderDrawingSurface->openWindow(_GenericEditorDialog);
    }
}

void ApplicationBuilder::createGenericEditor(void)
{
    _GenericEditorDialog = createDefaultFCTreeEditorDialog(MainApplication::the()->getProject(), _CommandManager);
    _GenericEditorDialog->setTitle(std::string("Edit ") + MainApplication::the()->getProject()->getType().getCName());
    _GenericEditorDialog->setAllwaysOnTop(true);
    _GenericEditorDialog->setModal(false);
    _GenericEditorDialog->setResizable(true);
    _GenericEditorDialog->setMaximizable(true);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void ApplicationBuilder::onCreate(const ApplicationBuilder *Id)
{
    Inherited::onCreate(Id);

    if(Id != NULL)
    {
        ListSelectionModelUnrecPtr Model = DefaultListSelectionModel::create();

        setSelectionModel(Model);
    }
}

void ApplicationBuilder::onDestroy()
{
}


/*----------------------- constructors & destructors ----------------------*/

ApplicationBuilder::ApplicationBuilder(void) :
    Inherited(),
    _GenericEditorDialog(NULL)
{
	_UndoManager = UndoManager::create();
	_CommandManager = CommandManager::create(_UndoManager);
}

ApplicationBuilder::ApplicationBuilder(const ApplicationBuilder &source) :
    Inherited(source),
    _GenericEditorDialog(NULL)
{
	_UndoManager = UndoManager::create();
	_CommandManager = CommandManager::create(_UndoManager);
}

ApplicationBuilder::~ApplicationBuilder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationBuilder::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ApplicationBuilder::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ApplicationBuilder NI" << std::endl;
}

OSG_END_NAMESPACE
