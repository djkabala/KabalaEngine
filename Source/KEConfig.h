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

/*!{*/

/*! The printable Version string. Includes the full version with specifiers,
    e.g. "1.3.0pre1"
 */

const std::string KE_VERSION_STRING("0.0.1");
const std::string KE_BUILDER_VERSION_STRING("0.0.1");

/*! The numeric full version, with two digits per major/minor/release, e.g.
    010300
 */

const ::osg::UInt32 KE_VERSION(0x000001);
const ::osg::UInt32 KE_BUILDER_VERSION(0x000001);

/*! The numeric major version number, e.g. 1
 */

const osg::UInt16 KE_MAJOR_VERSION(0);
const osg::UInt16 KE_BUILDER_MAJOR_VERSION(0);

/*! The numeric minor version number, e.g. 4
 */

const osg::UInt16 KE_MINOR_VERSION(0);
const osg::UInt16 KE_BUILDER_MINOR_VERSION(0);

/*! The numeric release version number, e.g. 0
 */

const osg::UInt16 KE_RELEASE_VERSION(1);
const osg::UInt16 KE_BUILDER_RELEASE_VERSION(1);

const std::string KE_AUTHORS("David Kabala");
const std::string KE_BUILDER_AUTHORS("David Kabala");

#define BOOST_SMART_PTR_HPP

#endif /* _KECONFIG_H_ */
