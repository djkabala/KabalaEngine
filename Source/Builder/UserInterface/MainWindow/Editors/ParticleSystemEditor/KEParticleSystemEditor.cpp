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

#include "KEParticleSystemEditor.h"
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
// OSGParticleSystemEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystemEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystemEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystemEditor::createInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = dynamic_cast<GenericNameAttachmentEditor*>(findContainer("KE.WorldBuilder.Editor.ParticleEditor.NameEditor", TheApplicationBuilder));
}

void ParticleSystemEditor::destroyInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor = NULL;
}

void ParticleSystemEditor::attachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
    _NameEditor->setCommandManager(TheApplicationBuilder->getCommandManager());
}

void ParticleSystemEditor::dettachInterface(ApplicationBuilder* const TheApplicationBuilder)
{
}

UInt32 ParticleSystemEditor::getCardIndex(void) const
{
    return 6;
}

std::string ParticleSystemEditor::getEditorTypeText(void) const
{
    return "Particle System Editor";
}

void ParticleSystemEditor::attachParticleSystem(ParticleSystem* const TheParticleSystem)
{
    _NameEditor->attachContainer(TheParticleSystem);
}

void ParticleSystemEditor::dettachParticleSystem(void)
{
    _NameEditor->dettachContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystemEditor::ParticleSystemEditor(void) :
    Inherited()
{
}

ParticleSystemEditor::ParticleSystemEditor(const ParticleSystemEditor &source) :
    Inherited(source)
{
}

ParticleSystemEditor::~ParticleSystemEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystemEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ParticleSystemEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystemEditor NI" << std::endl;
}

OSG_END_NAMESPACE
