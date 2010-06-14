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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEImportModelCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ImportModelCommand
A ImportModelCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType ImportModelCommand::_Type("ImportModelCommand", "UndoableCommand");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

ImportModelCommandPtr ImportModelCommand::create(HierarchyPanelRefPtr HierarchyPanel,NodeUnrecPtr NodeToAddTo)
{
	return RefPtr(new ImportModelCommand(HierarchyPanel,NodeToAddTo));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ImportModelCommand::execute(void)
{
    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;

    std::list< const Char8 * > ReadableModelSuff;
    SceneFileHandler::the()->getSuffixList(ReadableModelSuff, SceneFileType::OSG_READ_SUPPORTED);
    //Determine all of the readable model filetypes
    Filters.push_back(WindowEventProducer::FileDialogFilter("All Model filetypes",""));
    std::string AllModelSuffixes;
    std::string AllModelSuffixesDesc("All Model filetypes (");
    for(std::list<const Char8*>::const_iterator SuffixItor(ReadableModelSuff.begin()) ; SuffixItor != ReadableModelSuff.end() ; ++SuffixItor)
    {
        if(!AllModelSuffixes.empty())
        {
            AllModelSuffixes += ",";
            AllModelSuffixesDesc += ", ";
        }
        AllModelSuffixes += *SuffixItor;
        AllModelSuffixesDesc = AllModelSuffixesDesc + "*." + *SuffixItor;
        Filters.push_back(WindowEventProducer::FileDialogFilter(std::string(SceneFileHandler::the()->getFileType(*SuffixItor)->getName()) +  " (*." + *SuffixItor + ")",*SuffixItor));
    }
    AllModelSuffixesDesc += ")";
    Filters[0] = WindowEventProducer::FileDialogFilter(AllModelSuffixesDesc,AllModelSuffixes);
    Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

	std::vector<BoostPath> FilesToOpen;
    FilesToOpen = MainApplication::the()->getMainWindow()->openFileDialog("Import a model file.",
        Filters,
        BoostPath(".."),
        false);

	_NewNode = NULL;

    if(FilesToOpen.size() > 0)
    {
        //Try loading the file using the SceneFileHandler
        _NewNode = SceneFileHandler::the()->read(FilesToOpen[0].string().c_str());

        //Try loading the file using the XML file handler
        if(_NewNode == NULL)
        {
            _NewNode = dynamic_pointer_cast<Node>(FCFileHandler::the()->read(FilesToOpen[0], Node::getClassType()));
        }
    }


    if(_NodeToAddTo!=NULL && _NewNode != NULL)
	{
	    _HierarchyPanel->getSceneGraphTreeModel()->addNode(_NodeToAddTo,_NewNode);
	    _HasBeenDone = true;
    }
	
	_HasBeenDone = true;
}

std::string ImportModelCommand::getCommandDescription(void) const
{
	std::string Description("Imported Model");
	
	return Description;
}

std::string ImportModelCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

void ImportModelCommand::redo(void)
{
    Inherited::redo();

	if(_NewNode!=NULL)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->addNode(_NodeToAddTo,_NewNode);
	}

}

void ImportModelCommand::undo(void)
{
    Inherited::undo();

	if(_NewNode!=NULL)
	{
		_HierarchyPanel->getSceneGraphTreeModel()->removeNode(_NewNode);
	}

}

const CommandType &ImportModelCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ImportModelCommand::~ImportModelCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImportModelCommand::operator =(const ImportModelCommand& source)
{
}

