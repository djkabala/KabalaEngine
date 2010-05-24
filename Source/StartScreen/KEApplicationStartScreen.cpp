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

#include "KEApplicationStartScreen.h"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include "Application/KEMainApplication.h"
#include "Application/KEApplicationSettings.h"

// UserInterface Headers
#include <OpenSG/OSGUIForeground.h>
#include <OpenSG/OSGInternalWindow.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include <OpenSG/OSGGraphics2D.h>
#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGPanel.h>
#include <OpenSG/OSGUIFont.h>
#include <OpenSG/OSGColorLayer.h>
#include <OpenSG/OSGFlowLayout.h>
#include <OpenSG/OSGSpringLayout.h>
#include <OpenSG/OSGSpringLayoutConstraints.h>
#include <OpenSG/OSGLayoutSpring.h>
#include <OpenSG/OSGLabel.h>

//Animation
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGFieldAnimation.h>
#include <OpenSG/OSGKeyframeAnimator.h>
#include <OpenSG/OSGKeyframeSequences.h>

#include <boost/filesystem/operations.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGApplicationStartScreenBase.cpp file.
// To modify it, please change the .fcd file (OSGApplicationStartScreen.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationStartScreen::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ApplicationStartScreen::attachApplication(void)
{
    Inherited::attachApplication();

    //Camera Transformation Node
    Matrix CameraTransformMatrix;
    CameraTransformMatrix.setTranslate(0.0f,0.0f, 5.0f);
    TransformRefPtr CameraBeaconTransform = Transform::create();
    CameraBeaconTransform->setMatrix(CameraTransformMatrix);

    NodeRefPtr CameraBeaconNode = Node::create();
    CameraBeaconNode->setCore(CameraBeaconTransform);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = NULL;
    //BoostPath TorusKnotFile(MainApplication::the()->getSettings()->getDataDirectory() / std::string("Models") / std::string("TorusKnot.osb"));
    //SLOG << "Loading Torus Knot from: " << TorusKnotFile.string() << std::endl;
    //if(boost::filesystem::exists(TorusKnotFile))
    //{
        //TorusGeometryNode = SceneFileHandler::the()->read(TorusKnotFile.native_file_string().c_str());
    //}
    //if(TorusGeometryNode == NULL)
    //{
        //SWARNING << "Could not load Torus Knot from: "
                 //<< TorusKnotFile.string() << " because this file doesn't exist."  << std::endl;
        TorusGeometryNode = makeTorus(.5, 2, 64, 64);
    //}

    //Scene Transformation
    TransformRefPtr SceneTransformCore = Transform::create();

    NodeRefPtr SceneTransformNode = Node::create();
    SceneTransformNode->setCore(SceneTransformCore);
    SceneTransformNode->addChild(TorusGeometryNode);

    //Light
    NodeRefPtr LightBeaconNode = Node::create();
    LightBeaconNode->setCore(Transform::create());

    DirectionalLightRefPtr SceneLightCore = DirectionalLight::create();
    SceneLightCore->setDirection(1.0,0.0,0.0);
    SceneLightCore->setBeacon(LightBeaconNode);

    NodeRefPtr SceneLightNode = Node::create();
    SceneLightNode->setCore(SceneLightCore);
    SceneLightNode->addChild(SceneTransformNode);


    // Make Main Scene Node and add the Torus
    NodeRefPtr DefaultRootNode = OSG::Node::create();
    DefaultRootNode->setCore(OSG::Group::create());
    DefaultRootNode->addChild(CameraBeaconNode);
    DefaultRootNode->addChild(SceneLightNode);
    DefaultRootNode->addChild(LightBeaconNode);

    //Camera
    PerspectiveCameraRefPtr DefaultCamera = PerspectiveCamera::create();
    DefaultCamera->setBeacon(CameraBeaconNode);
    DefaultCamera->setFov   (osgDegree2Rad(60.f));
    DefaultCamera->setNear  (0.1f);
    DefaultCamera->setFar   (10000.f);

    //Background
    GradientBackgroundRefPtr DefaultBackground = GradientBackground::create();
    DefaultBackground->addLine(Color3f(0.0f,0.0f,0.0f), 0.0f);
    DefaultBackground->addLine(Color3f(0.0f,0.0f,0.5f), 1.0f);

    //Animation
    //KeyFrames
    KeyframeTransformationSequenceRefPtr TransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    OSG::Matrix TempMat;

    TransformationKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5));
    TransformationKeyframes->addKeyframe(TempMat,4.0f);
    TempMat.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0));
    TransformationKeyframes->addKeyframe(TempMat,8.0f);
    TempMat.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5));
    TransformationKeyframes->addKeyframe(TempMat,12.0f);
    TempMat.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,16.0f);

    //Animator
    KeyframeAnimatorRefPtr TorusAnimator = OSG::KeyframeAnimator::create();
    TorusAnimator->setKeyframeSequence(TransformationKeyframes);

    //Animation
    /*_TorusAnimation = FieldAnimation::create();
    _TorusAnimation->setAnimator(TorusAnimator);
    _TorusAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    _TorusAnimation->setCycling(-1);
    _TorusAnimation->setAnimatedField(SceneTransformCore, std::string("matrix"));
    _TorusAnimation->attachUpdateProducer(MainApplication::the()->getMainWindow()->editEventProducer());
    _TorusAnimation->start();*/

    //Foreground
    //ImageForegroundRefPtr LogoForeground = ImageForeground::create();
    //BoostPath LogoPath(MainApplication::the()->getSettings()->getDataDirectory() / "Images/Logo.png");
    //ImageRefPtr LoadedImage = ImageFileHandler::the().read(LogoPath.string().c_str());

    //	LogoForeground->addImage( LoadedImage, Pnt2f( 0,0 ) );

    ForegroundRefPtr UserInterfaceForeground = createInterface();
    _TheUIDrawingSurface->setEventProducer(MainApplication::the()->getMainWindow());

    if(MainApplication::the()->getMainWindow() != NULL &&
       MainApplication::the()->getMainWindow()->getMFPort()->size() == 0)
    {
        ViewportRefPtr DefaultViewport = Viewport::create();
        DefaultViewport->setCamera                  (DefaultCamera);
        DefaultViewport->setRoot                    (DefaultRootNode);
        DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
        DefaultViewport->setBackground              (DefaultBackground);
        DefaultViewport->addForeground              (UserInterfaceForeground);

        MainApplication::the()->getMainWindow()->addPort(DefaultViewport);
    }

    MainApplication::the()->getMainWindow()->addKeyListener(&_StartScreenKeyListener);
    MainApplication::the()->getMainWindow()->addUpdateListener(&_ScreenUpdateListener);

}

void ApplicationStartScreen::dettachApplication(void)
{
    //_TorusAnimation->stop();

    _TheUIDrawingSurface->setEventProducer(NULL);

    MainApplication::the()->getMainWindow()->removeKeyListener(&_StartScreenKeyListener);
    MainApplication::the()->getMainWindow()->removeUpdateListener(&_ScreenUpdateListener);

    if(MainApplication::the()->getMainWindow() != NULL)
    {
        MainApplication::the()->getMainWindow()->subPort(0);
    }

    Inherited::dettachApplication();
}

void ApplicationStartScreen::reset(void)
{
}

ForegroundRefPtr ApplicationStartScreen::createInterface(void)
{
    // Create the Graphics
    GraphicsRefPtr StartScreenUIGraphics = OSG::Graphics2D::create();



    UIFontRefPtr ButtonFont = OSG::UIFont::create();
    ButtonFont->setSize(32);

    ButtonRefPtr BuilderButton = ::OSG::Button::create();
    BuilderButton->setPreferredSize(Vec2f(200, 75));
    BuilderButton->setText("Builder");
    BuilderButton->setFont(ButtonFont);
    BuilderButton->addActionListener(&_BuilderButtonActionListener); 

    ButtonRefPtr PlayerButton = ::OSG::Button::create();
    PlayerButton->setPreferredSize(Vec2f(200, 75));
    PlayerButton->setText("Player");
    PlayerButton->setFont(ButtonFont);
    PlayerButton->addActionListener(&_PlayerButtonActionListener); 

    ButtonRefPtr ExitButton = ::OSG::Button::create();
    ExitButton->setPreferredSize(Vec2f(200, 75));
    ExitButton->setText("Exit");
    ExitButton->setFont(ButtonFont);
    ExitButton->addActionListener(&_ExitButtonActionListener); 

    //ButtonPanel
    PanelRefPtr ButtonPanel = Panel::createEmpty();
    LayoutRefPtr ButtonPanelLayout = OSG::FlowLayout::create();
    ButtonPanel->pushToChildren(BuilderButton);
    ButtonPanel->pushToChildren(PlayerButton);
    ButtonPanel->pushToChildren(ExitButton);
    ButtonPanel->setLayout(ButtonPanelLayout);

    //Font
    UIFontRefPtr LabelFont = UIFont::create();
    LabelFont->setSize(16);

    //Version Label
    LabelRefPtr VersionLabel = OSG::Label::create();
    VersionLabel->setText("Version:");
    VersionLabel->setAlignment(Vec2f(1.0f,0.5f));
    VersionLabel->setPreferredSize(Vec2f(100,20));
    VersionLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    VersionLabel->setBackgrounds(NULL);
    VersionLabel->setBorders(NULL);
    VersionLabel->setFont(LabelFont);

    //Version Value Label
    LabelRefPtr VersionValueLabel = OSG::Label::create();
    VersionValueLabel->setText(getKabalaEngineVersion() + " - " + getKabalaEngineBuildType());
    VersionValueLabel->setPreferredSize(Vec2f(110,20));
    VersionValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    VersionValueLabel->setBackgrounds(NULL);
    VersionValueLabel->setBorders(NULL);
    VersionValueLabel->setFont(LabelFont);

    //Author Value Label
    LabelRefPtr AuthorValueLabel = OSG::Label::create();
    AuthorValueLabel->setText(getKabalaEngineAuthors());
    AuthorValueLabel->setPreferredSize(Vec2f(300,20));
    AuthorValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
    AuthorValueLabel->setBackgrounds(NULL);
    AuthorValueLabel->setBorders(NULL);
    AuthorValueLabel->setFont(LabelFont);

    // Create The Main InternalWindow
    InternalWindowRefPtr StartScreenInternalWindow = OSG::InternalWindow::create();

    //Layout
    SpringLayoutRefPtr StartScreenInternalWindowLayout = OSG::SpringLayout::create();
    //::OSG::Button Panel
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ButtonPanel, 0, SpringLayoutConstraints::NORTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ButtonPanel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);

    //Version Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, VersionLabel, 0, SpringLayoutConstraints::WEST_EDGE, VersionValueLabel);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, VersionLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, VersionLabel, LayoutSpring::height(VersionLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, VersionLabel, LayoutSpring::width(VersionLabel));

    //Version Value Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, VersionValueLabel, 0, SpringLayoutConstraints::EAST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, VersionValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, VersionValueLabel, LayoutSpring::height(VersionValueLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, VersionValueLabel, LayoutSpring::width(VersionValueLabel));

    //Author Value Label
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, AuthorValueLabel, 0, SpringLayoutConstraints::WEST_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, AuthorValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StartScreenInternalWindow);
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, AuthorValueLabel, LayoutSpring::height(AuthorValueLabel));
    StartScreenInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, AuthorValueLabel, LayoutSpring::width(AuthorValueLabel));

    StartScreenInternalWindow->pushToChildren(ButtonPanel);
    StartScreenInternalWindow->pushToChildren(AuthorValueLabel);
    StartScreenInternalWindow->pushToChildren(VersionLabel);
    StartScreenInternalWindow->pushToChildren(VersionValueLabel);
    StartScreenInternalWindow->setLayout(StartScreenInternalWindowLayout);
    StartScreenInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    StartScreenInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    StartScreenInternalWindow->setDrawTitlebar(false);
    StartScreenInternalWindow->setDrawDecorations(false);
    StartScreenInternalWindow->setResizable(false);

    // Create the Drawing Surface
    _TheUIDrawingSurface = UIDrawingSurface::create();
    _TheUIDrawingSurface->setGraphics(StartScreenUIGraphics);

    _TheUIDrawingSurface->openWindow(StartScreenInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr StartScreenUIForeground = OSG::UIForeground::create();

    StartScreenUIForeground->setDrawingSurface(_TheUIDrawingSurface);

    return StartScreenUIForeground;
}

void ApplicationStartScreen::start(void)
{
}

void ApplicationStartScreen::stop(void)
{
}

void ApplicationStartScreen::updateAnimation(const Time& Elps)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationStartScreen::ApplicationStartScreen(void) :
    Inherited(),
	_StartScreenKeyListener(ApplicationStartScreenRefPtr(this)),
	_BuilderButtonActionListener(ApplicationStartScreenRefPtr(this)),
	_PlayerButtonActionListener(ApplicationStartScreenRefPtr(this)),
	_ExitButtonActionListener(ApplicationStartScreenRefPtr(this)),
    _ScreenUpdateListener(ApplicationStartScreenRefPtr(this))
{
}

ApplicationStartScreen::ApplicationStartScreen(const ApplicationStartScreen &source) :
    Inherited(source),
	_StartScreenKeyListener(ApplicationStartScreenRefPtr(this)),
	_BuilderButtonActionListener(ApplicationStartScreenRefPtr(this)),
	_PlayerButtonActionListener(ApplicationStartScreenRefPtr(this)),
	_ExitButtonActionListener(ApplicationStartScreenRefPtr(this)),
    _ScreenUpdateListener(ApplicationStartScreenRefPtr(this))
{
}

ApplicationStartScreen::~ApplicationStartScreen(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationStartScreen::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ApplicationStartScreen::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ApplicationStartScreen NI" << std::endl;
}

void ApplicationStartScreen::StartScreenKeyListener::keyTyped(const KeyEventUnrecPtr e)
{
   if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
   {
		MainApplication::the()->exit();
   }
}

void ApplicationStartScreen::BuilderButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	MainApplication::the()->attachBuilder();
}

void ApplicationStartScreen::PlayerButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	MainApplication::the()->attachPlayer();
}

void ApplicationStartScreen::ExitButtonActionListener::actionPerformed(const ActionEventUnrecPtr e)
{
	MainApplication::the()->exit();
}

void ApplicationStartScreen::ScreenUpdateListener::update(const UpdateEventUnrecPtr e)
{
    _ApplicationStartScreen->updateAnimation(e->getElapsedTime());
}

OSG_END_NAMESPACE
