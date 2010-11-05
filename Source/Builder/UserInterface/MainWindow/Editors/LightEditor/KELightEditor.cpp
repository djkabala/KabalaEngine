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

#include "KELightEditor.h"
#include <OpenSG/OSGComboBox.h>
#include <OpenSG/OSGTextureSelectChunk.h>
#include <OpenSG/OSGGenericNameAttachmentEditor.h>
#include <OpenSG/OSGDerivedFieldContainerComboBoxModel.h>
#include <OpenSG/OSGLight.h>
#include <OpenSG/OSGMatrixTransCompFieldEditor.h>
#include <OpenSG/OSGBoolFieldEditor.h>
#include <OpenSG/OSGColorFieldEditor.h>

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
// OSGLightEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGLightEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LightEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LightEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = dynamic_cast<ComboBox*>(findContainer("KE.WorldBuilder.Editor.LightEditor.TypeComboBox", TheApplicationBuilder));
    _TypeTextureSelect = dynamic_cast<TextureSelectChunk*>(findContainer("KE.WorldBuilder.Editor.LightEditor.TypeIconTextureSelect", TheApplicationBuilder));
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.NameEditor", TheApplicationBuilder));
    _EnabledEditor = dynamic_cast<BoolFieldEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.EnabledEditor", TheApplicationBuilder));
    _BeaconTransformEditor = dynamic_cast<MatrixTransCompFieldEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.TransformEditor", TheApplicationBuilder));
    _AmbientColorEditor = dynamic_cast<ColorFieldEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.AmbientEditor", TheApplicationBuilder));
    _DiffuseColorEditor = dynamic_cast<ColorFieldEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.DiffuseEditor", TheApplicationBuilder));
    _SpecularColorEditor = dynamic_cast<ColorFieldEditor*>(findContainer("KE.WorldBuilder.Editor.LightEditor.SpecularEditor", TheApplicationBuilder));

    DerivedFieldContainerComboBoxModelRecPtr ComboModel = DerivedFieldContainerComboBoxModel::create();
    ComboModel->editMFDerivedFieldContainerTypes()->push_back(Light::getClassType().getName());
    _TypeComboBox->setModel(ComboModel);
}

void LightEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboBox = NULL;
    _TypeTextureSelect = NULL;
    _NameEditor = NULL;
    _EnabledEditor = NULL;
    _BeaconTransformEditor = NULL;
    _AmbientColorEditor = NULL;
    _DiffuseColorEditor = NULL;
    _SpecularColorEditor = NULL;
}

void LightEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TheCommandManager = TheApplicationBuilder->getCommandManager();

    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _EnabledEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _BeaconTransformEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _AmbientColorEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _DiffuseColorEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _SpecularColorEditor->setCommandManager(TheApplicationBuilder->getCommandManager());

    _TypeComboSelectionChangedConnection = _TypeComboBox->getModel()->connectSelectionChanged(boost::bind(&LightEditor::handleTypeComboSelectionChanged, this, _1));
}

void LightEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _TypeComboSelectionChangedConnection.disconnect();
    _TheCommandManager = CommandManagerPtr();
}

UInt32 LightEditor::getCardIndex(void) const
{
    return 7;
}

std::string LightEditor::getEditorTypeText(void) const
{
    return "Light Editor";
}

void LightEditor::attachLight(Light* const TheLight)
{
    _EditingLight = TheLight;

    _TypeComboBox->setSelectedItem(&_EditingLight->getType());
    _NameEditor->attachContainer(_EditingLight);
    _EnabledEditor->attachField(_EditingLight, Light::OnFieldId);
    _BeaconTransformEditor->attachField(dynamic_cast<Transform*>(_EditingLight->getBeacon()->getCore()), Transform::MatrixFieldId);
    _AmbientColorEditor->attachField(_EditingLight, Light::AmbientFieldId);
    _DiffuseColorEditor->attachField(_EditingLight, Light::DiffuseFieldId);
    _SpecularColorEditor->attachField(_EditingLight, Light::SpecularFieldId);
}

void LightEditor::dettachLight(void)
{
    _EditingLight = NULL;

    _NameEditor->dettachContainer();
    _EnabledEditor->dettachField();
    _BeaconTransformEditor->dettachField();
    _AmbientColorEditor->dettachField();
    _DiffuseColorEditor->dettachField();
    _SpecularColorEditor->dettachField();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void LightEditor::handleTypeComboSelectionChanged(ComboBoxSelectionEventDetails* const details)
{
    boost::any SelectedItem(_TypeComboBox->getSelectedItem());
    if(SelectedItem.empty() ||
        _EditingLight->getType() != *boost::any_cast<FieldContainerType*>(SelectedItem))
    {
        const FieldContainerType* LightType(boost::any_cast<FieldContainerType*>(SelectedItem));
        
        LightRecPtr NewLight = dynamic_pointer_cast<Light>(LightType->createContainer());
        NewLight->setBeacon(_EditingLight->getBeacon());
        NewLight->setOn(_EditingLight->getOn());
        NewLight->setAmbient(_EditingLight->getAmbient());
        NewLight->setDiffuse(_EditingLight->getDiffuse());
        NewLight->setSpecular(_EditingLight->getSpecular());
        NewLight->setConstantAttenuation(_EditingLight->getConstantAttenuation());
        NewLight->setLinearAttenuation(_EditingLight->getLinearAttenuation());
        NewLight->setQuadraticAttenuation(_EditingLight->getQuadraticAttenuation());
        NewLight->setLightEngine(_EditingLight->getLightEngine());
        NewLight->setShadowIntensity(_EditingLight->getShadowIntensity());
        NewLight->setShadowMode(_EditingLight->getShadowMode());

        dynamic_cast<Node*>(_EditingLight->getParents().front())->setCore(NewLight);

        dettachLight();

        attachLight(NewLight);

        //CommandPtr OpenProjectItemCommand = OpenProjectCommand::create();
        //_TheCommandManager->executeCommand(OpenProjectItemCommand);
    }
}

/*----------------------- constructors & destructors ----------------------*/

LightEditor::LightEditor(void) :
    Inherited()
{
}

LightEditor::LightEditor(const LightEditor &source) :
    Inherited(source)
{
}

LightEditor::~LightEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LightEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LightEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LightEditor NI" << std::endl;
}

OSG_END_NAMESPACE
