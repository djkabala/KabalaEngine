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

#include "KEBackgroundEditor.h"
#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGTextureSelectChunk.h>
#include <OpenSG/OSGGenericNameAttachmentEditor.h>
#include <OpenSG/OSGColorFieldEditor.h>
#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/OSGSolidBackground.h>

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
// OSGBackgroundEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGBackgroundEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BackgroundEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BackgroundEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = dynamic_cast<ComboBox*>(findContainer("KE.WorldBuilder.Editor.BackgroundEditor.TypeComboBox", TheApplicationBuilder));
    _TypeTextureSelect = dynamic_cast<TextureSelectChunk*>(findContainer("KE.WorldBuilder.Editor.BackgroundEditor.TypeIconTextureSelect", TheApplicationBuilder));
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.BackgroundEditor.NameEditor", TheApplicationBuilder));
    _SolidColorEditor = dynamic_cast<ColorFieldEditor*>(findContainer("KE.WorldBuilder.Editor.BackgroundEditor.ColorEditor", TheApplicationBuilder));

    DerivedFieldContainerComboBoxModelRecPtr ComboModel = DerivedFieldContainerComboBoxModel::create();
    ComboModel->editMFDerivedFieldContainerTypes()->push_back(Background::getClassType().getName());
    _TypeComboBox->setModel(ComboModel);

}

void BackgroundEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = NULL;
    _TypeTextureSelect = NULL;
    _NameEditor = NULL;
    _SolidColorEditor = NULL;
}

void BackgroundEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _SolidColorEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void BackgroundEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 BackgroundEditor::getCardIndex(void) const
{
    return 3;
}

std::string BackgroundEditor::getEditorTypeText(void) const
{
    return "Background Editor";
}

void BackgroundEditor::attachBackground(Background* const TheBackground)
{
    _TypeComboBox->setSelectedItem(&TheBackground->getType());
    _NameEditor->attachContainer(TheBackground);
    if(TheBackground->getType().isDerivedFrom(SolidBackground::getClassType()))
    {
        _SolidColorEditor->attachField(TheBackground, SolidBackground::ColorFieldId);
    }
}

void BackgroundEditor::dettachBackground(void)
{
    _NameEditor->dettachContainer();
    _SolidColorEditor->dettachField();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BackgroundEditor::BackgroundEditor(void) :
    Inherited()
{
}

BackgroundEditor::BackgroundEditor(const BackgroundEditor &source) :
    Inherited(source)
{
}

BackgroundEditor::~BackgroundEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BackgroundEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void BackgroundEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump BackgroundEditor NI" << std::endl;
}

OSG_END_NAMESPACE
