/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#define KE_COMPILEKABALAENGINELIB

#include "KEConfig.h"

#include "KEAboutKEWindow.h"

#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>
#include <OpenSG/OSGGL.h>

KE_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                            methods                                 *
\***************************************************************************/

InternalWindowPtr openAboutKabalaEngineWindow(UIDrawingSurfacePtr TheDrawingSurface)
{
	InternalWindowPtr AboutWindow = createAboutKabalaEngineWindow();

	TheDrawingSurface->openWindow(AboutWindow);

	return AboutWindow;
}

InternalWindowPtr createAboutKabalaEngineWindow(void)
{
	//Authors
    GridBagLayoutConstraintsPtr AuthorsLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(AuthorsLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        AuthorsLabelConstraints->setGridX(0);
        AuthorsLabelConstraints->setGridY(0);
        AuthorsLabelConstraints->setWeightY(0.0f);
    endEditCP(AuthorsLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr AuthorsLabel = osg::Label::create();
	beginEditCP(AuthorsLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		AuthorsLabel->setText("Authors:");
		AuthorsLabel->setConstraints(AuthorsLabelConstraints);
    endEditCP(AuthorsLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr AuthorsValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(AuthorsValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        AuthorsValueLabelConstraints->setGridX(1);
        AuthorsValueLabelConstraints->setGridY(0);
        AuthorsValueLabelConstraints->setWeightY(0.0f);
    endEditCP(AuthorsValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr AuthorsValueLabel = osg::Label::create();
    beginEditCP(AuthorsValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		AuthorsValueLabel->setText(KE_AUTHORS);
		AuthorsValueLabel->setConstraints(AuthorsValueLabelConstraints);
    endEditCP(AuthorsValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
	
	//Engine Version
    GridBagLayoutConstraintsPtr EngineVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineVersionLabelConstraints->setGridX(0);
        EngineVersionLabelConstraints->setGridY(1);
    endEditCP(EngineVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineVersionLabel = osg::Label::create();
    beginEditCP(EngineVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineVersionLabel->setText("Engine Version:");
		EngineVersionLabel->setConstraints(EngineVersionLabelConstraints);
    endEditCP(EngineVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr EngineVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineVersionValueLabelConstraints->setGridX(1);
        EngineVersionValueLabelConstraints->setGridY(1);
    endEditCP(EngineVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr EngineVersionValueLabel = osg::Label::create();
    beginEditCP(EngineVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineVersionValueLabel->setText(KE_VERSION_STRING);
		EngineVersionValueLabel->setConstraints(EngineVersionValueLabelConstraints);
    endEditCP(EngineVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

	//Builder Version
    GridBagLayoutConstraintsPtr BuilderVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(BuilderVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        BuilderVersionLabelConstraints->setGridX(0);
        BuilderVersionLabelConstraints->setGridY(2);
    endEditCP(BuilderVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr BuilderVersionLabel = osg::Label::create();
    beginEditCP(BuilderVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		BuilderVersionLabel->setText("Builder Version:");
		BuilderVersionLabel->setConstraints(BuilderVersionLabelConstraints);
    endEditCP(BuilderVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr BuilderVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(BuilderVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        BuilderVersionValueLabelConstraints->setGridX(1);
        BuilderVersionValueLabelConstraints->setGridY(2);
    endEditCP(BuilderVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr BuilderVersionValueLabel = osg::Label::create();
    beginEditCP(BuilderVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		BuilderVersionValueLabel->setText(KE_BUILDER_VERSION_STRING);
		BuilderVersionValueLabel->setConstraints(BuilderVersionValueLabelConstraints);
    endEditCP(BuilderVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
	
	//OpenSG Version
    GridBagLayoutConstraintsPtr OpenSGVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenSGVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenSGVersionLabelConstraints->setGridX(0);
        OpenSGVersionLabelConstraints->setGridY(3);
    endEditCP(OpenSGVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenSGVersionLabel = osg::Label::create();
    beginEditCP(OpenSGVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenSGVersionLabel->setText("OpenSG Version:");
		OpenSGVersionLabel->setConstraints(OpenSGVersionLabelConstraints);
    endEditCP(OpenSGVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenSGVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenSGVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenSGVersionValueLabelConstraints->setGridX(1);
        OpenSGVersionValueLabelConstraints->setGridY(3);
    endEditCP(OpenSGVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr OpenSGVersionValueLabel = osg::Label::create();
    beginEditCP(OpenSGVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenSGVersionValueLabel->setText(OSG_VERSION_STRING);
		OpenSGVersionValueLabel->setConstraints(OpenSGVersionValueLabelConstraints);
    endEditCP(OpenSGVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
	
	//OpenGL Version
    GridBagLayoutConstraintsPtr OpenGLVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVersionLabelConstraints->setGridX(0);
        OpenGLVersionLabelConstraints->setGridY(4);
    endEditCP(OpenGLVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVersionLabel = osg::Label::create();
    beginEditCP(OpenGLVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVersionLabel->setText("OpenGL Version:");
		OpenGLVersionLabel->setConstraints(OpenGLVersionLabelConstraints);
    endEditCP(OpenGLVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVersionValueLabelConstraints->setGridX(1);
        OpenGLVersionValueLabelConstraints->setGridY(4);
    endEditCP(OpenGLVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVersionValueLabel = osg::Label::create();
    beginEditCP(OpenGLVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVersionValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
		OpenGLVersionValueLabel->setConstraints(OpenGLVersionValueLabelConstraints);
    endEditCP(OpenGLVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
	
	//OpenGL Vendor
    GridBagLayoutConstraintsPtr OpenGLVendorLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVendorLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVendorLabelConstraints->setGridX(0);
        OpenGLVendorLabelConstraints->setGridY(5);
    endEditCP(OpenGLVendorLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVendorLabel = osg::Label::create();
    beginEditCP(OpenGLVendorLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVendorLabel->setText("OpenGL Vendor:");
		OpenGLVendorLabel->setConstraints(OpenGLVendorLabelConstraints);
    endEditCP(OpenGLVendorLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLVendorValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVendorValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVendorValueLabelConstraints->setGridX(1);
        OpenGLVendorValueLabelConstraints->setGridY(5);
    endEditCP(OpenGLVendorValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVendorValueLabel = osg::Label::create();
    beginEditCP(OpenGLVendorValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVendorValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
		OpenGLVendorValueLabel->setConstraints(OpenGLVendorValueLabelConstraints);
    endEditCP(OpenGLVendorValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
	
	//OpenGL Renderer
    GridBagLayoutConstraintsPtr OpenGLRendererLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLRendererLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLRendererLabelConstraints->setGridX(0);
        OpenGLRendererLabelConstraints->setGridY(6);
    endEditCP(OpenGLRendererLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLRendererLabel = osg::Label::create();
    beginEditCP(OpenGLRendererLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLRendererLabel->setText("OpenGL Renderer:");
		OpenGLRendererLabel->setConstraints(OpenGLRendererLabelConstraints);
    endEditCP(OpenGLRendererLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLRendererValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLRendererValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLRendererValueLabelConstraints->setGridX(1);
        OpenGLRendererValueLabelConstraints->setGridY(6);
    endEditCP(OpenGLRendererValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLRendererValueLabel = osg::Label::create();
    beginEditCP(OpenGLRendererValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLRendererValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		OpenGLRendererValueLabel->setConstraints(OpenGLRendererValueLabelConstraints);
    endEditCP(OpenGLRendererValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

	//Ok ::osg::Button
    GridBagLayoutConstraintsPtr OkButtonLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OkButtonLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridWidthFieldMask);
        OkButtonLabelConstraints->setGridX(0);
        OkButtonLabelConstraints->setGridY(7);
        OkButtonLabelConstraints->setGridWidth(2);
		OkButtonLabelConstraints->setFill(GridBagLayoutConstraints::FILL_NONE);
    endEditCP(OkButtonLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridWidthFieldMask);

    ButtonPtr OkButton = ::osg::Button::create();
    beginEditCP(OkButton, ::osg::Button::TextFieldMask | ::osg::Button::ConstraintsFieldMask);
        OkButton->setText("Ok");
		OkButton->setConstraints(OkButtonLabelConstraints);
    endEditCP(OkButton, ::osg::Button::TextFieldMask | ::osg::Button::ConstraintsFieldMask);

    // Create The Internal Window
    InternalWindowPtr AboutWindow = osg::InternalWindow::create();
    GridBagLayoutPtr MainInternalWindowLayout = osg::GridBagLayout::create();

    beginEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
        MainInternalWindowLayout->setColumns(2);
        MainInternalWindowLayout->setRows(8);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
        MainInternalWindowLayout->getRowWeights().push_back(1.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::AllwaysOnTopFieldMask | InternalWindow::IconableFieldMask | InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);
       // Assign the ::osg::Button to the MainInternalWindow so it will be displayed
       // when the view is rendered.
       AboutWindow->getChildren().push_back(AuthorsLabel);
       AboutWindow->getChildren().push_back(AuthorsValueLabel);
       AboutWindow->getChildren().push_back(EngineVersionLabel);
       AboutWindow->getChildren().push_back(EngineVersionValueLabel);
       AboutWindow->getChildren().push_back(BuilderVersionLabel);
       AboutWindow->getChildren().push_back(BuilderVersionValueLabel);
       AboutWindow->getChildren().push_back(OpenSGVersionLabel);
       AboutWindow->getChildren().push_back(OpenSGVersionValueLabel);
       AboutWindow->getChildren().push_back(OpenGLVersionLabel);
       AboutWindow->getChildren().push_back(OpenGLVersionValueLabel);
       AboutWindow->getChildren().push_back(OpenGLVendorLabel);
       AboutWindow->getChildren().push_back(OpenGLVendorValueLabel);
       AboutWindow->getChildren().push_back(OpenGLRendererLabel);
       AboutWindow->getChildren().push_back(OpenGLRendererValueLabel);
       AboutWindow->getChildren().push_back(OkButton);
       AboutWindow->setLayout(MainInternalWindowLayout);
       AboutWindow->setPosition(Pnt2f(0,0));
       AboutWindow->setPreferredSize(Vec2f(300,300));
	   AboutWindow->setTitle(std::string("About Kabala Engine"));
	   AboutWindow->setIconable(false);
	   AboutWindow->setAllwaysOnTop(true);
    endEditCP(AboutWindow, InternalWindow::AllwaysOnTopFieldMask | InternalWindow::IconableFieldMask | InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);

	return AboutWindow;
}

KE_END_NAMESPACE

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

