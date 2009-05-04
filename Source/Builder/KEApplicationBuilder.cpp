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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include "KEConfig.h"

#include "KEApplicationBuilder.h"

#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTransform.h>

#include <OpenSG/Input/OSGWindowEventProducer.h>

#include <OpenSG/UserInterface/OSGUIForeground.h>

#include "Project/KEProject.h"
#include "Builder/UserInterface/KEBuilderInterface.h"
#include "Builder/UserInterface/IconManager/KEDefaultIconManager.h"
#include "Application/KEMainApplication.h"

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ApplicationBuilder
The ApplicationBuilder. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationBuilder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ApplicationBuilder::reset(void)
{
    
	_TheBuilderInterface->disconnectInterface(ApplicationBuilderPtr(this));

    beginEditCP(ApplicationBuilderPtr(this) , ApplicationBuilder::EditingProjectFieldMask);
		setEditingProject(MainApplication::the()->getProject());
	endEditCP(ApplicationBuilderPtr(this) , ApplicationBuilder::EditingProjectFieldMask);
    
	_TheBuilderInterface->connectInterface(ApplicationBuilderPtr(this));
}

bool ApplicationBuilder::saveProject(void)
{
	if(getEditingProject() != NullFC)
	{
		getEditingProject()->save();
		return true;
	}
	return false;
}

bool ApplicationBuilder::saveProjectAs(void)
{
	return saveProject(Path());
}

bool ApplicationBuilder::saveProject(const Path& ProjectFile)
{
	if(getEditingProject() != NullFC)
	{
		getEditingProject()->save(ProjectFile);
		return true;
	}
	return false;
}

void ApplicationBuilder::attachApplication(void)
{
	Inherited::attachApplication();

	beginEditCP(ApplicationBuilderPtr(this) , ApplicationBuilder::EditingProjectFieldMask);
		setEditingProject(MainApplication::the()->getProject());
	endEditCP(ApplicationBuilderPtr(this) , ApplicationBuilder::EditingProjectFieldMask);

	
	//Camera Beacon
	Matrix TransformMatrix;
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(TransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

    // Make Main Scene Node empty
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(CameraBeaconNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
	//Camera
	PerspectiveCameraPtr DefaultCamera = PerspectiveCamera::create();
	beginEditCP(DefaultCamera);
		DefaultCamera->setBeacon(CameraBeaconNode);
		DefaultCamera->setFov   (deg2rad(60.f));
		DefaultCamera->setNear  (0.1f);
		DefaultCamera->setFar   (10000.f);
	endEditCP(DefaultCamera);

	//Background
	SolidBackgroundPtr DefaultBackground = SolidBackground::create();
	beginEditCP(DefaultBackground, SolidBackground::ColorFieldMask);
		DefaultBackground->setColor(Color3f(0.0f,0.0f,0.0f));
	endEditCP(DefaultBackground, SolidBackground::ColorFieldMask);

	//Icon Manager
	_IconManager = DefaultIconManager::create();
	
	//User Interface
	ForegroundPtr UserInterfaceForeground = createInterface();
    beginEditCP(_TheBuilderInterface->getDrawingSurface(), UIDrawingSurface::EventProducerFieldMask);
        _TheBuilderInterface->getDrawingSurface()->setEventProducer(MainApplication::the()->getMainWindowEventProducer());
    endEditCP(_TheBuilderInterface->getDrawingSurface(), UIDrawingSurface::EventProducerFieldMask);

	//Viewport
	if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC && MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().size() == 0)
	{
		ViewportPtr DefaultViewport = Viewport::create();
		beginEditCP(DefaultViewport);
			DefaultViewport->setCamera                  (DefaultCamera);
			DefaultViewport->setRoot                    (DefaultRootNode);
			DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
			DefaultViewport->setBackground              (DefaultBackground);
			DefaultViewport->getForegrounds().push_back    (UserInterfaceForeground);
		endEditCP(DefaultViewport);

		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(DefaultViewport);
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}
}

void ApplicationBuilder::dettachApplication(void)
{
    beginEditCP(_TheBuilderInterface->getDrawingSurface(), UIDrawingSurface::EventProducerFieldMask);
        _TheBuilderInterface->getDrawingSurface()->setEventProducer(NullFC);
    endEditCP(_TheBuilderInterface->getDrawingSurface(), UIDrawingSurface::EventProducerFieldMask);


	if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC)
	{
		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(0);
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}

	Inherited::dettachApplication();
}

ForegroundPtr ApplicationBuilder::createInterface(void)
{
	_TheBuilderInterface = BuilderInterface::create();
	_TheBuilderInterface->createInterface(ApplicationBuilderPtr(this));
	_TheBuilderInterface->connectInterface(ApplicationBuilderPtr(this));

	// Create the UI Foreground Object
    UIForegroundPtr StartScreenUIForeground = osg::UIForeground::create();

    beginEditCP(StartScreenUIForeground, UIForeground::DrawingSurfaceFieldMask);
        StartScreenUIForeground->setDrawingSurface(_TheBuilderInterface->getDrawingSurface());
    endEditCP(StartScreenUIForeground, UIForeground::DrawingSurfaceFieldMask);

	return StartScreenUIForeground;
}

void ApplicationBuilder::start(void)
{
}

void ApplicationBuilder::stop(void)
{
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationBuilder::ApplicationBuilder(void) :
    Inherited()
{
	_UndoManager = UndoManager::create();
	_CommandManager = CommandManager::create(_UndoManager);
}

ApplicationBuilder::ApplicationBuilder(const ApplicationBuilder &source) :
    Inherited(source),
		_IconManager(source._IconManager),
		_UndoManager(source._UndoManager),
		_CommandManager(source._CommandManager)
{
}

ApplicationBuilder::~ApplicationBuilder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationBuilder::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ApplicationBuilder::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ApplicationBuilder NI" << std::endl;
}

