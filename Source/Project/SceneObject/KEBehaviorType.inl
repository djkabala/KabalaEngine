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
FieldContainerType *BehaviorType::getFieldContainerType()
{
	return behaviorFieldContainerType;
}
inline
BehaviorType *BehaviorType::getParent(void) const
{
    return _pParent;
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

inline
const const Scene* BehaviorType::getAttachedScene()
{
    return attachedScene;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool BehaviorType::isInitialized(void) const
{
    return _bInitialized;
}

OSG_END_NAMESPACE


#endif /* _KEBEHAVIORTYPE_INL_ */
