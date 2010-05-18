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

#include "KEApplicationSettings.h"
#include <OpenSG/OSGFCFileHandler.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGApplicationSettingsBase.cpp file.
// To modify it, please change the .fcd file (OSGApplicationSettings.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ApplicationSettings::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

ApplicationSettingsUnrecPtr ApplicationSettings::load(const BoostPath& FilePath)
{
	return create(FilePath);
}

ApplicationSettingsUnrecPtr ApplicationSettings::create(const BoostPath& FilePath)
{
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(FilePath);

	for(FCFileType::FCPtrStore::iterator Itor(NewContainers.begin()) ; Itor!= NewContainers.end() ; ++Itor)
	{
		if((*Itor)->getType() == ApplicationSettings::getClassType())
		{
			return dynamic_pointer_cast<ApplicationSettings>(*Itor);
		}
	}

	return ApplicationSettingsTransitPtr();
}

ApplicationSettingsTransitPtr ApplicationSettings::create(void)
{
    return ApplicationSettingsBase::create();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ApplicationSettings::save(const BoostPath& FilePath)
{
	FCFileType::FCPtrStore Containers;
	Containers.insert(ApplicationSettingsRefPtr(this));

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

void ApplicationSettings::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ApplicationSettings::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ApplicationSettings NI" << std::endl;
}

OSG_END_NAMESPACE
