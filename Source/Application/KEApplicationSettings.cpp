/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include "KEConfig.h"

#include "KEApplicationSettings.h"
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

KE_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ApplicationSettings
The Main Application. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationSettings::initMethod (void)
{
}


ApplicationSettingsPtr ApplicationSettings::load(const Path& FilePath)
{
	return create(FilePath);
}

ApplicationSettingsPtr ApplicationSettings::create(const Path& FilePath)
{
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(FilePath);

	for(FCFileType::FCPtrStore::iterator Itor(NewContainers.begin()) ; Itor!= NewContainers.end() ; ++Itor)
	{
		if((*Itor)->getType() == ApplicationSettings::getClassType())
		{
			return ApplicationSettings::Ptr::dcast(*Itor);
		}
	}

	return NullFC;
}

ApplicationSettingsPtr ApplicationSettings::create(void)
{
    return ApplicationSettingsBase::create();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ApplicationSettings::save(const Path& FilePath)
{
	FCFileType::FCPtrStore Containers;
	Containers.insert(ApplicationSettingsPtr(this));

	FCFileType::FCTypeVector IgnoreTypes;

	FCFileHandler::the()->write(Containers,FilePath,IgnoreTypes);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationSettings::ApplicationSettings(void) :
    Inherited()
{
}

ApplicationSettings::ApplicationSettings(const ApplicationSettings &source) :
    Inherited(source)
{
}

ApplicationSettings::~ApplicationSettings(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationSettings::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ApplicationSettings::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ApplicationSettings NI" << std::endl;
}

