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

OSG_BEGIN_NAMESPACE

inline
UndoManagerPtr ApplicationBuilder::getUndoManager(void) const
{
	return _UndoManager;
}

inline
CommandManagerPtr ApplicationBuilder::getCommandManager(void) const
{
	return _CommandManager;
}

inline
UIDrawingSurface* ApplicationBuilder::getDrawingSurface(void) const
{
	return _BuilderDrawingSurface;
}

inline
UIForeground* ApplicationBuilder::getForeground(void) const
{
	return _BuilderForeground;
}

inline
Viewport* ApplicationBuilder::getViewport(void) const
{
	return _BuilderViewport;
}

inline
boost::signals2::connection ApplicationBuilder::connectSelectionChanged(const ListSelectionModel::SelectionChangedEventType::slot_type &listener,
                                                   boost::signals2::connect_position at)
{
    return getSelectionModel()->connectSelectionChanged(listener,at);
}

inline
boost::signals2::connection ApplicationBuilder::connectSelectionChanged(const ListSelectionModel::SelectionChangedEventType::group_type &group,
                                                   const ListSelectionModel::SelectionChangedEventType::slot_type &listener,
                                                   boost::signals2::connect_position at)
{
    return getSelectionModel()->connectSelectionChanged(group,listener,at);
}

inline
void   ApplicationBuilder::disconnectSelectionChanged       (const ListSelectionModel::SelectionChangedEventType::group_type &group)
{
    getSelectionModel()->disconnectSelectionChanged(group);
}

inline
void   ApplicationBuilder::disconnectAllSlotsSelectionChanged(void)
{
    getSelectionModel()->disconnectAllSlotsSelectionChanged();
}

inline
bool   ApplicationBuilder::isEmptySelectionChanged          (void) const
{
    return getSelectionModel()->isEmptySelectionChanged();
}

inline
UInt32 ApplicationBuilder::numSlotsSelectionChanged         (void) const
{
    return getSelectionModel()->numSlotsSelectionChanged();
}


OSG_END_NAMESPACE
