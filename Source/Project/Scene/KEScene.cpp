/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEScene.h"
#include "KEUtils.h"
#include "Project/KEProject.h"
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Scene
The Scene. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Scene::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Scene::enter(void)
{
	if(getRoot() == NullFC)
	{
		createDefaults();
		initDefaults();
	}


	//Set up Initial Model Nodes
	beginEditCP(getRoot(), Node::ChildrenFieldMask);
		for(::osg::UInt32 i(0) ; i<getInitialModelNodes().size() ; ++i)
		{
			getRoot()->addChild(getInitialModelNodes()[i]);
		}
	endEditCP(getRoot(), Node::ChildrenFieldMask);

	//Background
	getInternalParentProject()->setActiveBackground(getInitialBackground());

	//Camera
	getInternalParentProject()->setActiveCamera(getInitialCamera());
    
	//Root Node
	getInternalParentProject()->setActiveNode(getRoot());

	//Foregrounds
	beginEditCP(getInternalParentProject(), Project::InternalActiveForegroundsFieldMask);
		getInternalParentProject()->getActiveForegrounds().clear();
		for(::osg::UInt32 i(0) ; i<getInitialForegrounds().size() ; ++i)
		{
			getInternalParentProject()->getActiveForegrounds().push_back(getInitialForegrounds(i));
		}
	endEditCP(getInternalParentProject(), Project::InternalActiveForegroundsFieldMask);

	//Attach the User Interface Drawing Surfaces to the Window Event Producer
	for(::osg::UInt32 i(0) ; i<getUIDrawingSurfaces().size() ; ++i)
	{
		beginEditCP(getUIDrawingSurfaces(i), UIDrawingSurface::EventProducerFieldMask);
			getUIDrawingSurfaces(i)->setEventProducer(getInternalParentProject()->getEventProducer());
		endEditCP(getUIDrawingSurfaces(i), UIDrawingSurface::EventProducerFieldMask);
	}

	//Attach the initial animations
	for(::osg::UInt32 i(0) ; i<getInitialAnimations().size() ; ++i)
	{
        getInternalParentProject()->addActiveAnimation(getInitialAnimations(i));
    }

    //Attach the initial particle systems
	for(::osg::UInt32 i(0) ; i<getInitialParticleSystems().size() ; ++i)
	{
        getInternalParentProject()->addActiveParticleSystem(getInitialParticleSystems(i));
    }


    producerSceneEntered(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}

void Scene::start(void)
{
    producerSceneStarted(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}

void Scene::end(void)
{
    producerSceneEnded(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}

void Scene::reset(void)
{
    producerSceneReset(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}


void Scene::exit(void)
{
	//Dettach the initial animations
	for(::osg::UInt32 i(0) ; i<getInitialAnimations().size() ; ++i)
	{
        //getInitialAnimations(i)->stop();
        getInternalParentProject()->removeActiveAnimation(getInitialAnimations(i));
    }

    //Dettach the initial particle systems
	for(::osg::UInt32 i(0) ; i<getInitialParticleSystems().size() ; ++i)
	{
        getInternalParentProject()->removeActiveParticleSystem(getInitialParticleSystems(i));
    }

    producerSceneExited(SceneEvent::create(ScenePtr(this), getTimeStamp()));
}

void Scene::createDefaults(void)
{
	if(getDefaultCameraBeaconCore() == NullFC)
	{
		TransformPtr TheDefaultCameraBeaconCore = Transform::create();

		beginEditCP(ScenePtr(this), Scene::DefaultCameraBeaconCoreFieldMask);
			setDefaultCameraBeaconCore(TheDefaultCameraBeaconCore);
		endEditCP(ScenePtr(this), Scene::DefaultCameraBeaconCoreFieldMask);
	}

	if(getDefaultCameraBeacon() == NULL)
	{
		NodePtr TheDefaultCameraBeacon = Node::create();

		beginEditCP(ScenePtr(this), Scene::DefaultCameraBeaconFieldMask);
			setDefaultCameraBeacon(TheDefaultCameraBeacon);
		endEditCP(ScenePtr(this), Scene::DefaultCameraBeaconFieldMask);
	}

	if(getRootCore() == NullFC)
	{
		TransformPtr TheRootCore = Transform::create();

		beginEditCP(ScenePtr(this), Scene::RootCoreFieldMask);
			setRootCore(TheRootCore);
		endEditCP(ScenePtr(this), Scene::RootCoreFieldMask);
	}

	if(getRoot() == NULL)
	{
		NodePtr TheRoot = Node::create();

		beginEditCP(ScenePtr(this), Scene::RootFieldMask);
			setRoot(TheRoot);
		endEditCP(ScenePtr(this), Scene::RootFieldMask);
	}
}

void Scene::initDefaults(void)
{
	Matrix Mat;
	Mat.setIdentity();

	beginEditCP(getDefaultCameraBeaconCore() , Transform::MatrixFieldMask);
		getDefaultCameraBeaconCore()->setMatrix(Mat);
	endEditCP(getDefaultCameraBeaconCore() , Transform::MatrixFieldMask);

	beginEditCP(getDefaultCameraBeacon(), Node::CoreFieldMask);
		getDefaultCameraBeacon()->setCore(getDefaultCameraBeaconCore());
	endEditCP(getDefaultCameraBeacon(), Node::CoreFieldMask);

	beginEditCP(getRootCore() , Transform::MatrixFieldMask);
		getRootCore()->setMatrix(Mat);
	endEditCP(getRootCore() , Transform::MatrixFieldMask);

	beginEditCP(getRoot(), Node::CoreFieldMask | Node::ChildrenFieldMask);
		getRoot()->setCore(getRootCore());
		while(getRoot()->getNChildren() > 0)
		{
			getRoot()->subChild(getRoot()->getNChildren()-1);
		}
		getRoot()->addChild(getDefaultCameraBeacon());
	endEditCP(getRoot(), Node::ChildrenFieldMask | Node::ChildrenFieldMask);

}

void Scene::attachNames(void)
{
	//Backgrounds
	for(::osg::UInt32 i(0); i<getBackgrounds().size() ; ++i)
	{
		attachName(getBackgrounds(i));
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
        if(getModelNodes(i) != NullFC)
        {
		    attachName(getModelNodes(i));
        }
	}

}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void Scene::producerSceneEntered(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneEnteredMethodId, e);
}

void Scene::producerSceneExited(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneExitedMethodId, e);
}

void Scene::producerSceneStarted(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneStartedMethodId, e);
}

void Scene::producerSceneEnded(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneEndedMethodId, e);
}

void Scene::producerSceneReset(const SceneEventPtr e)
{
    _Producer.produceEvent(SceneResetMethodId, e);
}


/*----------------------- constructors & destructors ----------------------*/

Scene::Scene(void) :
    Inherited()
{
}

Scene::Scene(const Scene &source) :
    Inherited(source)
{
}

Scene::~Scene(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Scene::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Scene::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Scene NI" << std::endl;
}


OSG_END_NAMESPACE

