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
#include <OpenSG/OSGPathType.h>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/info_parser.hpp>

#include "KEApplicationSettings.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool ApplicationSettings::writeXML(const BoostPath& FilePath)
{
    try
    {
        boost::property_tree::xml_parser::write_xml(FilePath.string(), 
                                                    _PropertyTree, 
                                                    std::locale(), 
                                                    boost::property_tree::xml_parser::xml_writer_make_settings<typename boost::property_tree::ptree::key_type::value_type>(' ', 4));
    }
    catch(std::exception& ex)
    {
        SWARNING << "Failed to write settings to file: " << FilePath.string() 
                 << ", error: " << ex.what() << std::endl;
	    return false;
    }
	return true;
}

bool ApplicationSettings::readXML(const BoostPath& FilePath)
{
    try
    {
        boost::property_tree::xml_parser::read_xml(FilePath.string(), _PropertyTree);
    }
    catch(std::exception& ex)
    {
        SWARNING << "Failed to read settings from file: " << FilePath.string() 
                 << ", error: " << ex.what() << std::endl;
	    return false;
    }

	return true;
}

//bool ApplicationSettings::writeXML(OutputStreamType& Stream)
//{
//    try
//    {
//        //boost::property_tree::xml_parser::write_xml(Stream, _PropertyTree);
//    }
//    catch(std::exception& ex)
//    {
//        SWARNING << "Failed to write settings to stream, error: " << ex.what() << std::endl;
//	    return false;
//    }
//	return true;
//}

bool ApplicationSettings::readXML(InputStreamType& Stream)
{
    try
    {
        boost::property_tree::xml_parser::read_xml(Stream, _PropertyTree);
    }
    catch(std::exception& ex)
    {
        SWARNING << "Failed to read settings from stream, error: " << ex.what() << std::endl;
	    return false;
    }

	return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ApplicationSettings::ApplicationSettings(void)
{
}

ApplicationSettings::ApplicationSettings(const ApplicationSettings &source) :
_PropertyTree(source._PropertyTree)
{
}

ApplicationSettings::~ApplicationSettings(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ApplicationSettings::dump(      UInt32     uiIndent) const
{
    try
    {
        boost::property_tree::info_parser::write_info(SLOG, _PropertyTree);
    }
    catch(std::exception& ex)
    {
        SWARNING << "Failed to dump settings: " << ex.what() << std::endl;
    }
}

OSG_END_NAMESPACE
