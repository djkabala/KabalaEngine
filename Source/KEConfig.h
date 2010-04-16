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

#ifndef _KECONFIG_H_
#define _KECONFIG_H_

#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include <string>

/*-------------------------------------------------------------------------*/
/*                                Versioning                               */

/*! @name Version Defines
 */
#ifndef WIN32

#include <KEVersion.h>

#else

inline
::osg::UInt32 getKabalaEngineMajorVersion(void)
{
	return 0;
}

inline
::osg::UInt32 getKabalaEngineMinorVersion(void)
{
	return 3;
}

inline
::osg::UInt32 getKabalaEnginePatchVersion(void)
{
	return 0;
}

inline
std::string getKabalaEngineVersion(void)
{
	return "0.3.0";
}

inline
::osg::UInt32 getKabalaEngineBuilderMajorVersion(void)
{
	return 0;
}

inline
::osg::UInt32 getKabalaEngineBuilderMinorVersion(void)
{
	return 3;
}

inline
::osg::UInt32 getKabalaEngineBuilderPatchVersion(void)
{
	return 0;
}

inline
std::string getKabalaEngineBuilderVersion(void)
{
	return "0.3.0";
}

inline
std::string getKabalaEngineBuildType(void)
{
	return "Debug";
}

inline
std::string getKabalaEngineBuildRepositoryRevision(void)
{
	return "164";
}

inline
std::string getKabalaEngineAuthors(void)
{
	return "David Kabala <djkabala@gmail.com>";
}

inline
std::string getKabalaEngineWebsite(void)
{
	return "http://www.vrac.iastate.edu/~dkabala/KabalaEngine/";
}

inline
std::string getKabalaEngineBuilderAuthors()
{
	return "David Kabala <djkabala@gmail.com>";
}

#endif

#define BOOST_SMART_PTR_HPP

#endif /* _KECONFIG_H_ */
