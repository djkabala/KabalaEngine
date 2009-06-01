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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEFieldContainerTypeComponentGenerator.h"
#include <OpenSG/OSGBackground.h>
#include <OpenSG/UserInterface/OSGComponent.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGTextComponent.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/UserInterface/OSGDefaultListComponentGenerator.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FieldContainerTypeComponentGenerator

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FieldContainerTypeComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr FieldContainerTypeComponentGenerator::getListComponent(::osg::ListPtr Parent, const boost::any& Value, ::osg::UInt32 Index, bool IsSelected, bool HasFocus)
{
	if(Value.empty()){
			return Panel::createEmpty();
	}

    FieldContainerType* TheFCType;
    try
    {
        TheFCType = boost::any_cast<FieldContainerType*>(Value);
    }
    catch(boost::bad_any_cast &)
    {
        return Panel::createEmpty();
    }

    if(TheFCType == NULL)
    {
        return Panel::createEmpty();
    }

	//Default Prototype
	DefaultListComponentGeneratorPtr DefaultPrototype = DefaultListComponentGenerator::Ptr::dcast(DefaultListComponentGenerator::getClassType().getPrototype());

	//Label
	ComponentPtr TheLabelComponent = ::osg::Component::Ptr::dcast(DefaultPrototype->getDrawObjectPrototype()->shallowCopy());
	beginEditCP(TheLabelComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
		TheLabelComponent->setBorders(NullFC);
		TheLabelComponent->setBackgrounds(NullFC);
	endEditCP(TheLabelComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);

	if(TheLabelComponent->getType().isDerivedFrom(TextComponent::getClassType()))
	{
		std::string ValueString(TheFCType->getCName());

		beginEditCP(TheLabelComponent, TextComponent::TextFieldMask);
			TextComponent::Ptr::dcast(TheLabelComponent)->setText(ValueString);
		endEditCP(TheLabelComponent, TextComponent::TextFieldMask);
		if(IsSelected && HasFocus)
		{
			beginEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
			if(DefaultPrototype->getFocusedTextColorHasPriority())
			{
				TextComponent::Ptr::dcast(TheLabelComponent)->setTextColors(DefaultPrototype->getFocusedTextColor());
			}
			else
			{
				TextComponent::Ptr::dcast(TheLabelComponent)->setTextColors(DefaultPrototype->getSelectedTextColor());
			}
			endEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
		}
		else if(IsSelected)
		{
			beginEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
				TextComponent::Ptr::dcast(TheLabelComponent)->setTextColors(DefaultPrototype->getSelectedTextColor());
			endEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
		}
		else if(HasFocus)
		{
			beginEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
				TextComponent::Ptr::dcast(TheLabelComponent)->setTextColors(DefaultPrototype->getFocusedTextColor());
			endEditCP(TheLabelComponent, TextComponent::TextColorsFieldMask);
		}
	}

	//Icon
	ImageComponentPtr TheIconComponent(NullFC);
	if(_IconManager != NULL)
	{
		TheIconComponent = _IconManager->createIconImageComponent(TheFCType->getCName());
	}
	if(TheIconComponent ==  NullFC)
	{
		TheIconComponent = _IconManager->createIconImageComponent("UnknownType");
	}
	if(TheIconComponent ==  NullFC)
	{
		TheIconComponent = ImageComponent::create();
	}
	beginEditCP(TheIconComponent, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | ImageComponent::PreferredSizeFieldMask);
		TheIconComponent->setAlignment(Vec2f(0.5f, 0.5f));
		TheIconComponent->setScale(ImageComponent::SCALE_MIN_AXIS);
		TheIconComponent->setPreferredSize(getIconSize());
	endEditCP(TheIconComponent, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask | ImageComponent::PreferredSizeFieldMask);

	//Panel
	PanelPtr TheComponent = Panel::create();
	
	//Layout
	SpringLayoutPtr ComponentLayout = SpringLayout::create();

	//Editor Icon
    ComponentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIconComponent, 0, SpringLayoutConstraints::WEST_EDGE, TheComponent);
	ComponentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIconComponent, 0, SpringLayoutConstraints::NORTH_EDGE, TheComponent);
	ComponentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheIconComponent, 0, SpringLayoutConstraints::SOUTH_EDGE, TheComponent);
	ComponentLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIconComponent, LayoutSpring::width(TheIconComponent));
	
	//Editor Label
    ComponentLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheLabelComponent, 1, SpringLayoutConstraints::EAST_EDGE, TheIconComponent);
    ComponentLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheLabelComponent, 0, SpringLayoutConstraints::EAST_EDGE, TheComponent);
	ComponentLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheLabelComponent, 0, SpringLayoutConstraints::NORTH_EDGE, TheComponent);
	ComponentLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheLabelComponent, 0, SpringLayoutConstraints::SOUTH_EDGE, TheComponent);

	beginEditCP(TheComponent, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		TheComponent->getChildren().push_back(TheIconComponent);
		TheComponent->getChildren().push_back(TheLabelComponent);
		TheComponent->setLayout(ComponentLayout);
		TheComponent->setPreferredSize(Vec2f(150.0f,32.0f));
	endEditCP(TheComponent, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	
	//Border & Background
	if(IsSelected && HasFocus)
	{
		beginEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
			if(DefaultPrototype->getFocusedBorderHasPriority())
			{
				TheComponent->setBorders(DefaultPrototype->getFocusedBorder());
			}
			else
			{
				TheComponent->setBorders(DefaultPrototype->getSelectedBorder());
			}
			if(DefaultPrototype->getFocusedBackgroundHasPriority())
			{
				TheComponent->setBackgrounds(DefaultPrototype->getFocusedBackground());
			}
			else
			{
				TheComponent->setBackgrounds(DefaultPrototype->getSelectedBackground());
			}
		endEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
	}
	else if(IsSelected)
	{
		beginEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
			TheComponent->setBorders(DefaultPrototype->getSelectedBorder());
			TheComponent->setBackgrounds(DefaultPrototype->getSelectedBackground());
		endEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
	}
	else if(HasFocus)
	{
		beginEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
			TheComponent->setBorders(DefaultPrototype->getFocusedBorder());
			TheComponent->setBackgrounds(DefaultPrototype->getFocusedBackground());
		endEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
	}
	else
	{
		beginEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
			TheComponent->setBorders(NullFC);
			TheComponent->setBackgrounds(NullFC);
		endEditCP(TheComponent, ::osg::Component::BordersFieldMask | ::osg::Component::BackgroundsFieldMask);
	}
	return TheComponent;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldContainerTypeComponentGenerator::FieldContainerTypeComponentGenerator(void) :
    Inherited()
{
}

FieldContainerTypeComponentGenerator::FieldContainerTypeComponentGenerator(const FieldContainerTypeComponentGenerator &source) :
    Inherited(source)
{
}

FieldContainerTypeComponentGenerator::~FieldContainerTypeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FieldContainerTypeComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FieldContainerTypeComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FieldContainerTypeComponentGenerator NI" << std::endl;
}

