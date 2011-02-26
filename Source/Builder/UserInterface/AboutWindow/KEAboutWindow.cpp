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


#include "KEAboutWindow.h"
#include "Builder/KEApplicationBuilder.h"
#include "Project/KEProject.h"
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

#include <OpenSG/OSGDialogWindow.h>
#include <OpenSG/OSGButton.h>
#include <OpenSG/OSGStringListModel.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGUIDrawUtils.h>
//#include <OpenSG/OSGGL.h>

#include "KEPlatformUtils.h"

OSG_BEGIN_NAMESPACE

void openAboutWindow(void)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());

    DialogWindowRecPtr TheAboutWindow = createAboutWindow();
    
    dynamic_cast<Button*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.OkButton"))->connectActionPerformed(boost::bind(&handleAboutWindowCloseButton, _1, TheAboutWindow.get()));

    TheAboutWindow->setPosition(calculateAlignment(Pnt2f(0.0f,0.0f), AppBuilder->getDrawingSurface()->getSize(), TheAboutWindow->getPreferredSize(), 0.5f,0.5f));

    //Update the Values

    //General
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.VersionValueLabel"))->setText(getKabalaEngineVersion());
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.CodeRevisionValueLabel"))->setText(getKabalaEngineBuildRepositoryRevision());
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.BuildTypeValueLabel"))->setText(getKabalaEngineBuildType());
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.OpenSGVersionValueLabel"))->setText(OSG_VERSION_STRING);
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.LoggingValueLabel"))
        ->setText(MainApplication::the()->getLoggingEnabled() ? "Enabled" : "Disabled");
    if(MainApplication::the()->getLoggingEnabled() &&
       MainApplication::the()->getLoggingToFile())
    {
        dynamic_cast<Button*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.LogFileButton"))
            ->setText(MainApplication::the()->getLoggingFilePath().string());
        dynamic_cast<Button*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.GeneralPanel.LogFileButton"))
            ->connectActionPerformed(boost::bind(&openFile, MainApplication::the()->getLoggingFilePath()));
    }
    //FMod
    //Lua
    //ODE
    //VLC
    //DirectShow
    //
    
    //System
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.OSValueLabel"))->setText(getPlatformName());
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.ProcessorsValueLabel"))->setText(getPlatformProcessors());
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.RAMValueLabel"))->setText(getPlatformRAM());

    //Activate the window in order to bind the OpenGL context
    AppBuilder->getDrawingSurface()->getEventProducer()->activate();

    {
        const char* glVersion   = 
            reinterpret_cast<const char *>(glGetString(GL_VERSION));
        dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.OpenGLValueLabel"))
            ->setText(glVersion ? glVersion : "Unknown");
    }

    const char* glVendor   = 
        reinterpret_cast<const char *>(glGetString(GL_VENDOR));
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.OpenGLVendorValueLabel"))
        ->setText(glVendor ? glVendor : "Unknown");

    const char* glRenderer = 
        reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    dynamic_cast<Label*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.SystemPanel.OpenGLRendererValueLabel"))
        ->setText(glRenderer ? glRenderer : "Unknown");

    //Dectivate the window
    AppBuilder->getDrawingSurface()->getEventProducer()->deactivate();

    //OpenSG libraries
    StringListModelUnrecPtr OpenSGLibListModel = dynamic_cast<StringListModel*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.PlugintsPanel.OpenSGLibsListModel"));
    OpenSGLibListModel->editMFItems()->reserve(getNumLibraries());
    std::string LibName;
    for(UInt32 i(0) ; i<getNumLibraries() ; ++i)
    {
        LibName = getLibraryName(i);
        OpenSGLibListModel->editMFItems()->push_back(LibName +
                                                     ": " +
                                                     getLibraryVersion(LibName) +
                                                     "  Rev: " +
                                                     getLibraryRevision(LibName)
                                                     );
    }


    //OpenGL Extensions
    StringListModelUnrecPtr OpenGLExtListModel = dynamic_cast<StringListModel*>(AppBuilder->findContainer("KabalaEngine.AboutWindow.PlugintsPanel.KabalaEnginePluginsListModel"));
    std::vector<std::string> GLExtList(AppBuilder->getDrawingSurface()->getEventProducer()->getExtensions());
    OpenGLExtListModel->editMFItems()->setValues(GLExtList);

	AppBuilder->getDrawingSurface()->openWindow(TheAboutWindow);
}

void handleAboutWindowCloseButton(ActionEventDetails* const details,
                                  DialogWindow* const TheAboutWindow)
{
    TheAboutWindow->close(DialogWindowEventDetails::DIALOG_OPTION_OK,"",0);
}

DialogWindowTransitPtr createAboutWindow(void)
{
    BoostPath WindowDefinitionPath(MainApplication::the()->getSettings().get<BoostPath>("builder.ui.about_window.path"));

    if(!WindowDefinitionPath.is_complete())
    {
        WindowDefinitionPath = MainApplication::the()->getSettings().get<BoostPath>("basic.data.directory") / WindowDefinitionPath;
    }

    return loadAboutWindow(WindowDefinitionPath);
}

DialogWindowTransitPtr loadAboutWindow(const BoostPath& WindowDefinitionFile)
{
    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(WindowDefinitionFile);

    for(FCFileType::FCPtrStore::iterator Itor(NewContainers.begin()) ; Itor!= NewContainers.end() ; ++Itor)
    {
        if((*Itor)->getType() == DialogWindow::getClassType())
        {
            return DialogWindowTransitPtr(dynamic_pointer_cast<DialogWindow>(*Itor));
        }
    }
    SFATAL << "Failed to load Builder About Window definition from file: " << WindowDefinitionFile.string() << std::endl;

    return DialogWindowTransitPtr(NULL);
}

OSG_END_NAMESPACE
