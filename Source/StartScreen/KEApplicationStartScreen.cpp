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

#include <OpenSG/OSGConfig.h>
#include "KEConfig.h"

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
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include "Application/KEMainApplication.h"
#include "Application/KEApplicationSettings.h"

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/UserInterface/OSGLabel.h>

//Animation
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

#include <boost/filesystem/operations.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ApplicationStartScreen
The ApplicationStartScreen. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationStartScreen::initMethod (void)
{
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
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(CameraTransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = NullFC;
    Path TorusKnotFile(MainApplication::the()->getSettings()->getDataDirectory() / std::string("Models") / std::string("TorusKnot.osb"));
    if(boost::filesystem::exists(TorusKnotFile))
    {
        TorusGeometryNode = SceneFileHandler::the().read(TorusKnotFile.native_file_string().c_str());
    }
    if(TorusGeometryNode == NullFC)
    {
        TorusGeometryNode = makeTorus(.5, 2, 64, 64);
    }

    //Scene Transformation
    TransformPtr SceneTransformCore = Transform::create();

	NodePtr SceneTransformNode = Node::create();
	beginEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		SceneTransformNode->setCore(SceneTransformCore);
        SceneTransformNode->addChild(TorusGeometryNode);
	endEditCP(SceneTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Light
	NodePtr LightBeaconNode = Node::create();
	beginEditCP(LightBeaconNode, Node::CoreFieldMask);
		LightBeaconNode->setCore(Transform::create());
	endEditCP(LightBeaconNode, Node::CoreFieldMask);

    DirectionalLightPtr SceneLightCore = DirectionalLight::create();
    beginEditCP(SceneLightCore, DirectionalLight::DirectionFieldMask | DirectionalLight::BeaconFieldMask);
        SceneLightCore->setDirection(1.0,0.0,0.0);
        SceneLightCore->setBeacon(LightBeaconNode);
    endEditCP(SceneLightCore, DirectionalLight::DirectionFieldMask | DirectionalLight::BeaconFieldMask);

    NodePtr SceneLightNode = Node::create();
    beginEditCP(SceneLightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        SceneLightNode->setCore(SceneLightCore);
        SceneLightNode->addChild(SceneTransformNode);
    endEditCP(SceneLightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);


    // Make Main Scene Node and add the Torus
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(CameraBeaconNode);
        DefaultRootNode->addChild(SceneLightNode);
        DefaultRootNode->addChild(LightBeaconNode);
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
	GradientBackgroundPtr DefaultBackground = GradientBackground::create();
	beginEditCP(DefaultBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);
		DefaultBackground->addLine(Color3f(0.0f,0.0f,0.0f), 0.0f);
		DefaultBackground->addLine(Color3f(0.0f,0.0f,0.5f), 1.0f);
	endEditCP(DefaultBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);

    //Animation
    //KeyFrames
    KeyframeTransformationsSequencePtr TransformationKeyframes = KeyframeTransformationsSequence44f::create();
	osg::Matrix TempMat;

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
    KeyframeAnimatorPtr TorusAnimator = osg::KeyframeAnimator::create();
    beginEditCP(TorusAnimator);
        TorusAnimator->setKeyframeSequence(TransformationKeyframes);
    endEditCP(TorusAnimator);

    //Animation
    _TorusAnimation = FieldAnimation::create();
    beginEditCP(_TorusAnimation);
        _TorusAnimation->setAnimator(TorusAnimator);
        _TorusAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        _TorusAnimation->setCycling(-1);
    endEditCP(_TorusAnimation);
	_TorusAnimation->setAnimatedField(SceneTransformCore, std::string("matrix"));

    //Animation Advancer
    _AnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(_AnimationAdvancer);
        ElapsedTimeAnimationAdvancer::Ptr::dcast(_AnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(_AnimationAdvancer);

	//Foreground
	//ImageForegroundPtr LogoForeground = ImageForeground::create();
	//Path LogoPath(MainApplication::the()->getSettings()->getDataDirectory() / "Images/Logo.png");
    //ImagePtr LoadedImage = ImageFileHandler::the().read(LogoPath.string().c_str());

	//beginEditCP(LogoForeground);
	//	LogoForeground->addImage( LoadedImage, Pnt2f( 0,0 ) );
	//endEditCP  (LogoForeground);

	ForegroundPtr UserInterfaceForeground = createInterface();
    beginEditCP(_TheUIDrawingSurface, UIDrawingSurface::EventProducerFieldMask);
        _TheUIDrawingSurface->setEventProducer(MainApplication::the()->getMainWindowEventProducer());
    endEditCP(_TheUIDrawingSurface, UIDrawingSurface::EventProducerFieldMask);

	if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC && MainApplication::the()->getMainWindowEventProducer()->getWindow()->getPort().size() == 0)
	{
		ViewportPtr DefaultViewport = Viewport::create();
		beginEditCP(DefaultViewport);
			DefaultViewport->setCamera                  (DefaultCamera);
			DefaultViewport->setRoot                    (DefaultRootNode);
			DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
			DefaultViewport->setBackground              (DefaultBackground);
			//DefaultViewport->getForegrounds().push_back    (LogoForeground);
			DefaultViewport->getForegrounds().push_back    (UserInterfaceForeground);
		endEditCP(DefaultViewport);

		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->addPort(DefaultViewport);
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}

	MainApplication::the()->getMainWindowEventProducer()->addKeyListener(&_StartScreenKeyListener);
	MainApplication::the()->getMainWindowEventProducer()->addUpdateListener(&_ScreenUpdateListener);
    
}

void ApplicationStartScreen::dettachApplication(void)
{
    beginEditCP(_TheUIDrawingSurface, UIDrawingSurface::EventProducerFieldMask);
        _TheUIDrawingSurface->setEventProducer(NullFC);
    endEditCP(_TheUIDrawingSurface, UIDrawingSurface::EventProducerFieldMask);

	MainApplication::the()->getMainWindowEventProducer()->removeKeyListener(&_StartScreenKeyListener);
	MainApplication::the()->getMainWindowEventProducer()->removeUpdateListener(&_ScreenUpdateListener);

	if(MainApplication::the()->getMainWindowEventProducer()->getWindow() != NullFC)
	{
		beginEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
			MainApplication::the()->getMainWindowEventProducer()->getWindow()->subPort(0);
		endEditCP(MainApplication::the()->getMainWindowEventProducer()->getWindow(), Window::PortFieldMask);
	}

	Inherited::dettachApplication();
}

void ApplicationStartScreen::reset(void)
{
}

ForegroundPtr ApplicationStartScreen::createInterface(void)
{
    // Create the Graphics
    GraphicsPtr StartScreenUIGraphics = osg::Graphics2D::create();
	


    UIFontPtr ButtonFont = osg::UIFont::create();
    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(32);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);

    ButtonPtr BuilderButton = ::osg::Button::create();
    beginEditCP(BuilderButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
            BuilderButton->setPreferredSize(Vec2f(200, 75));
            BuilderButton->setText("Builder");
            BuilderButton->setFont(ButtonFont);
    endEditCP(BuilderButton,::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
    BuilderButton->addActionListener(&_BuilderButtonActionListener); 
	
    ButtonPtr PlayerButton = ::osg::Button::create();
    beginEditCP(PlayerButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
            PlayerButton->setPreferredSize(Vec2f(200, 75));
            PlayerButton->setText("Player");
            PlayerButton->setFont(ButtonFont);
    endEditCP(PlayerButton,::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
    PlayerButton->addActionListener(&_PlayerButtonActionListener); 
	
    ButtonPtr ExitButton = ::osg::Button::create();
    beginEditCP(ExitButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
            ExitButton->setPreferredSize(Vec2f(200, 75));
            ExitButton->setText("Exit");
            ExitButton->setFont(ButtonFont);
    endEditCP(ExitButton,::osg::Button::PreferredSizeFieldMask | ::osg::Button::TextFieldMask | ::osg::Button::FontFieldMask);
    ExitButton->addActionListener(&_ExitButtonActionListener); 
           
	//ButtonPanel
	PanelPtr ButtonPanel = Panel::createEmpty();
    LayoutPtr ButtonPanelLayout = osg::FlowLayout::create();
	beginEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
       ButtonPanel->getChildren().push_back(BuilderButton);
       ButtonPanel->getChildren().push_back(PlayerButton);
       ButtonPanel->getChildren().push_back(ExitButton);
       ButtonPanel->setLayout(ButtonPanelLayout);
	endEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	//Font
    UIFontPtr LabelFont = UIFont::create();
	beginEditCP(LabelFont, UIFont::SizeFieldMask);
        LabelFont->setSize(16);
    endEditCP(LabelFont, UIFont::SizeFieldMask);

	//Version Label
    LabelPtr VersionLabel = osg::Label::create();
	beginEditCP(VersionLabel, Label::TextFieldMask | Label::FontFieldMask | Label::AlignmentFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
		VersionLabel->setText("Version:");
		VersionLabel->setAlignment(Vec2f(1.0f,0.5f));
        VersionLabel->setPreferredSize(Vec2f(100,20));
		VersionLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
		VersionLabel->setBackgrounds(NullFC);
		VersionLabel->setBorders(NullFC);
		VersionLabel->setFont(LabelFont);
	endEditCP(VersionLabel, Label::TextFieldMask | Label::FontFieldMask | Label::AlignmentFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);

	//Version Value Label
    LabelPtr VersionValueLabel = osg::Label::create();
	beginEditCP(VersionValueLabel, Label::TextFieldMask | Label::FontFieldMask | Label::PreferredSizeFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
        VersionValueLabel->setText(getKabalaEngineVersion());
        VersionValueLabel->setPreferredSize(Vec2f(70,20));
		VersionValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
		VersionValueLabel->setBackgrounds(NullFC);
		VersionValueLabel->setBorders(NullFC);
		VersionValueLabel->setFont(LabelFont);
	endEditCP(VersionValueLabel, Label::TextFieldMask | Label::FontFieldMask | Label::PreferredSizeFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);

	//Author Value Label
    LabelPtr AuthorValueLabel = osg::Label::create();
	beginEditCP(AuthorValueLabel, Label::TextFieldMask | Label::FontFieldMask | Label::PreferredSizeFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);
        AuthorValueLabel->setText(getKabalaEngineAuthors());
        AuthorValueLabel->setPreferredSize(Vec2f(100,20));
		AuthorValueLabel->setTextColors(Color4f(1.0f,1.0f,1.0f,1.0f));
		AuthorValueLabel->setBackgrounds(NullFC);
		AuthorValueLabel->setBorders(NullFC);
		AuthorValueLabel->setFont(LabelFont);
	endEditCP(AuthorValueLabel, Label::TextFieldMask | Label::FontFieldMask | Label::PreferredSizeFieldMask | Label::TextColorsFieldMask | Label::BackgroundsFieldMask | Label::BordersFieldMask);

    // Create The Main InternalWindow
    InternalWindowPtr StartScreenInternalWindow = osg::InternalWindow::create();

	//Layout
    SpringLayoutPtr StartScreenInternalWindowLayout = osg::SpringLayout::create();
	//::osg::Button Panel
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

	beginEditCP(StartScreenInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::DrawDecorationsFieldMask | InternalWindow::ResizableFieldMask);
       StartScreenInternalWindow->getChildren().push_back(ButtonPanel);
       StartScreenInternalWindow->getChildren().push_back(AuthorValueLabel);
       StartScreenInternalWindow->getChildren().push_back(VersionLabel);
       StartScreenInternalWindow->getChildren().push_back(VersionValueLabel);
       StartScreenInternalWindow->setLayout(StartScreenInternalWindowLayout);
	   StartScreenInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   StartScreenInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   StartScreenInternalWindow->setDrawTitlebar(false);
	   StartScreenInternalWindow->setDrawDecorations(false);
	   StartScreenInternalWindow->setResizable(false);
    endEditCP(StartScreenInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::DrawDecorationsFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    _TheUIDrawingSurface = UIDrawingSurface::create();
    beginEditCP(_TheUIDrawingSurface, UIDrawingSurface::GraphicsFieldMask);
        _TheUIDrawingSurface->setGraphics(StartScreenUIGraphics);
    endEditCP(_TheUIDrawingSurface, UIDrawingSurface::GraphicsFieldMask);
    
	_TheUIDrawingSurface->openWindow(StartScreenInternalWindow);
	
	// Create the UI Foreground Object
    UIForegroundPtr StartScreenUIForeground = osg::UIForeground::create();

    beginEditCP(StartScreenUIForeground, UIForeground::DrawingSurfaceFieldMask);
        StartScreenUIForeground->setDrawingSurface(_TheUIDrawingSurface);
    endEditCP(StartScreenUIForeground, UIForeground::DrawingSurfaceFieldMask);

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
   _AnimationAdvancer->update(Elps);
   _TorusAnimation->update(_AnimationAdvancer);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationStartScreen::ApplicationStartScreen(void) :
    Inherited(),
	_StartScreenKeyListener(ApplicationStartScreenPtr(this)),
	_BuilderButtonActionListener(ApplicationStartScreenPtr(this)),
	_PlayerButtonActionListener(ApplicationStartScreenPtr(this)),
	_ExitButtonActionListener(ApplicationStartScreenPtr(this)),
    _ScreenUpdateListener(ApplicationStartScreenPtr(this))
{
}

ApplicationStartScreen::ApplicationStartScreen(const ApplicationStartScreen &source) :
    Inherited(source),
	_StartScreenKeyListener(ApplicationStartScreenPtr(this)),
	_BuilderButtonActionListener(ApplicationStartScreenPtr(this)),
	_PlayerButtonActionListener(ApplicationStartScreenPtr(this)),
	_ExitButtonActionListener(ApplicationStartScreenPtr(this)),
    _ScreenUpdateListener(ApplicationStartScreenPtr(this))
{
}

ApplicationStartScreen::~ApplicationStartScreen(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationStartScreen::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ApplicationStartScreen::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ApplicationStartScreen NI" << std::endl;
}


void ApplicationStartScreen::StartScreenKeyListener::keyTyped(const KeyEvent& e)
{
   if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
   {
		MainApplication::the()->exit();
   }
}

void ApplicationStartScreen::BuilderButtonActionListener::actionPerformed(const ActionEvent& e)
{
	MainApplication::the()->attachBuilder();
}

void ApplicationStartScreen::PlayerButtonActionListener::actionPerformed(const ActionEvent& e)
{
	MainApplication::the()->attachPlayer();
}

void ApplicationStartScreen::ExitButtonActionListener::actionPerformed(const ActionEvent& e)
{
	MainApplication::the()->exit();
}

void ApplicationStartScreen::ScreenUpdateListener::update(const UpdateEvent& e)
{
    _ApplicationStartScreen->updateAnimation(e.getElapsedTime());
}
