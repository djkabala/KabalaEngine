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
#include "KEPlatformUtils.h"
#include <boost/lexical_cast.hpp>

#ifdef __APPLE__
#include "CoreServices/CoreServices.h"
#include <mach-o/arch.h>
#endif

OSG_BEGIN_NAMESPACE

#ifdef __APPLE__
std::string getPlatformName(void)
{
    SInt32 verMajor, verMinor, verPatch;
    Gestalt( gestaltSystemVersionMajor, &verMajor );
    Gestalt( gestaltSystemVersionMinor, &verMinor );
    Gestalt( gestaltSystemVersionBugFix, &verPatch );

    return std::string("Mac OS X ") + boost::lexical_cast<std::string>(verMajor)
                              + "." + boost::lexical_cast<std::string>(verMinor)
                              + "." + boost::lexical_cast<std::string>(verPatch);
}

std::string getPlatformProcessors(void)
{
    const NXArchInfo* ArchInfo = NXGetLocalArchInfo();
    if(ArchInfo != NULL)
    {
        return std::string(ArchInfo->description);
    }
    else
    {
        return std::string("Unknown");
    }
}

std::string getPlatformRAM(void)
{
    SInt32 sizeInBytes;
    Gestalt( gestaltPhysicalRAMSize, &sizeInBytes );
    return boost::lexical_cast<std::string>(sizeInBytes/1000000) + " Mb";
}

std::string getPlatformGraphicsChips(void)
{
    return "NYI";
}

bool openFile(const BoostPath& FileToOpen)
{
    return false;
}

#endif

#ifdef WIN32
std::string getPlatformName(void)
{
    return "NYI";
}

std::string getPlatformProcessors(void)
{
    return "NYI";
}

std::string getPlatformRAM(void)
{
    return "NYI";
}

std::string getPlatformGraphicsChips(void)
{
    return "NYI";
}

bool openFile(const BoostPath& FileToOpen)
{
    return false;
}

#endif

#ifdef __linux
std::string getPlatformName(void)
{
    return "NYI";
}

std::string getPlatformProcessors(void)
{
    return "NYI";
}

std::string getPlatformRAM(void)
{
    return "NYI";
}

std::string getPlatformGraphicsChips(void)
{
    return "NYI";
}

bool openFile(const BoostPath& FileToOpen)
{
    return false;
}

#endif

OSG_END_NAMESPACE
