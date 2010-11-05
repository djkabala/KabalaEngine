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

#include "KECameraEditor.h"
#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGTextureSelectChunk.h>
#include <OpenSG/OSGGenericNameAttachmentEditor.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGNumberSpinnerFieldEditor.h>
#include <OpenSG/OSGMatrixTransCompFieldEditor.h>
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
// OSGCameraEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGCameraEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CameraEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CameraEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = dynamic_cast<ComboBox*>(findContainer("KE.WorldBuilder.Editor.CameraEditor.TypeComboBox", TheApplicationBuilder));
    _TypeTextureSelect = dynamic_cast<TextureSelectChunk*>(findContainer("KE.WorldBuilder.Editor.CameraEditor.TypeIconTextureSelect", TheApplicationBuilder));
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.CameraEditor.NameEditor", TheApplicationBuilder));
    _FOVEditor = dynamic_cast<NumberSpinnerFieldEditor*>(findContainer("KE.WorldBuilder.Editor.CameraEditor.FOVEditor", TheApplicationBuilder));
    _BeaconTransformEditor = dynamic_cast<MatrixTransCompFieldEditor*>(findContainer("KE.WorldBuilder.Editor.CameraEditor.TransformEditor", TheApplicationBuilder));

    DerivedFieldContainerComboBoxModelRecPtr ComboModel = DerivedFieldContainerComboBoxModel::create();
    ComboModel->editMFDerivedFieldContainerTypes()->push_back(Camera::getClassType().getName());
    _TypeComboBox->setModel(ComboModel);
}

void CameraEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = NULL;
    _TypeTextureSelect = NULL;
    _NameEditor = NULL;
    _FOVEditor = NULL;
    _BeaconTransformEditor = NULL;
}

void CameraEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _FOVEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _BeaconTransformEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void CameraEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 CameraEditor::getCardIndex(void) const
{
    return 5;
}

std::string CameraEditor::getEditorTypeText(void) const
{
    return "Camera Editor";
}

void CameraEditor::attachCamera(Camera* const TheCamera)
{
    _TypeComboBox->setSelectedItem(&TheCamera->getType());
    _NameEditor->attachContainer(TheCamera);
    _BeaconTransformEditor->attachField(dynamic_cast<Transform*>(TheCamera->getBeacon()->getCore()), Transform::MatrixFieldId);
    if(TheCamera->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
    {
        _FOVEditor->attachField(TheCamera, PerspectiveCamera::FovFieldId);
    }
}

void CameraEditor::dettachCamera(void)
{
    _NameEditor->dettachContainer();
    _BeaconTransformEditor->dettachField();
    _FOVEditor->dettachField();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CameraEditor::CameraEditor(void) :
    Inherited()
{
}

CameraEditor::CameraEditor(const CameraEditor &source) :
    Inherited(source)
{
}

CameraEditor::~CameraEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CameraEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CameraEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CameraEditor NI" << std::endl;
}

OSG_END_NAMESPACE
