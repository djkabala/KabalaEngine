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

#include "KELogListComponentGenerator.h"
#include <OpenSG/OSGLabel.h>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLogListComponentGeneratorBase.cpp file.
// To modify it, please change the .fcd file (OSGLogListComponentGenerator.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LogListComponentGenerator::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
	
void LogListComponentGenerator::applyBordersAndBackground(Component* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
	if(IsSelected && HasFocus)
	{
		if(getFocusedBorderHasPriority())
		{
			TheComponent->setBorders(getFocusedBorder());
		}
		else
		{
			TheComponent->setBorders(getSelectedBorder());
		}
		if(getFocusedBackgroundHasPriority())
		{
			TheComponent->setBackgrounds(getFocusedBackground());
		}
		else
		{
			TheComponent->setBackgrounds(getSelectedBackground());
		}
	}
	else if(IsSelected)
	{
		TheComponent->setBorders(getSelectedBorder());
		TheComponent->setBackgrounds(getSelectedBackground());
	}
	else if(HasFocus)
	{
		TheComponent->setBorders(getFocusedBorder());
		TheComponent->setBackgrounds(getFocusedBackground());
	}
}

void LogListComponentGenerator::applyTextColor(TextComponent* const TheComponent, List* const Parent, const std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
    if(IsSelected && HasFocus)
    {
	    if(getFocusedTextColorHasPriority())
	    {
		    TheComponent->setTextColors(getFocusedTextColor());
	    }
	    else
	    {
		    TheComponent->setTextColors(getSelectedTextColor());
	    }
    }
    else if(IsSelected)
    {
        TheComponent->setTextColors(getSelectedTextColor());
    }
    else if(HasFocus)
    {
        TheComponent->setTextColors(getFocusedTextColor());
    }
    
    if(TheComponent->getType().isDerivedFrom(Label::getClassType()))
    {
        dynamic_cast<Label* const>(TheComponent)->setTextSelectable(true);
    }
}

std::string LogListComponentGenerator::getText(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) const
{
	if(Value.empty()){
		return std::string("");
	}

	std::string ValueString;
    try
    {
        ValueString = boost::any_cast<std::string>(Value);
    }
    catch (boost::bad_any_cast &ex)
    {
        //Could not convert to string
        SWARNING << "Bad any cast: " << ex.what() << std::endl;
    }
    return ValueString;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LogListComponentGenerator::LogListComponentGenerator(void) :
    Inherited()
{
}

LogListComponentGenerator::LogListComponentGenerator(const LogListComponentGenerator &source) :
    Inherited(source)
{
}

LogListComponentGenerator::~LogListComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LogListComponentGenerator::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LogListComponentGenerator::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LogListComponentGenerator NI" << std::endl;
}

OSG_END_NAMESPACE
