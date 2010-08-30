/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *  authors: David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)  *
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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KETravMaskCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>
#include <OpenSG/OSGDialogWindow.h>
#include <OpenSG/OSGUIDrawingSurface.h>
#include <OpenSG/OSGTravMaskGraphOp.h>
#include "Player/KEApplicationPlayer.h"
#include "Application/KEMainApplication.h"
#include "Player/HierarchyPanel/KEHierarchyPanel.h"

#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class ExportModelCommand
A ExportModelCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType TravMaskCommand::_Type("TravMaskCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

TravMaskCommandPtr TravMaskCommand::create(Node* const RootNode,
                                     UIDrawingSurface* const DrawingSurface)
{
	return RefPtr(new TravMaskCommand(RootNode, DrawingSurface));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TravMaskCommand::execute(void)
{
    if(_RootNode != NULL)
    {
        DialogWindowRefPtr SearchStrDialog = 
            DialogWindow::createTextInputDialog("Search string ...",
                                                "Enter the text you would like to match.",
                                                true,
                                                std::vector<std::string>(1, MainApplication::the()->getSettings().get<std::string>("player.debugger.trav_mask_graph_op.search_regex")));

        SearchStrDialog->connectDialogWindowClosed(boost::bind(&TravMaskCommand::handleChooseMatchStringDialogClosed, _1, _DrawingSurface.get(), _RootNode.get()));
        SearchStrDialog->setModal(true);

        _DrawingSurface->openWindow(SearchStrDialog);
    }
}

void TravMaskCommand::handleChooseMatchStringDialogClosed(DialogWindowEventDetails* const details,
                                                          UIDrawingSurface* const DrawingSurface,
                                                          Node* const RootNode)
{
    if(details->getOption() == DialogWindowEventDetails::DIALOG_OPTION_OK)
    {
        //Get the Search string returned
        std::string SearchRegex = details->getInput();

        std::string MaskStrValue;
        try
        {
            MaskStrValue = boost::lexical_cast<std::string>(MainApplication::the()->getSettings().get<UInt32>("player.debugger.trav_mask_graph_op.applied_trav_mask"));
        }
        catch(boost::bad_lexical_cast & ex)
        {
            SWARNING << "Bad lexical cast: " << ex.what() << std::endl;
            return;
        }

        //Open Dialog for setting the traversal mask
        DialogWindowRefPtr TravMaskDialog = 
            DialogWindow::createTextInputDialog("Traversal Mask",
                                                "Enter the traversal mask you would like to be applied",
                                                true,
                                                std::vector<std::string>(1, MaskStrValue));

        TravMaskDialog->connectDialogWindowClosed(boost::bind(&TravMaskCommand::handleChooseTravMaskDialogClosed, _1, SearchRegex, RootNode));
        TravMaskDialog->setModal(true);

        DrawingSurface->openWindow(TravMaskDialog);
    }
}

void TravMaskCommand::handleChooseTravMaskDialogClosed(DialogWindowEventDetails* const details,
                                                       const std::string& SearchRegex,
                                                       Node* const RootNode)
{
    if(details->getOption()== DialogWindowEventDetails::DIALOG_OPTION_OK)
    {
        //Get the Search string returned
        UInt32 NewTravMask;
        try
        {
            NewTravMask = boost::lexical_cast<UInt32>(details->getInput());
        }
        catch(boost::bad_lexical_cast & ex)
        {
            SWARNING << "Bad lexical cast: " << ex.what() << std::endl;
            return;
        }


        //Create and run the graph op
        TravMaskGraphOpRefPtr colMeshGrOp = TravMaskGraphOp::create();
        colMeshGrOp->setMatchRegex(SearchRegex);
        colMeshGrOp->setNewTravMask (NewTravMask);
        colMeshGrOp->setMatchName(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.match_name"));
        colMeshGrOp->setMatchWholeName(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.match_whole_name"));
        colMeshGrOp->setMatchNodeCoreType(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.match_node_core_type"));
        colMeshGrOp->setNodeCoreType(MainApplication::the()->getSettings().get<std::string>("player.debugger.trav_mask_graph_op.node_core_typename"));
        colMeshGrOp->setMatchDerivedCoreTypes(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.match_derived_core_types"));
        colMeshGrOp->setMatchCurrentTravMask(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.match_trav_mask"));
        colMeshGrOp->setCurrentTravMaskValue(MainApplication::the()->getSettings().get<UInt32>("player.debugger.trav_mask_graph_op.match_trav_mask_value"));
        colMeshGrOp->setMatchMaskCondition(MainApplication::the()->getSettings().get<UInt8>("player.debugger.trav_mask_graph_op.match_mask_condition"));
        colMeshGrOp->setApplyMaskToAllDecendents(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.apply_mask_to_decendents"));
        colMeshGrOp->setApplyToNonMatching(MainApplication::the()->getSettings().get<bool>("player.debugger.trav_mask_graph_op.apply_to_non_matching"));
        colMeshGrOp->setNewTravMaskOperation(MainApplication::the()->getSettings().get<UInt8>("player.debugger.trav_mask_graph_op.apply_trav_mask_operation"));
        // default values for this graph op will do fine.
        if(colMeshGrOp->traverse(RootNode))
        {
	        SLOG << "Number of nodes changed to traversal mask " << NewTravMask << ": " << colMeshGrOp->getNumChanged() << std::endl;
        }
    }
}

std::string TravMaskCommand::getCommandDescription(void) const
{
	std::string Description("Recursively set Traversal Mask");
	
	return Description;
}

std::string TravMaskCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &TravMaskCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TravMaskCommand::~TravMaskCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TravMaskCommand::operator =(const TravMaskCommand& source)
{
}

