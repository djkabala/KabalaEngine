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

#include <OSGConfig.h>

#include "KELogListModel.h"
#include "Application/Logging/KELogEventDetails.h"
#include "Application/KEMainApplication.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLogListModelBase.cpp file.
// To modify it, please change the .fcd file (OSGLogListModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LogListModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 LogListModel::getSize(void) const
{
    return _Logs.size();
}

boost::any LogListModel::getElementAt(UInt32 index) const
{
    return boost::any(_Logs[index]);
}

boost::signals2::connection LogListModel::connectLogging(void)
{
    _LogConnection.disconnect();
    _LogConnection = MainApplication::the()->connectLog(boost::bind(&LogListModel::handleLogEvent, this, _1));
    return _LogConnection;
}

void LogListModel::disconnectLogging(void)
{
    _LogConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void LogListModel::resolveLinks(void)
{
    Inherited::resolveLinks();

    _LogConnection.disconnect();
}

void LogListModel::handleLogEvent(LogEventDetails* const details)
{
    //Add the new Log
    _Logs.push_back(details->getValue());

    produceListDataIntervalAdded(this, _Logs.size(), _Logs.size());

    updateSize();
}

void LogListModel::updateSize(void)
{
    //Remove Logs if necissary
    if(_Logs.size() > getMaxLogSize())
    {
        UInt32 NumToRemove(_Logs.size() - getMaxLogSize());
        //Remove range
        _Logs.erase(_Logs.begin(), _Logs.begin() + NumToRemove);

        produceListDataIntervalRemoved(this, 0, NumToRemove-1);
    }
}

/*----------------------- constructors & destructors ----------------------*/

LogListModel::LogListModel(void) :
    Inherited()
{
}

LogListModel::LogListModel(const LogListModel &source) :
    Inherited(source)
{
}

LogListModel::~LogListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LogListModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & MaxLogSizeFieldMask)
    {
        updateSize();
    }
}

void LogListModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LogListModel NI" << std::endl;
}

OSG_END_NAMESPACE
