/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *            Authors: David Kabala,Eric Langkamp,Robert Goetz               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
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

#ifndef _KEBEHAVIORTYPE_INL_
#define _KEBEHAVIORTYPE_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
BehaviorType *BehaviorType::getParent(void) const
{
    return _pParent;
}

inline
std::vector<std::string> BehaviorType::getLuaFunctionNames()
{
	return luaFunctionNames;
}

inline
std::string BehaviorType::getCode()
{
	return TheCode;
}

inline
const std::vector<std::string> BehaviorType::getEvents()
{
    return _bEvents;
}

inline
const std::vector<std::string> BehaviorType::getEventLinks()
{
    return _bEventLinks;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

inline
void BehaviorType::setCode(std::string bCode)
{
	TheCode = bCode;
}

/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool BehaviorType::isInitialized(void) const
{
    return _bInitialized;
}

OSG_END_NAMESPACE


#endif /* _KEBEHAVIORTYPE_INL_ */
