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

#include "KEViewportEditor.h"
#include <OpenSG/OSGGenericNameAttachmentEditor.h>

#include "Project/KEProject.h"
#include "Builder/KEApplicationBuilder.h"
#include "Builder/UserInterface/MainWindow/KEMainWindow.h"
#include "Builder/UserInterface/MainWindow/MainMenu/KEMainMenu.h"
#include "Builder/UserInterface/MainWindow/MainToolbar/KEMainToolbar.h"
#include "Builder/UserInterface/MainWindow/StatusBar/KEStatusBar.h"
#include "Builder/UserInterface/MainWindow/HelpPanel/KEHelpPanel.h"
#include "Builder/UserInterface/MainWindow/SceneComponentTree/KESceneComponentTree.h"
#include "Builder/UserInterface/MainWindow/SceneNavigationPanel/KESceneNavigationPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportPanel/KESceneViewportPanel.h"
#include "Builder/UserInterface/MainWindow/SceneViewportToolbar/KESceneViewportToolbar.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGViewportEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGViewportEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ViewportEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ViewportEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.ViewportEditor.NameEditor", TheApplicationBuilder));
}

void ViewportEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = NULL;
}

void ViewportEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    //_NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void ViewportEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 ViewportEditor::getCardIndex(void) const
{
    return 1;
}

std::string ViewportEditor::getEditorTypeText(void) const
{
    return "Viewport Editor";
}

void ViewportEditor::attachViewport(Viewport* const TheViewport)
{
    _NameEditor->attachContainer(TheViewport);
}

void ViewportEditor::dettachViewport(void)
{
    _NameEditor->dettachContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ViewportEditor::ViewportEditor(void) :
    Inherited()
{
}

ViewportEditor::ViewportEditor(const ViewportEditor &source) :
    Inherited(source)
{
}

ViewportEditor::~ViewportEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ViewportEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ViewportEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ViewportEditor NI" << std::endl;
}

OSG_END_NAMESPACE
