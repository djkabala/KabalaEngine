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

#include "KEBuilderInterface.h"
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGMenuBar.h>
#include <OpenSG/UserInterface/OSGToolbar.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGMenuItem.h>
#include <OpenSG/Input/OSGWindowEventProducer.h>

#include "Builder/UserInterface/Statusbar/KEStatusbar.h"
#include "Builder/UserInterface/SceneEditor/KESceneEditor.h"
#include "Builder/KEApplicationBuilder.h"

#include "Project/KEProject.h"

#include "Builder/UserInterface/Commands/KENewProjectCommand.h"
#include "Builder/UserInterface/Commands/KEOpenProjectCommand.h"
#include "Builder/UserInterface/Commands/KECloseProjectCommand.h"
#include "Builder/UserInterface/Commands/KESaveProjectCommand.h"
#include "Builder/UserInterface/Commands/KESaveProjectAsCommand.h"
#include "Builder/UserInterface/Commands/KEStartScreenCommand.h"
#include "Builder/UserInterface/Commands/KEPlayProjectCommand.h"
#include "Builder/UserInterface/Commands/KEQuitAppCommand.h"
#include "Builder/UserInterface/Commands/KEUndoCommand.h"
#include "Builder/UserInterface/Commands/KERedoCommand.h"
#include "Builder/UserInterface/Commands/KEAboutKabalaEngineCommand.h"
#include <OpenSG/UserInterface/OSGCommandManager.h>
KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BuilderInterface
The BuilderInterface.         
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const std::string BuilderInterface::_PresentationName("Builder");
const std::string BuilderInterface::_PresentationIconName("Builder");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BuilderInterface::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


const std::string& BuilderInterface::getPresentationName(void) const
{
	return _PresentationName;
}

const std::string& BuilderInterface::getPresentationIconName(void) const
{
	return _PresentationIconName;
}

void BuilderInterface::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	SpringLayoutPtr BuilderInterfaceLayout = SpringLayout::create();
	beginEditCP(BuilderInterfacePtr(this), BuilderInterface::MenuBarFieldMask | BuilderInterface::ToolbarFieldId | BuilderInterface::StatusbarFieldMask | BuilderInterface::MainInternalWindowFieldMask | BuilderInterface::DrawingSurfaceFieldMask | BuilderInterface::ChildrenFieldMask | BuilderInterface::LayoutFieldMask);
		setMenuBar(MenuBar::create());
		setToolbar(Toolbar::create());
		setEditor(SceneEditor::create());
		setStatusbar(Statusbar::create());
		setMainInternalWindow(osg::InternalWindow::create());
		setDrawingSurface(UIDrawingSurface::create());
		getChildren().clear();
		getChildren().push_back(getToolbar());
        getChildren().push_back(getStatusbar());
        getChildren().push_back(getEditor());
		setLayout(BuilderInterfaceLayout);
    endEditCP(BuilderInterfacePtr(this), BuilderInterface::MenuBarFieldMask | BuilderInterface::ToolbarFieldId | BuilderInterface::StatusbarFieldMask | BuilderInterface::MainInternalWindowFieldMask | BuilderInterface::DrawingSurfaceFieldMask | BuilderInterface::ChildrenFieldMask | BuilderInterface::LayoutFieldMask);

	//Editor
	getEditor()->createInterface(TheApplicationBuilder);

	//Menubar
    _NewProjectMenuItem = MenuItem::create();
    _OpenProjectMenuItem = MenuItem::create();
    _CloseProjectMenuItem = MenuItem::create();
    _SaveProjectMenuItem = MenuItem::create();
    _SaveProjectAsMenuItem = MenuItem::create();
    _PlayProjectMenuItem = MenuItem::create();
    _StartScreenMenuItem = MenuItem::create();
    _ExitMenuItem = MenuItem::create();


    _UndoMenuItem = MenuItem::create();
    _RedoMenuItem = MenuItem::create();
    _CutMenuItem = MenuItem::create();
    _CopyMenuItem = MenuItem::create();
    _PasteMenuItem = MenuItem::create();
    _DeleteMenuItem = MenuItem::create();
	
    _AboutKEMenuItem = MenuItem::create();

    //File MenuItems
    beginEditCP(_NewProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _NewProjectMenuItem->setText("New Project ...");
        _NewProjectMenuItem->setAcceleratorKey(KeyEvent::KEY_N);
        _NewProjectMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _NewProjectMenuItem->setMnemonicKey(KeyEvent::KEY_N);
    endEditCP(_NewProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(_OpenProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _OpenProjectMenuItem->setText("Open Project ...");
        _OpenProjectMenuItem->setAcceleratorKey(KeyEvent::KEY_O);
        _OpenProjectMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _OpenProjectMenuItem->setMnemonicKey(KeyEvent::KEY_O);
    endEditCP(_OpenProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(_CloseProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _CloseProjectMenuItem->setText("Close Project ...");
        _CloseProjectMenuItem->setAcceleratorKey(KeyEvent::KEY_W);
        _CloseProjectMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _CloseProjectMenuItem->setMnemonicKey(KeyEvent::KEY_C);
    endEditCP(_CloseProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_SaveProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _SaveProjectMenuItem->setText("Save Project ...");
        _SaveProjectMenuItem->setAcceleratorKey(KeyEvent::KEY_S);
        _SaveProjectMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _SaveProjectMenuItem->setMnemonicKey(KeyEvent::KEY_S);
    endEditCP(_SaveProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	beginEditCP(_SaveProjectAsMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _SaveProjectAsMenuItem->setText("Save Project As ...");
        _SaveProjectAsMenuItem->setAcceleratorKey(KeyEvent::KEY_S);
        _SaveProjectAsMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_SHIFT);
        _SaveProjectAsMenuItem->setMnemonicKey(KeyEvent::KEY_A);
    endEditCP(_SaveProjectAsMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_PlayProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _PlayProjectMenuItem->setText("Play Project");
        _PlayProjectMenuItem->setAcceleratorKey(KeyEvent::KEY_P);
        _PlayProjectMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _PlayProjectMenuItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(_PlayProjectMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    
	beginEditCP(_StartScreenMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _StartScreenMenuItem->setText("Go To Start Screen");
        _StartScreenMenuItem->setMnemonicKey(KeyEvent::KEY_T);
    endEditCP(_StartScreenMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(_ExitMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _ExitMenuItem->setText("Quit");
        _ExitMenuItem->setAcceleratorKey(KeyEvent::KEY_Q);
        _ExitMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _ExitMenuItem->setMnemonicKey(KeyEvent::KEY_Q);
    endEditCP(_ExitMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);

	//Edit
    beginEditCP(_UndoMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
        _UndoMenuItem->setText("Undo");
        _UndoMenuItem->setAcceleratorKey(KeyEvent::KEY_Z);
        _UndoMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _UndoMenuItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(_UndoMenuItem, MenuItem::TextFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask | MenuItem::MnemonicKeyFieldMask);
    beginEditCP(_RedoMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
        _RedoMenuItem->setText("Redo");
        _RedoMenuItem->setAcceleratorKey(KeyEvent::KEY_Z);
        _RedoMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL |KeyEvent::KEY_MODIFIER_SHIFT);
        _RedoMenuItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(_RedoMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
    
	beginEditCP(_CutMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
        _CutMenuItem->setText("Cut");
        _CutMenuItem->setAcceleratorKey(KeyEvent::KEY_X);
        _CutMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _CutMenuItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(_CutMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
    
	beginEditCP(_CopyMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
        _CopyMenuItem->setText("Copy");
        _CopyMenuItem->setAcceleratorKey(KeyEvent::KEY_C);
        _CopyMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _CopyMenuItem->setMnemonicKey(KeyEvent::KEY_C);
    endEditCP(_CopyMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
    
	beginEditCP(_PasteMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
        _PasteMenuItem->setText("Paste");
        _PasteMenuItem->setAcceleratorKey(KeyEvent::KEY_V);
        _PasteMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _PasteMenuItem->setMnemonicKey(KeyEvent::KEY_P);
    endEditCP(_PasteMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
    
	beginEditCP(_DeleteMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);
        _DeleteMenuItem->setText("Delete");
        _DeleteMenuItem->setAcceleratorKey(KeyEvent::KEY_D);
        _DeleteMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        _DeleteMenuItem->setMnemonicKey(KeyEvent::KEY_D);
    endEditCP(_DeleteMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask | MenuItem::AcceleratorKeyFieldMask | MenuItem::AcceleratorModifiersFieldMask);

	//Help
	beginEditCP(_AboutKEMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _AboutKEMenuItem->setText("About Kabala Engine");
        _AboutKEMenuItem->setMnemonicKey(KeyEvent::KEY_A);
    endEditCP(_AboutKEMenuItem, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);

    // Create a File menu and adds its MenuItems
    _FileMenu = Menu::create();
    _FileMenu->addItem(_NewProjectMenuItem);
    _FileMenu->addItem(_OpenProjectMenuItem);
    _FileMenu->addItem(_CloseProjectMenuItem);
    _FileMenu->addSeparator();
    _FileMenu->addItem(_SaveProjectMenuItem);
    _FileMenu->addItem(_SaveProjectAsMenuItem);
    _FileMenu->addSeparator();
    _FileMenu->addItem(_PlayProjectMenuItem);
    _FileMenu->addItem(_StartScreenMenuItem);
    _FileMenu->addSeparator();
    _FileMenu->addItem(_ExitMenuItem);

    // Labels the File Menu
    beginEditCP(_FileMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _FileMenu->setText("File");
        _FileMenu->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(_FileMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    
    // Creates an Edit menu and adds its MenuItems
    _EditMenu = Menu::create();
    // Labels the Edit Menu
    beginEditCP(_EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _EditMenu->setText("Edit");
        _EditMenu->setMnemonicKey(KeyEvent::KEY_E);
    endEditCP(_EditMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    _EditMenu->addItem(_UndoMenuItem);
    _EditMenu->addItem(_RedoMenuItem);
    _EditMenu->addSeparator();
    _EditMenu->addItem(_CutMenuItem);
    _EditMenu->addItem(_CopyMenuItem);
    _EditMenu->addItem(_PasteMenuItem);
    _EditMenu->addItem(_DeleteMenuItem);

	//Help
    _HelpMenu = Menu::create();
    // Labels the Edit Menu
    beginEditCP(_HelpMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
        _HelpMenu->setText("Help");
        _HelpMenu->setMnemonicKey(KeyEvent::KEY_H);
    endEditCP(_HelpMenu, MenuItem::TextFieldMask | MenuItem::MnemonicKeyFieldMask);
    _HelpMenu->addItem(_AboutKEMenuItem);

    getMenuBar()->addMenu(_FileMenu);
    getMenuBar()->addMenu(_EditMenu);
    getMenuBar()->addMenu(_HelpMenu);


	//Toolbar
	_UndoButton = TheApplicationBuilder->getIconManager()->createButton("EditUndo", Vec2f(33.0f,33.0f));
	beginEditCP(_UndoButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);
		_UndoButton->setPreferredSize(Vec2f(37.0f,37.0f));
		_UndoButton->setToolTipText("Undo");
	endEditCP(_UndoButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);

	_RedoButton = TheApplicationBuilder->getIconManager()->createButton("EditRedo", Vec2f(33.0f,33.0f));
	beginEditCP(_RedoButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);
		_RedoButton->setPreferredSize(Vec2f(37.0f,37.0f));
		_RedoButton->setToolTipText("Redo");
	endEditCP(_RedoButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);

	_OpenProjectButton = TheApplicationBuilder->getIconManager()->createButton("OpenProject", Vec2f(33.0f,33.0f));
	beginEditCP(_OpenProjectButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);
		_OpenProjectButton->setPreferredSize(Vec2f(37.0f,37.0f));
		_OpenProjectButton->setToolTipText("Open Project");
	endEditCP(_OpenProjectButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);

	_SaveProjectButton = TheApplicationBuilder->getIconManager()->createButton("SaveProject", Vec2f(33.0f,33.0f));
	beginEditCP(_SaveProjectButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);
		_SaveProjectButton->setPreferredSize(Vec2f(37.0f,37.0f));
		_SaveProjectButton->setToolTipText("Save Project");
	endEditCP(_SaveProjectButton, ::osg::Button::PreferredSizeFieldMask | ::osg::Button::ToolTipTextFieldMask);

	beginEditCP(getToolbar(), Toolbar::PreferredSizeFieldMask);
		getToolbar()->setPreferredSize(Vec2f(37.0f,37.0f));
    endEditCP(getToolbar(),Toolbar::PreferredSizeFieldMask);
	getToolbar()->addTool(_UndoButton);
	getToolbar()->addTool(_RedoButton);
	getToolbar()->addTool(_OpenProjectButton);
	getToolbar()->addTool(_SaveProjectButton);
	getToolbar()->addSeparator();

	//Editors

	//Statusbar
	getStatusbar()->createInterface(TheApplicationBuilder);

	//Border
	BevelBorderPtr StatusbarBorder = BevelBorder::create();
	beginEditCP(StatusbarBorder);
		StatusbarBorder->setRaised(false);
		StatusbarBorder->setWidth(2);
	endEditCP(StatusbarBorder);

	//Background
	beginEditCP(getStatusbar(), Statusbar::PreferredSizeFieldMask | Statusbar::BackgroundsFieldMask | Statusbar::BordersFieldMask);
		getStatusbar()->setPreferredSize(Vec2f(20.0f,20.0f));
		getStatusbar()->setBackgrounds(getToolbar()->getBackground());
		getStatusbar()->setBorders(StatusbarBorder);
    endEditCP(getStatusbar(),Statusbar::PreferredSizeFieldMask | Statusbar::BackgroundsFieldMask | Statusbar::BordersFieldMask);

	//Layout
	//Toolbar
    BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, getToolbar(), 0, SpringLayoutConstraints::WEST_EDGE, BuilderInterfacePtr(this));
    BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, getToolbar(), 0, SpringLayoutConstraints::EAST_EDGE, BuilderInterfacePtr(this));
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, getToolbar(), 0, SpringLayoutConstraints::NORTH_EDGE, BuilderInterfacePtr(this));
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, getToolbar(), LayoutSpring::height(getToolbar()));

	//Editor
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, getEditor(), 0, SpringLayoutConstraints::WEST_EDGE, BuilderInterfacePtr(this));
    BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, getEditor(), 0, SpringLayoutConstraints::EAST_EDGE, BuilderInterfacePtr(this));
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, getEditor(), 0, SpringLayoutConstraints::SOUTH_EDGE, getToolbar());
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, getEditor(), 0, SpringLayoutConstraints::NORTH_EDGE, getStatusbar());

	//Statusbar
    BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, getStatusbar(), 0, SpringLayoutConstraints::WEST_EDGE, BuilderInterfacePtr(this));
    BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, getStatusbar(), 0, SpringLayoutConstraints::EAST_EDGE, BuilderInterfacePtr(this));
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, getStatusbar(), 0, SpringLayoutConstraints::SOUTH_EDGE, BuilderInterfacePtr(this));
	BuilderInterfaceLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, getStatusbar(), LayoutSpring::height(getStatusbar()));

	SpringLayoutPtr MainInternalWindowLayout = SpringLayout::create();
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, BuilderInterfacePtr(this), 0, SpringLayoutConstraints::WEST_EDGE, getMainInternalWindow());
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, BuilderInterfacePtr(this), 0, SpringLayoutConstraints::EAST_EDGE, getMainInternalWindow());
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, BuilderInterfacePtr(this), 0, SpringLayoutConstraints::NORTH_EDGE, getMainInternalWindow());
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, BuilderInterfacePtr(this), 0, SpringLayoutConstraints::SOUTH_EDGE, getMainInternalWindow());

	/*
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
	*/
	
	LayerPtr MainInternalWindowBackground;

    //Initialize The Main InternalWindow
	beginEditCP(getMainInternalWindow(), InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::DrawDecorationsFieldMask | InternalWindow::ResizableFieldMask | InternalWindow::MenuBarFieldMask);
       getMainInternalWindow()->getChildren().push_back(BuilderInterfacePtr(this));
       getMainInternalWindow()->setLayout(MainInternalWindowLayout);
       getMainInternalWindow()->setBackgrounds(MainInternalWindowBackground);
       getMainInternalWindow()->setBorders(NullFC);
	   getMainInternalWindow()->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   getMainInternalWindow()->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   getMainInternalWindow()->setDrawTitlebar(false);
	   getMainInternalWindow()->setDrawDecorations(true);
	   getMainInternalWindow()->setResizable(false);
       getMainInternalWindow()->setMenuBar(getMenuBar());
    endEditCP(getMainInternalWindow(), InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::DrawDecorationsFieldMask | InternalWindow::ResizableFieldMask | InternalWindow::MenuBarFieldMask);

    //Initialize the Drawing Surface
    beginEditCP(getDrawingSurface(), UIDrawingSurface::GraphicsFieldMask);
        getDrawingSurface()->setGraphics(osg::Graphics2D::create());
    endEditCP(getDrawingSurface(), UIDrawingSurface::GraphicsFieldMask);
    
	getDrawingSurface()->openWindow(getMainInternalWindow());
}

void BuilderInterface::addToolbarTools(const std::vector<ComponentPtr>& Tools)
{
    for(::osg::UInt32 i(0) ; i<Tools.size() ; ++i)
    {
        getToolbar()->addTool(Tools[i]);
    }
}

void BuilderInterface::removeToolbarTools(const std::vector<ComponentPtr>& Tools)
{
    for(::osg::UInt32 i(0) ; i<Tools.size() ; ++i)
    {
        getToolbar()->removeTool(Tools[i]);
    }
}

void BuilderInterface::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//ActionListeners
	_NewProjectActionListener = CommandActionListener(NewProjectCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_OpenProjectActionListener = CommandActionListener(OpenProjectCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_CloseProjectActionListener = CommandActionListener(CloseProjectCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_SaveProjectActionListener = CommandActionListener(SaveProjectCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_SaveProjectAsActionListener = CommandActionListener(SaveProjectAsCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_PlayProjectListener = CommandActionListener(PlayProjectCommand::create(TheApplicationBuilder->getParentApplication()), TheApplicationBuilder->getCommandManager());
	_StartScreenListener = CommandActionListener(StartScreenCommand::create(TheApplicationBuilder->getParentApplication()), TheApplicationBuilder->getCommandManager());
	_QuitActionListener = CommandActionListener(QuitAppCommand::create(TheApplicationBuilder->getParentApplication()), TheApplicationBuilder->getCommandManager());
	_UndoActionListener = CommandActionListener(UndoCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_RedoActionListener = CommandActionListener(RedoCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());
	_AboutKabalaEngineActionListener = CommandActionListener(AboutKabalaEngineCommand::create(TheApplicationBuilder), TheApplicationBuilder->getCommandManager());

	//Menu Connections
	_NewProjectMenuItem->addActionListener(&_NewProjectActionListener);
	_OpenProjectMenuItem->addActionListener(&_OpenProjectActionListener);
	_CloseProjectMenuItem->addActionListener(&_CloseProjectActionListener);
	_SaveProjectMenuItem->addActionListener(&_SaveProjectActionListener);
	_SaveProjectAsMenuItem->addActionListener(&_SaveProjectAsActionListener);
	_PlayProjectMenuItem->addActionListener(&_PlayProjectListener);
	_StartScreenMenuItem->addActionListener(&_StartScreenListener);
	_ExitMenuItem->addActionListener(&_QuitActionListener);
	_UndoMenuItem->addActionListener(&_UndoActionListener);
	_RedoMenuItem->addActionListener(&_RedoActionListener);
	_AboutKEMenuItem->addActionListener(&_AboutKabalaEngineActionListener);

	//Toolbar
	_UndoButton->addActionListener(&_UndoActionListener);
	_RedoButton->addActionListener(&_RedoActionListener);
	_OpenProjectButton->addActionListener(&_OpenProjectActionListener);
	_SaveProjectButton->addActionListener(&_SaveProjectActionListener);

	updateUndoRedoInterfaces(TheApplicationBuilder->getUndoManager());

	//Main Window Titlebar
	ProjectPtr TheProject(TheApplicationBuilder->getParentApplication()->getProject());
	std::string MainWindowTitle(TheProject->getName() + " -  Kabala Engine Builder");
	TheApplicationBuilder->getParentApplication()->getMainWindowEventProducer()->setTitle(MainWindowTitle);

	//Editor
	getEditor()->connectInterface(TheApplicationBuilder);

	_CommandManagerListener.setApplicationBuilder(TheApplicationBuilder);
}

void BuilderInterface::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Editor
	getEditor()->disconnectInterface(TheApplicationBuilder);
}

void BuilderInterface::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Editor
	getEditor()->updateInterface(TheApplicationBuilder);
}

void BuilderInterface::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Editor
	getEditor()->destroyInterface(TheApplicationBuilder);
}

void BuilderInterface::updateUndoRedoInterfaces(UndoManagerPtr TheUndoManager)
{
	beginEditCP(_UndoButton, ::osg::Button::EnabledFieldMask);
		_UndoButton->setEnabled(TheUndoManager->canUndo());
	endEditCP(_UndoButton, ::osg::Button::EnabledFieldMask);
	beginEditCP(_UndoMenuItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
		_UndoMenuItem->setEnabled(TheUndoManager->canUndo());
		if(TheUndoManager->canUndo())
		{
			_UndoMenuItem->setText(TheUndoManager->getUndoPresentationName());
		}
		else
		{
			_UndoMenuItem->setText("Undo");
		}
	endEditCP(_UndoMenuItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
	
	beginEditCP(_RedoButton, ::osg::Button::EnabledFieldMask | MenuItem::TextFieldMask);
		_RedoButton->setEnabled(TheUndoManager->canRedo());
	endEditCP(_RedoButton, ::osg::Button::EnabledFieldMask);
	beginEditCP(_RedoMenuItem, MenuItem::EnabledFieldMask);
		_RedoMenuItem->setEnabled(TheUndoManager->canRedo());
		if(TheUndoManager->canRedo())
		{
			_RedoMenuItem->setText(TheUndoManager->getRedoPresentationName());
		}
		else
		{
			_RedoMenuItem->setText("Redo");
		}
	endEditCP(_RedoMenuItem, MenuItem::EnabledFieldMask | MenuItem::TextFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BuilderInterface::BuilderInterface(void) :
    Inherited(),
	_NewProjectActionListener(NULL,NULL),
	_OpenProjectActionListener(NULL,NULL),
	_CloseProjectActionListener(NULL,NULL),
	_SaveProjectActionListener(NULL,NULL),
	_SaveProjectAsActionListener(NULL,NULL),
	_PlayProjectListener(NULL,NULL),
	_StartScreenListener(NULL,NULL),
	_QuitActionListener(NULL,NULL),
	_UndoActionListener(NULL,NULL),
	_RedoActionListener(NULL,NULL),
	_AboutKabalaEngineActionListener(NULL,NULL),
	_CommandManagerListener(BuilderInterfacePtr(this))
{
}

BuilderInterface::BuilderInterface(const BuilderInterface &source) :
    Inherited(source),
	_NewProjectActionListener(NULL,NULL),
	_OpenProjectActionListener(NULL,NULL),
	_CloseProjectActionListener(NULL,NULL),
	_SaveProjectActionListener(NULL,NULL),
	_SaveProjectAsActionListener(NULL,NULL),
	_PlayProjectListener(NULL,NULL),
	_StartScreenListener(NULL,NULL),
	_QuitActionListener(NULL,NULL),
	_UndoActionListener(NULL,NULL),
	_RedoActionListener(NULL,NULL),
	_AboutKabalaEngineActionListener(NULL,NULL),
	_CommandManagerListener(BuilderInterfacePtr(this))
{
}

BuilderInterface::~BuilderInterface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BuilderInterface::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BuilderInterface::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BuilderInterface NI" << std::endl;
}

void BuilderInterface::CommandManagerListener::stateChanged(const ChangeEvent& e)
{
	_BuilderInterface->updateUndoRedoInterfaces(_ApplicationBuilder->getUndoManager());
}

void BuilderInterface::CommandManagerListener::setApplicationBuilder(ApplicationBuilderPtr TheApplicationBuilder)
{
    _ApplicationBuilder = TheApplicationBuilder;
	_ApplicationBuilder->getUndoManager()->addChangeListener(this);
}
