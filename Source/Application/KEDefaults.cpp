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

#include "KEDefaults.h"
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGNameAttachment.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGTextureBackground.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGViewport.h>
#include "Project/KEProject.h"
#include "Project/Scene/KEScene.h"
#include "Project/SceneObject/KESceneObject.h"

#include "KEMainApplication.h"

//Physics

#include <OpenSG/OSGPhysicsHandler.h>
#include <OpenSG/OSGPhysicsWorld.h>
#include <OpenSG/OSGPhysicsHashSpace.h>
#include <OpenSG/OSGPhysicsBoxGeom.h>
#include <OpenSG/OSGPhysicsTriMeshGeom.h>
#include <OpenSG/OSGPhysicsSphereGeom.h>
#include <OpenSG/OSGShadowStage.h>

#include <boost/filesystem/convenience.hpp>

//Behaviors
#include "Library/Behavior/KECameraControlBehavior.h"

OSG_BEGIN_NAMESPACE

SceneTransitPtr createDefaultScene(void)
{
    //The Default Scene
    //Create the scene
    SceneRefPtr TheDefaultScene = Scene::create();
    setName(TheDefaultScene, "Untitled Scene" );

    //Setup Physics World and space
    PhysicsWorldRecPtr ScenePhysicsWorld = PhysicsWorld::create();
    ScenePhysicsWorld->setWorldContactSurfaceLayer(0.005);
    ScenePhysicsWorld->setAutoDisableFlag(1);
    ScenePhysicsWorld->setAutoDisableTime(0.75);
    ScenePhysicsWorld->setWorldContactMaxCorrectingVel(100.0);
    ScenePhysicsWorld->setGravity(Vec3f(0.0, -9.81, 0.0));
    
    TheDefaultScene->setPhysicsWorld(ScenePhysicsWorld);

    CollisionContactParametersRefPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
    DefaultCollisionParams->setMode(dContactBounce | dContactApprox1);
    DefaultCollisionParams->setMu(0.1);
    DefaultCollisionParams->setMu2(0.0);
    DefaultCollisionParams->setBounce(0.4);
    DefaultCollisionParams->setBounceSpeedThreshold(0.1);
    DefaultCollisionParams->setSoftCFM(0.1);
    DefaultCollisionParams->setSoftERP(0.2);
    DefaultCollisionParams->setMotion1(0.0);
    DefaultCollisionParams->setMotion2(0.0);
    DefaultCollisionParams->setMotionN(0.0);
    DefaultCollisionParams->setSlip1(0.0);
    DefaultCollisionParams->setSlip2(0.0);

    PhysicsHashSpaceRecPtr ScenePhysicsSpace = PhysicsHashSpace::create();
    ScenePhysicsSpace->setDefaultCollisionParameters(DefaultCollisionParams);

    //NodeRefPtr CameraGeometryNode = makeSphere(2, 1.0f);

    //Camera Transformation Node
    Matrix CameraTransformMatrix;
    CameraTransformMatrix.setTranslate(MainApplication::the()->getSettings().get<Pnt3f>("basic.default_scene.camera.position"));
    TransformRefPtr CameraBeaconTransform = Transform::create();
    CameraBeaconTransform->setMatrix(CameraTransformMatrix);

    NodeRefPtr CameraBeaconNode = Node::create();
    setName(CameraBeaconNode, "Camera Beacon" );
    CameraBeaconNode->setCore(CameraBeaconTransform);
    //CameraBeaconNode->addChild(CameraGeometryNode);

    //Camera
    PerspectiveCameraRefPtr DefaultSceneCamera = PerspectiveCamera::create();
    setName(DefaultSceneCamera, "Untitled Camera" );

    DefaultSceneCamera->setFov(MainApplication::the()->getSettings().get<Real32>("basic.default_scene.camera.fov"));
    DefaultSceneCamera->setNear(MainApplication::the()->getSettings().get<Real32>("basic.default_scene.camera.near_plane"));
    DefaultSceneCamera->setFar(MainApplication::the()->getSettings().get<Real32>("basic.default_scene.camera.far_plane"));
    DefaultSceneCamera->setBeacon(CameraBeaconNode);

    //Camera ODE data
    PhysicsBodyRecPtr CameraPhysicsBody = PhysicsBody::create(ScenePhysicsWorld);
    setName(CameraPhysicsBody, "DefaultScene.CameraBody");
    CameraPhysicsBody->setPosition(Vec3f(0.0f,8.0f,5.0f));

    CameraPhysicsBody->setSphereMass(1.0f,0.5f);

    PhysicsSphereGeomRecPtr CameraPhysicsGeom = PhysicsSphereGeom::create();
    CameraPhysicsGeom->setBody(CameraPhysicsBody);
    CameraPhysicsGeom->setSpace(ScenePhysicsSpace);
    CameraPhysicsGeom->setRadius(0.5f);

    //add attachments
    CameraBeaconNode->addAttachment(CameraPhysicsGeom);
    CameraBeaconNode->addAttachment(CameraPhysicsBody);

    //Camera Behavior
    CameraControlBehaviorRecPtr CameraBehavior = CameraControlBehavior::create();

    SceneObjectRecPtr CameraSceneObject = SceneObject::create();
    setName(CameraSceneObject, "Camera Scene Object" );
    CameraSceneObject->setNode(CameraBeaconNode);
    CameraSceneObject->pushToBehaviors(CameraBehavior);
    TheDefaultScene->pushToSceneObjects(CameraSceneObject);

    //Shadows
    ShadowStageRecPtr DefaultShadowViewport =ShadowStage::create();

    //DefaultShadowViewport->setOffFactor(4.0);
    //DefaultShadowViewport->setOffBias(8.0);
    //used to set global shadow intensity, ignores shadow intensity from light sources if != 0.0
    DefaultShadowViewport->setShadowMode(ShadowStage::NO_SHADOW);
    //DefaultShadowViewport->setShadowMode(ShadowStage::PCF_SHADOW_MAP);
    DefaultShadowViewport->setGlobalShadowIntensity(0.9);
    DefaultShadowViewport->setMapSize(512);
    //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    //ShadowSmoothness also used to define the light size for PCSS_SHADOW_MAP
    DefaultShadowViewport->setShadowSmoothness(0.5);
    // add light sources here
    //DefaultShadowViewport->editMFExcludeNodes()->push_back(obj1_trans_node);
    //DefaultShadowViewport->setAutoSearchForLights(true);

    //Light Beacon
    Matrix LightTransformMatrix;
    LightTransformMatrix.setTranslate(MainApplication::the()->getSettings().get<Pnt3f>("basic.default_scene.point_light.position"));
    TransformRefPtr LightBeaconTransform = Transform::create();
    LightBeaconTransform->setMatrix(LightTransformMatrix);

    NodeRefPtr LightBeaconNode = Node::create();
    setName(LightBeaconNode, "Light Beacon" );
    LightBeaconNode->setCore(LightBeaconTransform);

    //Make the Light
    PointLightRefPtr ThePointLight = PointLight::create();

    ThePointLight->setBeacon(LightBeaconNode);

    NodeRefPtr LightNode = Node::create();
    setName(LightNode, "Light");
    LightNode->setCore(ThePointLight);
    DefaultShadowViewport->editMFLightNodes  ()->push_back(LightNode);

    // Make Torus Node (creates Torus in background of scene)
    if(MainApplication::the()->getSettings().get<bool>("basic.default_scene.torus.draw"))
    {
        Pnt3f Position(MainApplication::the()->getSettings().get<Pnt3f>("basic.default_scene.torus.position"));
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 24, 24);
        //NodeRefPtr TorusGeometryNode = makeCylinder(1.0,0.05,24,true,true,true);
        setName(TorusGeometryNode, "Donut" );

        //create ODE data
        PhysicsBodyRecPtr torusBody = PhysicsBody::create(ScenePhysicsWorld);
        torusBody->setPosition(Vec3f(Position));
        torusBody->setGravityMode(false);

        torusBody->setBoxMass(1.0, 1,1,1);

        PhysicsTriMeshGeomRecPtr torusGeom = PhysicsTriMeshGeom::create();
        torusGeom->setBody(torusBody);
        torusGeom->setSpace(ScenePhysicsSpace);
        torusGeom->setGeometryNode(TorusGeometryNode);
        commitChanges();

        Matrix TorusTransformMatrix;
        TorusTransformMatrix.setTranslate(Position);

        TransformRefPtr TorusTransform = Transform::create();
        TorusTransform->setMatrix(TorusTransformMatrix);

        NodeRefPtr TorusTransformNode = Node::create();
        setName(TorusTransformNode, "Donut Transform" );
        TorusTransformNode->setCore(TorusTransform);
        TorusTransformNode->addChild(TorusGeometryNode);

        //add attachments
        TorusTransformNode->addAttachment(torusGeom);
        TorusTransformNode->addAttachment(torusBody);

        LightNode->addChild(TorusTransformNode);

        SceneObjectRecPtr TorusSceneObject = SceneObject::create();
        setName(TorusSceneObject, "Donut Scene Object" );
        TorusSceneObject->setNode(TorusTransformNode);
        TheDefaultScene->pushToSceneObjects(TorusSceneObject);

    }

    if(MainApplication::the()->getSettings().get<bool>("basic.default_scene.box.draw"))
    {
        Vec3f Lengths(3.0f, 3.0f, 3.0f);
        // Make Box Node (creates Box in background of scene)
        NodeRefPtr BoxGeometryNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 8, 8, 8);
        setName(BoxGeometryNode, "Box" );

        Matrix BoxTransformMatrix;
        Pnt3f Position(MainApplication::the()->getSettings().get<Pnt3f>("basic.default_scene.box.position"));
        BoxTransformMatrix.setTranslate(Position);

        TransformRefPtr BoxTransform = Transform::create();
        BoxTransform->setMatrix(BoxTransformMatrix);

        NodeRefPtr BoxTransformNode = Node::create();
        setName(BoxTransformNode, "Box Transform" );
        BoxTransformNode->setCore(BoxTransform);
        BoxTransformNode->addChild(BoxGeometryNode);
        LightNode->addChild(BoxTransformNode);

        //create ODE data
        PhysicsBodyRecPtr boxBody = PhysicsBody::create(ScenePhysicsWorld);
        boxBody->setPosition(Vec3f(Position));
        boxBody->setGravityMode(false);

        boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

        PhysicsBoxGeomRecPtr boxGeom = PhysicsBoxGeom::create();
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(ScenePhysicsSpace);
        boxGeom->setLengths(Lengths);

        //add attachments
        BoxTransformNode->addAttachment(boxGeom);
        BoxTransformNode->addAttachment(boxBody);

        SceneObjectRecPtr BoxSceneObject = SceneObject::create();
        setName(BoxSceneObject, "Box Scene Object" );
        BoxSceneObject->setNode(BoxTransformNode);
        TheDefaultScene->pushToSceneObjects(BoxSceneObject);
    }


    if(MainApplication::the()->getSettings().get<bool>("basic.default_scene.cone.draw"))
    {
        Pnt3f Position(MainApplication::the()->getSettings().get<Pnt3f>("basic.default_scene.cone.position"));
        // Make Cone Node (creates Cone in background of scene)
        NodeRefPtr ConeGeometryNode = makeCone(3.5, 1.5f, 24, true, true);
        //NodeRefPtr ConeGeometryNode = makeCone(0.4, 0.1f, 24, true, true);
        setName(ConeGeometryNode, "Cone" );

        //create ODE data
        PhysicsBodyRecPtr coneBody = PhysicsBody::create(ScenePhysicsWorld);
        coneBody->setPosition(Vec3f(Position));
        coneBody->setGravityMode(false);

        coneBody->setBoxMass(1.0, 1,1,1);

        PhysicsTriMeshGeomRecPtr coneGeom = PhysicsTriMeshGeom::create();
        coneGeom->setBody(coneBody);
        coneGeom->setSpace(ScenePhysicsSpace);
        coneGeom->setGeometryNode(ConeGeometryNode);
        commitChanges();

        Matrix ConeTransformMatrix;
        ConeTransformMatrix.setTranslate(Position);

        TransformRefPtr ConeTransform = Transform::create();
        ConeTransform->setMatrix(ConeTransformMatrix);

        NodeRefPtr ConeTransformNode = Node::create();
        setName(ConeTransformNode, "Cone Transform" );
        ConeTransformNode->setCore(ConeTransform);
        ConeTransformNode->addChild(ConeGeometryNode);
        LightNode->addChild(ConeTransformNode);

        //add attachments
        ConeTransformNode->addAttachment(coneGeom);
        ConeTransformNode->addAttachment(coneBody);

        SceneObjectRecPtr ConeSceneObject = SceneObject::create();
        setName(ConeSceneObject, "Cone Scene Object" );
        ConeSceneObject->setNode(ConeTransformNode);
        TheDefaultScene->pushToSceneObjects(ConeSceneObject);
    }

    //Create a ground plane
    SimpleMaterialRecPtr GroundMaterial = SimpleMaterial::create();
    GroundMaterial->setAmbient(Color3f(0.0,0.3,0.0));
    GroundMaterial->setDiffuse(Color3f(0.0,0.6,0.0));
    GroundMaterial->setSpecular(Color3f(0.2,0.2,0.2));
    GroundMaterial->setShininess(2.0f);

    GeometryRefPtr GroundGeometry = makeBoxGeo(60.0,1.0,60.0, 60,2,60);
    GroundGeometry->setMaterial(GroundMaterial);

    NodeRefPtr GroundGeometryNode = makeNodeFor(GroundGeometry);
    setName(GroundGeometryNode, "Ground" );

    SceneObjectRecPtr GroundSceneObject = SceneObject::create();
    setName(GroundSceneObject, "Ground Scene Object" );
    GroundSceneObject->setNode(GroundGeometryNode);
    TheDefaultScene->pushToSceneObjects(GroundSceneObject);

    Matrix GroundTransformMatrix;

    TransformRefPtr GroundTransform = Transform::create();
    GroundTransform->setMatrix(GroundTransformMatrix);

    NodeRefPtr GroundTransformNode = Node::create();
    setName(GroundTransformNode, "Ground Transform" );
    GroundTransformNode->setCore(GroundTransform);
    GroundTransformNode->addChild(GroundGeometryNode);
    LightNode->addChild(GroundTransformNode);

    //create Physical Attachments
    PhysicsBoxGeomRecPtr planeGeom = PhysicsBoxGeom::create();
    planeGeom->setLengths(Vec3f(60.0,1.0,60.0));
    planeGeom->setSpace(ScenePhysicsSpace);
    GroundGeometryNode->addAttachment(planeGeom);

    //Scene Root Node
    NodeRefPtr DefaultSceneNode = Node::create();
    setName(DefaultSceneNode, "Scene Root" );
    DefaultSceneNode->setCore(DefaultShadowViewport);
    DefaultSceneNode->addChild(LightNode);
    DefaultSceneNode->addChild(LightBeaconNode);
    LightNode->addChild(CameraBeaconNode);

    //Background
    SolidBackgroundRefPtr DefaultSceneBackground = SolidBackground::create();
    setName(DefaultSceneBackground, "Untitled Background" );
    DefaultSceneBackground->setColor(MainApplication::the()->getSettings().get<Color3r>("basic.default_scene.background.color"));

    //Viewport
    ViewportRefPtr DefaultSceneViewport = Viewport::create();
    setName(DefaultSceneViewport, "Untitled Viewport" );
    DefaultSceneViewport->setSize(0.0,0.0,1.0,1.0);
    DefaultSceneViewport->setCamera(DefaultSceneCamera);
    DefaultSceneViewport->setBackground(DefaultSceneBackground);
    DefaultSceneViewport->setRoot(DefaultSceneNode);

    TheDefaultScene->pushToViewports(DefaultSceneViewport);

    //Create the Physics handler
    PhysicsHandlerRecPtr ScenePhysicsHandler = PhysicsHandler::create();
    ScenePhysicsHandler->setWorld(ScenePhysicsWorld);
    ScenePhysicsHandler->pushToSpaces(ScenePhysicsSpace);
    ScenePhysicsHandler->setUpdateNode(DefaultSceneViewport->getRoot());


    TheDefaultScene->setPhysicsHandler(ScenePhysicsHandler);



    return SceneTransitPtr(TheDefaultScene);
}

ProjectTransitPtr createDefaultProject(void)
{
    ProjectRefPtr TheDefaultProject = ProjectBase::create();


    SceneRefPtr TheDefaultScene(createDefaultScene());

    TheDefaultProject->pushToScenes(TheDefaultScene);
    TheDefaultProject->setInitialScene(TheDefaultScene);	
    setName(TheDefaultProject,"Untitled Project");

    return ProjectTransitPtr(TheDefaultProject);
}

ViewportTransitPtr createDefaultLoadingViewport(void)
{
    //Camera Transformation Node
    Matrix CameraTransformMatrix;
    CameraTransformMatrix.setTranslate(MainApplication::the()->getSettings().get<Pnt3f>("basic.loading_viewport.camera.position"));
    TransformRefPtr CameraBeaconTransform = Transform::create();

    NodeRefPtr CameraBeaconNode = Node::create();
    CameraBeaconNode->setCore(CameraBeaconTransform);

    //Camera
    PerspectiveCameraRefPtr DefaultCamera = PerspectiveCamera::create();

    DefaultCamera->setFov(MainApplication::the()->getSettings().get<Real32>("basic.loading_viewport.camera.fov"));
    DefaultCamera->setNear(MainApplication::the()->getSettings().get<Real32>("basic.loading_viewport.camera.near_plane"));
    DefaultCamera->setFar(MainApplication::the()->getSettings().get<Real32>("basic.loading_viewport.camera.far_plane"));
    DefaultCamera->setBeacon(CameraBeaconNode);

    // Root Node
    NodeRefPtr DefaultNode = Node::create();
    DefaultNode->setCore(OSG::Group::create());
    DefaultNode->addChild(CameraBeaconNode);

    //Background
    BoostPath LoadingImagePath = MainApplication::the()->getSettings().get<BoostPath>("basic.loading_viewport.background.image_path");
    if(!LoadingImagePath.is_complete())
    {
        LoadingImagePath = MainApplication::the()->getSettings().get<BoostPath>("basic.data.directory") / LoadingImagePath;
    }

    BackgroundRefPtr DefaultBackground;
    if(!LoadingImagePath.empty())
    {
        if(boost::filesystem::exists(LoadingImagePath))
        {
            ImageRefPtr LoadingImage = ImageFileHandler::the()->read(LoadingImagePath.string().c_str());
            if(LoadingImage != NULL)
            {
                TextureObjChunkRefPtr LoadingTexture = TextureObjChunk::create();
                LoadingTexture->setImage(LoadingImage);
                LoadingTexture->setMinFilter(GL_LINEAR);

                DefaultBackground = TextureBackground::create();
                dynamic_pointer_cast<TextureBackground>(DefaultBackground)->setTexture(LoadingTexture);
                dynamic_pointer_cast<TextureBackground>(DefaultBackground)->editMFTexCoords()->push_back(Pnt2f(0.0f,0.0f));
                dynamic_pointer_cast<TextureBackground>(DefaultBackground)->editMFTexCoords()->push_back(Pnt2f(1.0f,0.0f));
                dynamic_pointer_cast<TextureBackground>(DefaultBackground)->editMFTexCoords()->push_back(Pnt2f(1.0f,1.0f));
                dynamic_pointer_cast<TextureBackground>(DefaultBackground)->editMFTexCoords()->push_back(Pnt2f(0.0f,1.0f));
            }
            else
            {
                SWARNING << "Failed to load 'loading image' from: " << LoadingImagePath.string() << std::endl;
            }
        }
        else
        {
            SWARNING << "Loading image file does not exist: " << LoadingImagePath.string() << std::endl;
        }
    }

    //If the image failed to load
    if(DefaultBackground == NULL)
    {
        DefaultBackground = SolidBackground::create();
        dynamic_pointer_cast<SolidBackground>(DefaultBackground)->setColor(MainApplication::the()->getSettings().get<Color3r>("basic.loading_viewport.background.color"));
    }

    //Viewport
    ViewportRefPtr DefaultViewport = Viewport::create();
    DefaultViewport->setSize(0.0,0.0,1.0,1.0);
    DefaultViewport->setCamera(DefaultCamera);
    DefaultViewport->setBackground(DefaultBackground);
    DefaultViewport->setRoot(DefaultNode);

    return ViewportTransitPtr(DefaultViewport);
}

OSG_END_NAMESPACE
