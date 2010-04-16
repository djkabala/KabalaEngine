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

#include <OpenSG/OSGConfig.h>
#include "KEConfig.h"

#include "KEAboutKEWindow.h"

#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>
#include "Builder/UserInterface/IconManager/KEIconManager.h"
#include "Builder/KEApplicationBuilder.h"
#include "Application/KEMainApplication.h"

#include <ode/ode.h>
#include <lua.hpp>
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

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
    // Create The Internal Window
    InternalWindowPtr AboutWindow = osg::InternalWindow::create();
    GridBagLayoutPtr MainInternalWindowLayout = osg::GridBagLayout::create();

    beginEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask);
        MainInternalWindowLayout->setColumns(3);

        MainInternalWindowLayout->getColumnWidths().push_back(20.0f);
        MainInternalWindowLayout->getColumnWeights().push_back(0.0f);

        MainInternalWindowLayout->getColumnWidths().push_back(150.0f);
        MainInternalWindowLayout->getColumnWeights().push_back(0.0f);

        MainInternalWindowLayout->getColumnWeights().push_back(1.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::AllwaysOnTopFieldMask | InternalWindow::IconableFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);
       AboutWindow->setLayout(MainInternalWindowLayout);
       AboutWindow->setPosition(Pnt2f(0,0));
       AboutWindow->setPreferredSize(Vec2f(500,500));
	   AboutWindow->setTitle(std::string("About Kabala Engine"));
	   AboutWindow->setIconable(false);
	   AboutWindow->setAllwaysOnTop(true);
    endEditCP(AboutWindow, InternalWindow::AllwaysOnTopFieldMask | InternalWindow::IconableFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);

    UInt32 Row(0);
	
	//Logo
    GridBagLayoutConstraintsPtr EngineLogoLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineLogoLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineLogoLabelConstraints->setGridX(0);
        EngineLogoLabelConstraints->setGridY(Row);
        EngineLogoLabelConstraints->setGridWidth(3);
    endEditCP(EngineLogoLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    ImageComponentPtr EngineLogo =
        ApplicationBuilder::Ptr::dcast(MainApplication::the()->getBuilderMode())->getIconManager()->createIconImageComponent("Logo");
    beginEditCP(EngineLogo);
		EngineLogo->setAlignment(Vec2f(0.5f,0.5f));
    endEditCP(EngineLogo);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(60.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineLogo);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Authors
    GridBagLayoutConstraintsPtr AuthorsLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(AuthorsLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        AuthorsLabelConstraints->setGridX(0);
        AuthorsLabelConstraints->setGridY(Row);
        AuthorsLabelConstraints->setWeightY(0.0f);
        AuthorsLabelConstraints->setGridWidth(2);
    endEditCP(AuthorsLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr AuthorsLabel = osg::Label::create();
	beginEditCP(AuthorsLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		AuthorsLabel->setText("Authors:");
		AuthorsLabel->setConstraints(AuthorsLabelConstraints);
    endEditCP(AuthorsLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr AuthorsValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(AuthorsValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        AuthorsValueLabelConstraints->setGridX(2);
        AuthorsValueLabelConstraints->setGridY(Row);
        AuthorsValueLabelConstraints->setWeightY(0.0f);
    endEditCP(AuthorsValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr AuthorsValueLabel = osg::Label::create();
    beginEditCP(AuthorsValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		AuthorsValueLabel->setText(getKabalaEngineAuthors());
		AuthorsValueLabel->setConstraints(AuthorsValueLabelConstraints);
    endEditCP(AuthorsValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(AuthorsLabel);
       AboutWindow->getChildren().push_back(AuthorsValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//Versioning
    GridBagLayoutConstraintsPtr EngineVersioningLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineVersioningLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineVersioningLabelConstraints->setGridX(0);
        EngineVersioningLabelConstraints->setGridY(Row);
        EngineVersioningLabelConstraints->setGridWidth(3);
    endEditCP(EngineVersioningLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineVersioningLabel = osg::Label::create();
    beginEditCP(EngineVersioningLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineVersioningLabel->setText("Engine");
		EngineVersioningLabel->setConstraints(EngineVersioningLabelConstraints);
    endEditCP(EngineVersioningLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineVersioningLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Engine Version
    GridBagLayoutConstraintsPtr EngineVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineVersionLabelConstraints->setGridX(1);
        EngineVersionLabelConstraints->setGridY(Row);
    endEditCP(EngineVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineVersionLabel = osg::Label::create();
    beginEditCP(EngineVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineVersionLabel->setText("Version:");
		EngineVersionLabel->setConstraints(EngineVersionLabelConstraints);
    endEditCP(EngineVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr EngineVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineVersionValueLabelConstraints->setGridX(2);
        EngineVersionValueLabelConstraints->setGridY(Row);
    endEditCP(EngineVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr EngineVersionValueLabel = osg::Label::create();
    beginEditCP(EngineVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineVersionValueLabel->setText(getKabalaEngineVersion());
		EngineVersionValueLabel->setConstraints(EngineVersionValueLabelConstraints);
    endEditCP(EngineVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineVersionLabel);
       AboutWindow->getChildren().push_back(EngineVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Engine RepositoryRevision
    GridBagLayoutConstraintsPtr EngineRepositoryRevisionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineRepositoryRevisionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineRepositoryRevisionLabelConstraints->setGridX(1);
        EngineRepositoryRevisionLabelConstraints->setGridY(Row);
    endEditCP(EngineRepositoryRevisionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineRepositoryRevisionLabel = osg::Label::create();
    beginEditCP(EngineRepositoryRevisionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineRepositoryRevisionLabel->setText("Repository Revision:");
		EngineRepositoryRevisionLabel->setConstraints(EngineRepositoryRevisionLabelConstraints);
    endEditCP(EngineRepositoryRevisionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr EngineRepositoryRevisionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineRepositoryRevisionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineRepositoryRevisionValueLabelConstraints->setGridX(2);
        EngineRepositoryRevisionValueLabelConstraints->setGridY(Row);
    endEditCP(EngineRepositoryRevisionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr EngineRepositoryRevisionValueLabel = osg::Label::create();
    beginEditCP(EngineRepositoryRevisionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineRepositoryRevisionValueLabel->setText(getKabalaEngineBuildRepositoryRevision());
		EngineRepositoryRevisionValueLabel->setConstraints(EngineRepositoryRevisionValueLabelConstraints);
    endEditCP(EngineRepositoryRevisionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineRepositoryRevisionLabel);
       AboutWindow->getChildren().push_back(EngineRepositoryRevisionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Engine BuildType
    GridBagLayoutConstraintsPtr EngineBuildTypeLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineBuildTypeLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineBuildTypeLabelConstraints->setGridX(1);
        EngineBuildTypeLabelConstraints->setGridY(Row);
    endEditCP(EngineBuildTypeLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineBuildTypeLabel = osg::Label::create();
    beginEditCP(EngineBuildTypeLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineBuildTypeLabel->setText("Build Type:");
		EngineBuildTypeLabel->setConstraints(EngineBuildTypeLabelConstraints);
    endEditCP(EngineBuildTypeLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr EngineBuildTypeValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineBuildTypeValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineBuildTypeValueLabelConstraints->setGridX(2);
        EngineBuildTypeValueLabelConstraints->setGridY(Row);
    endEditCP(EngineBuildTypeValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr EngineBuildTypeValueLabel = osg::Label::create();
    beginEditCP(EngineBuildTypeValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineBuildTypeValueLabel->setText(getKabalaEngineBuildType());
		EngineBuildTypeValueLabel->setConstraints(EngineBuildTypeValueLabelConstraints);
    endEditCP(EngineBuildTypeValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineBuildTypeLabel);
       AboutWindow->getChildren().push_back(EngineBuildTypeValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Builder Version
    GridBagLayoutConstraintsPtr BuilderVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(BuilderVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        BuilderVersionLabelConstraints->setGridX(1);
        BuilderVersionLabelConstraints->setGridY(Row);
    endEditCP(BuilderVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr BuilderVersionLabel = osg::Label::create();
    beginEditCP(BuilderVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		BuilderVersionLabel->setText("Builder Version:");
		BuilderVersionLabel->setConstraints(BuilderVersionLabelConstraints);
    endEditCP(BuilderVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr BuilderVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(BuilderVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        BuilderVersionValueLabelConstraints->setGridX(2);
        BuilderVersionValueLabelConstraints->setGridY(Row);
    endEditCP(BuilderVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr BuilderVersionValueLabel = osg::Label::create();
    beginEditCP(BuilderVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		BuilderVersionValueLabel->setText(getKabalaEngineBuilderVersion());
		BuilderVersionValueLabel->setConstraints(BuilderVersionValueLabelConstraints);
    endEditCP(BuilderVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(BuilderVersionLabel);
       AboutWindow->getChildren().push_back(BuilderVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//OpenSG
    GridBagLayoutConstraintsPtr OpenSGLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenSGLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenSGLabelConstraints->setGridX(0);
        OpenSGLabelConstraints->setGridY(Row);
        OpenSGLabelConstraints->setGridWidth(3);
    endEditCP(OpenSGLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenSGLabel = osg::Label::create();
    beginEditCP(OpenSGLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenSGLabel->setText("OpenSG");
		OpenSGLabel->setConstraints(OpenSGLabelConstraints);
    endEditCP(OpenSGLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OpenSGLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//OpenSG Version
    GridBagLayoutConstraintsPtr OpenSGVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenSGVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenSGVersionLabelConstraints->setGridX(1);
        OpenSGVersionLabelConstraints->setGridY(Row);
    endEditCP(OpenSGVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenSGVersionLabel = osg::Label::create();
    beginEditCP(OpenSGVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenSGVersionLabel->setText("Version:");
		OpenSGVersionLabel->setConstraints(OpenSGVersionLabelConstraints);
    endEditCP(OpenSGVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenSGVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenSGVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenSGVersionValueLabelConstraints->setGridX(2);
        OpenSGVersionValueLabelConstraints->setGridY(Row);
    endEditCP(OpenSGVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr OpenSGVersionValueLabel = osg::Label::create();
    beginEditCP(OpenSGVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenSGVersionValueLabel->setText(OSG_VERSION_STRING);
		OpenSGVersionValueLabel->setConstraints(OpenSGVersionValueLabelConstraints);
    endEditCP(OpenSGVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OpenSGVersionLabel);
       AboutWindow->getChildren().push_back(OpenSGVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//OpenGL
    GridBagLayoutConstraintsPtr EngineOpenGLLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineOpenGLLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineOpenGLLabelConstraints->setGridX(0);
        EngineOpenGLLabelConstraints->setGridY(Row);
        EngineOpenGLLabelConstraints->setGridWidth(3);
    endEditCP(EngineOpenGLLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineOpenGLLabel = osg::Label::create();
    beginEditCP(EngineOpenGLLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineOpenGLLabel->setText("OpenGL");
		EngineOpenGLLabel->setConstraints(EngineOpenGLLabelConstraints);
    endEditCP(EngineOpenGLLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineOpenGLLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//OpenGL Version
    GridBagLayoutConstraintsPtr OpenGLVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVersionLabelConstraints->setGridX(1);
        OpenGLVersionLabelConstraints->setGridY(Row);
    endEditCP(OpenGLVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVersionLabel = osg::Label::create();
    beginEditCP(OpenGLVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVersionLabel->setText("Version:");
		OpenGLVersionLabel->setConstraints(OpenGLVersionLabelConstraints);
    endEditCP(OpenGLVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVersionValueLabelConstraints->setGridX(2);
        OpenGLVersionValueLabelConstraints->setGridY(Row);
    endEditCP(OpenGLVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVersionValueLabel = osg::Label::create();
    beginEditCP(OpenGLVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVersionValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
		OpenGLVersionValueLabel->setConstraints(OpenGLVersionValueLabelConstraints);
    endEditCP(OpenGLVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OpenGLVersionLabel);
       AboutWindow->getChildren().push_back(OpenGLVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//OpenGL Vendor
    GridBagLayoutConstraintsPtr OpenGLVendorLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVendorLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVendorLabelConstraints->setGridX(1);
        OpenGLVendorLabelConstraints->setGridY(Row);
    endEditCP(OpenGLVendorLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVendorLabel = osg::Label::create();
    beginEditCP(OpenGLVendorLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVendorLabel->setText("Vendor:");
		OpenGLVendorLabel->setConstraints(OpenGLVendorLabelConstraints);
    endEditCP(OpenGLVendorLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLVendorValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLVendorValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLVendorValueLabelConstraints->setGridX(2);
        OpenGLVendorValueLabelConstraints->setGridY(Row);
    endEditCP(OpenGLVendorValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLVendorValueLabel = osg::Label::create();
    beginEditCP(OpenGLVendorValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLVendorValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));
		OpenGLVendorValueLabel->setConstraints(OpenGLVendorValueLabelConstraints);
    endEditCP(OpenGLVendorValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OpenGLVendorLabel);
       AboutWindow->getChildren().push_back(OpenGLVendorValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//OpenGL Renderer
    GridBagLayoutConstraintsPtr OpenGLRendererLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLRendererLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLRendererLabelConstraints->setGridX(1);
        OpenGLRendererLabelConstraints->setGridY(Row);
    endEditCP(OpenGLRendererLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLRendererLabel = osg::Label::create();
    beginEditCP(OpenGLRendererLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLRendererLabel->setText("Renderer:");
		OpenGLRendererLabel->setConstraints(OpenGLRendererLabelConstraints);
    endEditCP(OpenGLRendererLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr OpenGLRendererValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OpenGLRendererValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        OpenGLRendererValueLabelConstraints->setGridX(2);
        OpenGLRendererValueLabelConstraints->setGridY(Row);
    endEditCP(OpenGLRendererValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr OpenGLRendererValueLabel = osg::Label::create();
    beginEditCP(OpenGLRendererValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		OpenGLRendererValueLabel->setText(std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		OpenGLRendererValueLabel->setConstraints(OpenGLRendererValueLabelConstraints);
    endEditCP(OpenGLRendererValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OpenGLRendererLabel);
       AboutWindow->getChildren().push_back(OpenGLRendererValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//ODE
    GridBagLayoutConstraintsPtr ODELabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(ODELabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ODELabelConstraints->setGridX(0);
        ODELabelConstraints->setGridY(Row);
        ODELabelConstraints->setGridWidth(3);
    endEditCP(ODELabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr ODELabel = osg::Label::create();
    beginEditCP(ODELabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		ODELabel->setText("ODE");
		ODELabel->setConstraints(ODELabelConstraints);
    endEditCP(ODELabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(ODELabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//ODE Version
    GridBagLayoutConstraintsPtr ODEVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(ODEVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ODEVersionLabelConstraints->setGridX(1);
        ODEVersionLabelConstraints->setGridY(Row);
    endEditCP(ODEVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr ODEVersionLabel = osg::Label::create();
    beginEditCP(ODEVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		ODEVersionLabel->setText("Version:");
		ODEVersionLabel->setConstraints(ODEVersionLabelConstraints);
    endEditCP(ODEVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr ODEVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(ODEVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ODEVersionValueLabelConstraints->setGridX(2);
        ODEVersionValueLabelConstraints->setGridY(Row);
    endEditCP(ODEVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr ODEVersionValueLabel = osg::Label::create();
    beginEditCP(ODEVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		ODEVersionValueLabel->setText(dGetConfiguration());
		ODEVersionValueLabel->setConstraints(ODEVersionValueLabelConstraints);
    endEditCP(ODEVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(ODEVersionLabel);
       AboutWindow->getChildren().push_back(ODEVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	//Lua
    GridBagLayoutConstraintsPtr LuaLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(LuaLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        LuaLabelConstraints->setGridX(0);
        LuaLabelConstraints->setGridY(Row);
        LuaLabelConstraints->setGridWidth(3);
    endEditCP(LuaLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr LuaLabel = osg::Label::create();
    beginEditCP(LuaLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		LuaLabel->setText("Lua");
		LuaLabel->setConstraints(LuaLabelConstraints);
    endEditCP(LuaLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(LuaLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

	//Lua Version
    GridBagLayoutConstraintsPtr LuaVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(LuaVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        LuaVersionLabelConstraints->setGridX(1);
        LuaVersionLabelConstraints->setGridY(Row);
    endEditCP(LuaVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr LuaVersionLabel = osg::Label::create();
    beginEditCP(LuaVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		LuaVersionLabel->setText("Version:");
		LuaVersionLabel->setConstraints(LuaVersionLabelConstraints);
    endEditCP(LuaVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    GridBagLayoutConstraintsPtr LuaVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(LuaVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        LuaVersionValueLabelConstraints->setGridX(2);
        LuaVersionValueLabelConstraints->setGridY(Row);
    endEditCP(LuaVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    LabelPtr LuaVersionValueLabel = osg::Label::create();
    beginEditCP(LuaVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		LuaVersionValueLabel->setText(LUA_VERSION);
		LuaVersionValueLabel->setConstraints(LuaVersionValueLabelConstraints);
    endEditCP(LuaVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(LuaVersionLabel);
       AboutWindow->getChildren().push_back(LuaVersionValueLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;
	
	////Fmod
    //GridBagLayoutConstraintsPtr FmodLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(FmodLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //FmodLabelConstraints->setGridX(0);
        //FmodLabelConstraints->setGridY(Row);
        //FmodLabelConstraints->setGridWidth(3);
    //endEditCP(FmodLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    //LabelPtr FmodLabel = osg::Label::create();
    //beginEditCP(FmodLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//FmodLabel->setText("Fmod");
		//FmodLabel->setConstraints(FmodLabelConstraints);
    //endEditCP(FmodLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        //MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        //MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    //endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	//beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       //AboutWindow->getChildren().push_back(FmodLabel);
	//endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    //Row++;

	////Fmod Version
    //GridBagLayoutConstraintsPtr FmodVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(FmodVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //FmodVersionLabelConstraints->setGridX(1);
        //FmodVersionLabelConstraints->setGridY(Row);
    //endEditCP(FmodVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    //LabelPtr FmodVersionLabel = osg::Label::create();
    //beginEditCP(FmodVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//FmodVersionLabel->setText("Fmod Version:");
		//FmodVersionLabel->setConstraints(FmodVersionLabelConstraints);
    //endEditCP(FmodVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //GridBagLayoutConstraintsPtr FmodVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(FmodVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //FmodVersionValueLabelConstraints->setGridX(2);
        //FmodVersionValueLabelConstraints->setGridY(Row);
    //endEditCP(FmodVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    //LabelPtr FmodVersionValueLabel = osg::Label::create();
    //beginEditCP(FmodVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//FmodVersionValueLabel->setText(OSG_VERSION_STRING);
		//FmodVersionValueLabel->setConstraints(FmodVersionValueLabelConstraints);
    //endEditCP(FmodVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        //MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        //MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    //endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	//beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       //AboutWindow->getChildren().push_back(FmodVersionLabel);
       //AboutWindow->getChildren().push_back(FmodVersionValueLabel);
	//endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    //Row++;
	
	////VLC
    //GridBagLayoutConstraintsPtr VLCLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(VLCLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //VLCLabelConstraints->setGridX(0);
        //VLCLabelConstraints->setGridY(Row);
        //VLCLabelConstraints->setGridWidth(3);
    //endEditCP(VLCLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    //LabelPtr VLCLabel = osg::Label::create();
    //beginEditCP(VLCLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//VLCLabel->setText("VLC");
		//VLCLabel->setConstraints(VLCLabelConstraints);
    //endEditCP(VLCLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        //MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        //MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    //endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	//beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       //AboutWindow->getChildren().push_back(VLCLabel);
	//endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    //Row++;

	////VLC Version
    //GridBagLayoutConstraintsPtr VLCVersionLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(VLCVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //VLCVersionLabelConstraints->setGridX(1);
        //VLCVersionLabelConstraints->setGridY(Row);
    //endEditCP(VLCVersionLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    //LabelPtr VLCVersionLabel = osg::Label::create();
    //beginEditCP(VLCVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//VLCVersionLabel->setText("VLC Version:");
		//VLCVersionLabel->setConstraints(VLCVersionLabelConstraints);
    //endEditCP(VLCVersionLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //GridBagLayoutConstraintsPtr VLCVersionValueLabelConstraints = osg::GridBagLayoutConstraints::create();
    //beginEditCP(VLCVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        //VLCVersionValueLabelConstraints->setGridX(2);
        //VLCVersionValueLabelConstraints->setGridY(Row);
    //endEditCP(VLCVersionValueLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    //LabelPtr VLCVersionValueLabel = osg::Label::create();
    //beginEditCP(VLCVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		//VLCVersionValueLabel->setText(OSG_VERSION_STRING);
		//VLCVersionValueLabel->setConstraints(VLCVersionValueLabelConstraints);
    //endEditCP(VLCVersionValueLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    //beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        //MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        //MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    //endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	//beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       //AboutWindow->getChildren().push_back(VLCVersionLabel);
       //AboutWindow->getChildren().push_back(VLCVersionValueLabel);
	//endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    //Row++;

    //Blank Row
    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

    Row++;

	//Website
    GridBagLayoutConstraintsPtr EngineWebsiteLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(EngineWebsiteLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        EngineWebsiteLabelConstraints->setGridX(0);
        EngineWebsiteLabelConstraints->setGridY(Row);
        EngineWebsiteLabelConstraints->setGridWidth(3);
    endEditCP(EngineWebsiteLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);

    LabelPtr EngineWebsiteLabel = osg::Label::create();
    beginEditCP(EngineWebsiteLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);
		EngineWebsiteLabel->setText(getKabalaEngineWebsite());
		EngineWebsiteLabel->setConstraints(EngineWebsiteLabelConstraints);
		EngineWebsiteLabel->setAlignment(Vec2f(0.5f,0.5f));
    endEditCP(EngineWebsiteLabel, Label::TextFieldMask | Label::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(EngineWebsiteLabel);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);

    Row++;

    //Blank Row
    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowHeights().push_back(20.0f);
        MainInternalWindowLayout->getRowWeights().push_back(0.0f);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowHeightsFieldMask | GridBagLayout::RowWeightsFieldMask);

    Row++;

	//Ok ::osg::Button
    GridBagLayoutConstraintsPtr OkButtonLabelConstraints = osg::GridBagLayoutConstraints::create();
    beginEditCP(OkButtonLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridWidthFieldMask);
        OkButtonLabelConstraints->setGridX(0);
        OkButtonLabelConstraints->setGridY(Row);
        OkButtonLabelConstraints->setGridWidth(3);
		OkButtonLabelConstraints->setFill(GridBagLayoutConstraints::FILL_NONE);
    endEditCP(OkButtonLabelConstraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridWidthFieldMask);

    ButtonPtr OkButton = ::osg::Button::create();
    beginEditCP(OkButton, ::osg::Button::TextFieldMask | ::osg::Button::ConstraintsFieldMask);
        OkButton->setText("Ok");
		OkButton->setConstraints(OkButtonLabelConstraints);
    endEditCP(OkButton, ::osg::Button::TextFieldMask | ::osg::Button::ConstraintsFieldMask);

    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowWeightsFieldMask);
        MainInternalWindowLayout->getRowWeights().push_back(1.0f); //The Button Row
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowWeightsFieldMask);

	beginEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);
       AboutWindow->getChildren().push_back(OkButton);
	endEditCP(AboutWindow, InternalWindow::ChildrenFieldMask);


    Row++;

    //Layout
    beginEditCP(MainInternalWindowLayout, GridBagLayout::RowsFieldMask);
        MainInternalWindowLayout->setRows(Row+1);
    endEditCP(MainInternalWindowLayout, GridBagLayout::RowsFieldMask);

	return AboutWindow;
}

OSG_END_NAMESPACE

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

