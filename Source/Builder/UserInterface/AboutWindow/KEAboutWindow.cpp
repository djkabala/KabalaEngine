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
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGUIDrawUtils.h>

OSG_BEGIN_NAMESPACE

void openAboutWindow(void)
{
    ApplicationBuilderUnrecPtr AppBuilder = dynamic_cast<ApplicationBuilder*>(MainApplication::the()->getBuilderMode());

    DialogWindowRecPtr TheAboutWindow = createAboutWindow();
    
    dynamic_cast<Button*>(AppBuilder->findContainer("KE.WorldBuilder.Overview.CloseButton"))->connectActionPerformed(boost::bind(&handleAboutWindowCloseButton, _1, TheAboutWindow.get()));

    TheAboutWindow->setPosition(calculateAlignment(Pnt2f(0.0f,0.0f), AppBuilder->getDrawingSurface()->getSize(), TheAboutWindow->getPreferredSize(), 0.5f,0.5f));
    
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
