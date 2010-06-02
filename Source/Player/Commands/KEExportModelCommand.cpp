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

#include "KEExportModelCommand.h"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGFCFileHandler.h>
#include <OpenSG/OSGWindowEventProducer.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::ExportModelCommand
A ExportModelCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType ExportModelCommand::_Type("ExportModelCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

ExportModelCommandPtr ExportModelCommand::create(NodeUnrecPtr ExportNode)
{
	return RefPtr(new ExportModelCommand(ExportNode));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ExportModelCommand::execute(void)
{
    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;

    std::list< const Char8 * > WritableModelSuff;
    SceneFileHandler::the()->getSuffixList(WritableModelSuff, SceneFileType::OSG_WRITE_SUPPORTED);
    //Determine all of the readable model filetypes
    Filters.push_back(WindowEventProducer::FileDialogFilter("All Model filetypes",""));
    std::string AllModelSuffixes;
    std::string AllModelSuffixesDesc("All Model filetypes (");
    for(std::list<const Char8*>::const_iterator SuffixItor(WritableModelSuff.begin()) ; SuffixItor != WritableModelSuff.end() ; ++SuffixItor)
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

	BoostPath FileToSave;
    FileToSave = MainApplication::the()->getMainWindow()->saveFileDialog("Export a model file.",
        Filters,
        std::string("ExportedModel.osb"),
        BoostPath(".."),
        true);

    if(_ExportNode != NULL)
    {
        //Try saving the file using the SceneFileHandler
        SceneFileHandler::the()->write(_ExportNode, FileToSave.string().c_str());
    }
}

std::string ExportModelCommand::getCommandDescription(void) const
{
	std::string Description("Export Model Node");
	
	return Description;
}

std::string ExportModelCommand::getPresentationName(void) const
{
	return getCommandDescription();
}

const CommandType &ExportModelCommand::getType(void) const
{
	return _Type;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ExportModelCommand::~ExportModelCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ExportModelCommand::operator =(const ExportModelCommand& source)
{
}

