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

#include "KESceneObjectEditor.h"
#include <OpenSG/OSGGenericNameAttachmentEditor.h>
#include <OpenSG/OSGMatrixTransCompFieldEditor.h>
#include <OpenSG/OSGCheckboxButton.h>
#include <OpenSG/OSGMenuButton.h>

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

#include <OpenSG/OSGButtonSelectedEventDetails.h>
#include <OpenSG/OSGNumberSpinnerFieldEditor.h>
#include <OpenSG/OSGBoolFieldEditor.h>
#include <OpenSG/OSGPhysicsBody.h>
#include <OpenSG/OSGPhysicsGeom.h>
OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSceneObjectEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGSceneObjectEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SceneObjectEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SceneObjectEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.NameEditor", TheApplicationBuilder));
    _ModelMenuButton = dynamic_cast<MenuButton*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.ModelMenuButton", TheApplicationBuilder));
    _EnabledCheckbox = dynamic_cast<CheckboxButton*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.EnabledCheckbox", TheApplicationBuilder));
    _BeaconTransformEditor = dynamic_cast<MatrixTransCompFieldEditor*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.TransformationEditor", TheApplicationBuilder));
    _MassEditor = dynamic_cast<NumberSpinnerFieldEditor*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.PhysicalProperties.MassEditor", TheApplicationBuilder));
    _CollidableCheckbox = dynamic_cast<CheckboxButton*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.PhysicalProperties.CollidableCheckbox", TheApplicationBuilder));
    _GravityModeEditor = dynamic_cast<BoolFieldEditor*>(findContainer("KE.WorldBuilder.Editor.SceneObjectEditor.PhysicalProperties.GravityEditor", TheApplicationBuilder));
}

void SceneObjectEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = NULL;
    _ModelMenuButton = NULL;
    _EnabledCheckbox = NULL;
    _BeaconTransformEditor = NULL;
    _MassEditor = NULL;
    _CollidableCheckbox = NULL;
    _GravityModeEditor = NULL;
}

void SceneObjectEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _BeaconTransformEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _MassEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    _GravityModeEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
    
    _CollidableCheckboxSelectedConnection = _CollidableCheckbox->connectButtonSelected(boost::bind(&SceneObjectEditor::handleCollidableCheckboxSelected, this, _1));
    _CollidableCheckboxDeselectedConnection = _CollidableCheckbox->connectButtonDeselected(boost::bind(&SceneObjectEditor::handleCollidableCheckboxDeselected, this, _1));
}

void SceneObjectEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _CollidableCheckboxSelectedConnection.disconnect();
}

UInt32 SceneObjectEditor::getCardIndex(void) const
{
    return 1;
}

std::string SceneObjectEditor::getEditorTypeText(void) const
{
    return "Scene Object Editor";
}

void SceneObjectEditor::attachSceneObject(SceneObject* const TheSceneObject)
{
    _EditingSceneObject = TheSceneObject;
    _NameEditor->attachContainer(TheSceneObject);
    _BeaconTransformEditor->attachField(dynamic_cast<Transform*>(TheSceneObject->getNode()->getCore()), Transform::MatrixFieldId);

    
    AttachmentUnrecPtr Att = TheSceneObject->getNode()->findAttachment(PhysicsBody::getClassType());
    if(Att!=NULL)
    {
        _MassEditor->setEnabled(true);
        _GravityModeEditor->setEnabled(true);
        PhysicsBodyUnrecPtr BodyAtt = dynamic_pointer_cast<PhysicsBody>(Att);
        _MassEditor->attachField(BodyAtt, PhysicsBody::MassFieldId);
        _GravityModeEditor->attachField(BodyAtt, PhysicsBody::GravityModeFieldId);
    }
    else
    {
        _MassEditor->setEnabled(false);
        _GravityModeEditor->setEnabled(false);
    }
    Att = TheSceneObject->getNode()->findAttachment(PhysicsGeom::getClassType());
    if(Att!=NULL)
    {
        _CollidableCheckbox->setEnabled(true);
        PhysicsGeomUnrecPtr GeomAtt = dynamic_pointer_cast<PhysicsGeom>(Att);

        if(GeomAtt->getCategoryBits() != 0)
        {
            _CollidableCheckbox->setSelected(true);
        }
        else
        {
            _CollidableCheckbox->setSelected(false);
        }
    }
    else
    {
        _CollidableCheckbox->setEnabled(false);
    }
}

void SceneObjectEditor::dettachSceneObject(void)
{
    _EditingSceneObject = NULL;
    _NameEditor->dettachContainer();
    _BeaconTransformEditor->dettachField();
    _MassEditor->dettachField();
    _GravityModeEditor->dettachField();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SceneObjectEditor::handleCollidableCheckboxSelected(ButtonSelectedEventDetails* const details)
{
    AttachmentUnrecPtr Att = _EditingSceneObject->getNode()->findAttachment(PhysicsGeom::getClassType());
    if(Att!=NULL)
    {
        PhysicsGeomUnrecPtr GeomAtt = dynamic_pointer_cast<PhysicsGeom>(Att);
        GeomAtt->setCategoryBits(TypeTraits<UInt32>::getMax());
        GeomAtt->setCollideBits(TypeTraits<UInt32>::getMax());
    }
}
void SceneObjectEditor::handleCollidableCheckboxDeselected(ButtonSelectedEventDetails* const details)
{
    AttachmentUnrecPtr Att = _EditingSceneObject->getNode()->findAttachment(PhysicsGeom::getClassType());
    if(Att!=NULL)
    {
        PhysicsGeomUnrecPtr GeomAtt = dynamic_pointer_cast<PhysicsGeom>(Att);
        GeomAtt->setCategoryBits(0);
        GeomAtt->setCollideBits(0);
    }
}

/*----------------------- constructors & destructors ----------------------*/

SceneObjectEditor::SceneObjectEditor(void) :
    Inherited()
{
}

SceneObjectEditor::SceneObjectEditor(const SceneObjectEditor &source) :
    Inherited(source)
{
}

SceneObjectEditor::~SceneObjectEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SceneObjectEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SceneObjectEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SceneObjectEditor NI" << std::endl;
}

OSG_END_NAMESPACE
