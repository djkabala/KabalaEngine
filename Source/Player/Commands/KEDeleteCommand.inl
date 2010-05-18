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

OSG_BEGIN_NAMESPACE

inline
DeleteCommand::DeleteCommand(ApplicationPlayerRefPtr ApplicationPlayer,
                             HierarchyPanelRefPtr HierarchyPanel,
                             NodeRefPtr DeleteNode) : Inherited(),
    _ApplicationPlayer(ApplicationPlayer),
    _HierarchyPanel(HierarchyPanel),
    _DeletedNode(DeleteNode),
    _Parent(NULL)
{
}

inline
DeleteCommand::DeleteCommand(const DeleteCommand& source) : Inherited(source),
    _ApplicationPlayer(source._ApplicationPlayer),
    _HierarchyPanel(source._HierarchyPanel),
    _DeletedNode(source._DeletedNode),
    _Parent(NULL)

{
}

inline 
const CommandType &DeleteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
