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


KE_USING_NAMESPACE

#include "KEProject.h"
#include "KEUtils.h"
#include "Application/KEMainApplication.h"
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGOrthographicCamera.h>
#include "Project/Scene/KEScene.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Toolbox/OSGFCFileHandler.h>
#include "Application/KEMainApplication.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Project
The Project. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Project::initMethod (void)
{
}




ProjectPtr Project::load(const Path& ProjectFile)
{
	return create(ProjectFile);
}

ProjectPtr Project::create(const Path& ProjectFile)
{
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(ProjectFile);

	for(FCFileType::FCPtrStore::iterator Itor(NewContainers.begin()) ; Itor!= NewContainers.end() ; ++Itor)
	{
		if((*Itor)->getType() == Project::getClassType())
		{
			beginEditCP(Project::Ptr::dcast(*Itor), Project::FilePathFieldMask);
				Project::Ptr::dcast(*Itor)->setFilePath(ProjectFile);
			endEditCP(Project::Ptr::dcast(*Itor), Project::FilePathFieldMask);
			Project::Ptr::dcast(*Itor)->attachNames();
			return Project::Ptr::dcast(*Itor);
		}
	}
	return NullFC;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

WindowEventProducerPtr Project::getEventProducer(void) const
{
	return MainApplication::the()->getMainWindowEventProducer();
}

void Project::save(void)
{
	FCFileType::FCPtrStore Containers;
	Containers.insert(ProjectPtr(this));

	FCFileType::FCTypeVector IgnoreTypes;

	FCFileHandler::the()->write(Containers,getFilePath(),IgnoreTypes);
}

void Project::save(const Path& ProjectFile)
{
	beginEditCP(ProjectPtr(this), Project::FilePathFieldMask);
		setFilePath(ProjectFile);
	endEditCP(ProjectPtr(this), Project::FilePathFieldMask);
	
	save();
}

void Project::start(void)
{
	//If needed create a default Viewport
	if(getInternalActiveViewport() == NullFC)
	{
		beginEditCP(ProjectPtr(this), InternalActiveViewportFieldMask);
			setInternalActiveViewport(createDefaultViewport());
		endEditCP(ProjectPtr(this), InternalActiveViewportFieldMask);
	}

	//If I have an initial Scene then enter it
	if(getInitialScene() != NullFC)
	{
		setActiveScene(getInitialScene());
	}

	//Attach the viewport to the window
    if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC && 
       MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().size() == 0)
	{
		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(getInternalActiveViewport());
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}
}

void Project::stop(void)
{
	setActiveScene(NullFC);
	if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC && MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().size() == 0)
	{
		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(0);
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}
}

void Project::setActiveScene(ScenePtr TheScene)
{
	if(getInternalActiveScene() != TheScene)
	{
		if(getInternalActiveScene() != NullFC)
		{
			getInternalActiveScene()->exit();
		}
		beginEditCP(ProjectPtr(this), InternalActiveSceneFieldMask);
			setInternalActiveScene(TheScene);
		endEditCP(ProjectPtr(this), InternalActiveSceneFieldMask);
		if(getInternalActiveScene() != NullFC)
		{
			getInternalActiveScene()->enter();
		}
	}
}

ViewportPtr Project::createDefaultViewport(void) const
{
	ViewportPtr DefaultViewport = Viewport::create();
	beginEditCP(DefaultViewport);
		DefaultViewport->setCamera                  (NullFC);
		DefaultViewport->setRoot                    (NullFC);
		DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
		DefaultViewport->setBackground              (NullFC);
	endEditCP(DefaultViewport);

	return DefaultViewport;
}


void Project::setActiveBackground(BackgroundPtr TheBackground)
{
	beginEditCP(getInternalActiveViewport(), Viewport::BackgroundFieldMask);
		getInternalActiveViewport()->setBackground(TheBackground);
	endEditCP(getInternalActiveViewport(), Viewport::BackgroundFieldMask);
}

void Project::setActiveCamera(CameraPtr TheCamera)
{
	if(TheCamera->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
	{
		//Vec2f WindowSize(MainApplication::the()->getMainWindowEventProducer()->getSize());
		beginEditCP(TheCamera, PerspectiveCamera::AspectFieldMask);
			//PerspectiveCamera::Ptr::dcast(TheCamera)->setAspect(WindowSize.y()/WindowSize.x());
			PerspectiveCamera::Ptr::dcast(TheCamera)->setAspect(1.0);
		endEditCP(TheCamera, PerspectiveCamera::AspectFieldMask);
	}
	if(TheCamera->getType().isDerivedFrom(OrthographicCamera::getClassType()))
	{
		//Vec2f WindowSize(MainApplication::the()->getMainWindowEventProducer()->getSize());
		beginEditCP(TheCamera, OrthographicCamera::AspectFieldMask);
			//OrthographicCamera::Ptr::dcast(TheCamera)->setAspect(WindowSize.y()/WindowSize.x());
			OrthographicCamera::Ptr::dcast(TheCamera)->setAspect(1.0);
		endEditCP(TheCamera, OrthographicCamera::AspectFieldMask);
	}
	beginEditCP(getInternalActiveViewport(), Viewport::CameraFieldMask);
		getInternalActiveViewport()->setCamera(TheCamera);
	endEditCP(getInternalActiveViewport(), Viewport::CameraFieldMask);
}

void Project::setActiveNode(NodePtr TheNode)
{
	beginEditCP(getInternalActiveViewport(), Viewport::RootFieldMask);
		getInternalActiveViewport()->setRoot(TheNode);
	endEditCP(getInternalActiveViewport(), Viewport::RootFieldMask);
}

MFForegroundPtr &Project::getActiveForegrounds(void)
{
	return getInternalActiveViewport()->getForegrounds();
}

void Project::attachNames(void)
{
	//Backgrounds
	for(::osg::UInt32 i(0); i<getBackgrounds().size() ; ++i)
	{
		::ke::attachName(getBackgrounds(i));
	}

	//Foregrounds
	for(::osg::UInt32 i(0); i<getForegrounds().size() ; ++i)
	{
		attachName(getForegrounds(i));
	}

	//Cameras
	for(::osg::UInt32 i(0); i<getCameras().size() ; ++i)
	{
		attachName(getCameras(i));
	}

	//ModelNodes
	for(::osg::UInt32 i(0); i<getModelNodes().size() ; ++i)
	{
		attachName(getModelNodes(i));
	}

	//Scenes
	for(::osg::UInt32 i(0) ; i<getScenes().size() ; ++i)
	{
		getScenes(i)->attachNames();
	}

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Project::Project(void) :
    Inherited()
{
}

Project::Project(const Project &source) :
    Inherited(source)
{
}

Project::~Project(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Project::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & ScenesFieldMask))
	{
		for(::osg::UInt32 i(0) ; i<getScenes().size() ; ++i)
		{
			beginEditCP(getScenes()[i], Scene::InternalParentProjectFieldMask);
				getScenes()[i]->setInternalParentProject(ProjectPtr(this));
			endEditCP(getScenes()[i], Scene::InternalParentProjectFieldMask);
		}
	}
}

void Project::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Project NI" << std::endl;
}

