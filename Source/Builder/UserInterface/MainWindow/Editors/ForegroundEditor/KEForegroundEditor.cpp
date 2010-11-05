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

#include "KEForegroundEditor.h"
#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGTextureSelectChunk.h>
#include <OpenSG/OSGGenericNameAttachmentEditor.h>
#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>

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
// OSGForegroundEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGForegroundEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ForegroundEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ForegroundEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = dynamic_cast<ComboBox*>(findContainer("KE.WorldBuilder.Editor.ForegroundEditor.TypeComboBox", TheApplicationBuilder));
    _TypeTextureSelect = dynamic_cast<TextureSelectChunk*>(findContainer("KE.WorldBuilder.Editor.ForegroundEditor.TypeIconTextureSelect", TheApplicationBuilder));
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.ForegroundEditor.NameEditor", TheApplicationBuilder));

    DerivedFieldContainerComboBoxModelRecPtr ComboModel = DerivedFieldContainerComboBoxModel::create();
    ComboModel->editMFDerivedFieldContainerTypes()->push_back(Foreground::getClassType().getName());
    _TypeComboBox->setModel(ComboModel);
}

void ForegroundEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = NULL;
    _TypeTextureSelect = NULL;
    _NameEditor = NULL;
}

void ForegroundEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void ForegroundEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 ForegroundEditor::getCardIndex(void) const
{
    return 4;
}

std::string ForegroundEditor::getEditorTypeText(void) const
{
    return "Foreground Editor";
}

void ForegroundEditor::attachForeground(Foreground* const TheForeground)
{
    _TypeComboBox->setSelectedItem(&TheForeground->getType());
    _NameEditor->attachContainer(TheForeground);
}

void ForegroundEditor::dettachForeground(void)
{
    _NameEditor->dettachContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ForegroundEditor::ForegroundEditor(void) :
    Inherited()
{
}

ForegroundEditor::ForegroundEditor(const ForegroundEditor &source) :
    Inherited(source)
{
}

ForegroundEditor::~ForegroundEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ForegroundEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ForegroundEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ForegroundEditor NI" << std::endl;
}

OSG_END_NAMESPACE
