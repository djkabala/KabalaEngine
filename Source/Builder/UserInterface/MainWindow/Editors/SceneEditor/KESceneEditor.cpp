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

#include "KESceneEditor.h"
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

#include <OpenSG/OSGVectorSpinnerFieldEditor.h>
#include <OpenSG/OSGBoolFieldEditor.h>
OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.SceneEditor.NameEditor", TheApplicationBuilder));
    _PhysicsEnabledEditor = dynamic_cast<BoolFieldEditor*>(findContainer("KE.WorldBuilder.Editor.SceneEditor.Physics.EnabledEditor", TheApplicationBuilder));
    _GravityEditor = dynamic_cast<VectorSpinnerFieldEditor*>(findContainer("KE.WorldBuilder.Editor.SceneEditor.Physics.GravityDirectionEditor", TheApplicationBuilder));
}

void SceneEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = NULL;
    _PhysicsEnabledEditor = NULL;
    _GravityEditor = NULL;
}

void SceneEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _PhysicsEnabledEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _GravityEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void SceneEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 SceneEditor::getCardIndex(void) const
{
    return 2;
}

std::string SceneEditor::getEditorTypeText(void) const
{
    return "Scene Editor";
}

void SceneEditor::attachScene(Scene* const TheScene)
{
    _NameEditor->attachContainer(TheScene);
    //_PhysicsEnabledEditor->attachField(dynamic_cast<Transform*>(TheSceneObject->getNode()->getCore()), Transform::MatrixFieldId);
    _GravityEditor->attachField(TheScene->getPhysicsWorld(), PhysicsWorld::GravityFieldMask);
}

void SceneEditor::dettachScene(void)
{
    _NameEditor->dettachContainer();
    _PhysicsEnabledEditor->dettachField();
    _GravityEditor->dettachField();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SceneEditor::SceneEditor(void) :
    Inherited()
{
}

SceneEditor::SceneEditor(const SceneEditor &source) :
    Inherited(source)
{
}

SceneEditor::~SceneEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneEditor NI" << std::endl;
}

OSG_END_NAMESPACE
