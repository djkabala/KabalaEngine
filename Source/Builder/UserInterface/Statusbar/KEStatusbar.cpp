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

#include "KEStatusbar.h"
#include "Builder/KEApplicationBuilder.h"
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Statusbar
The Statusbar. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Statusbar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Statusbar::createInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
	//Image Component for icon: lower left
	_IconComponent = TheApplicationBuilder->getIconManager()->createIconImageComponent("DefaultStatus");
	beginEditCP(_IconComponent, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		_IconComponent->setAlignment(Vec2f(0.5f,0.5f));
		_IconComponent->setScale(ImageComponent::SCALE_MIN_AXIS);
	endEditCP(_IconComponent, ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	

	//Descriptor Label: Fill Center
	_DiscriptorLabel = Label::create();
	beginEditCP(_DiscriptorLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
		_DiscriptorLabel->setBorders(NullFC);
		_DiscriptorLabel->setBackgrounds(NullFC);
		_DiscriptorLabel->setText("There IS no status.  Mwah ha ha!!!");
	endEditCP(_DiscriptorLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);


	//Progressbar: right
    _ProgressBarBoundedRangeModel = DefaultBoundedRangeModel::create();
    _ProgressBarBoundedRangeModel->setMinimum(0);
    _ProgressBarBoundedRangeModel->setMaximum(100);
    _ProgressBarBoundedRangeModel->setValue(50);
    _ProgressBarBoundedRangeModel->setExtent(0);

    _ProgressBar = ProgressBar::create();
	beginEditCP(_ProgressBar, ProgressBar::EnableProgressStringFieldMask | ProgressBar::IndeterminateFieldMask | ProgressBar::OrientationFieldMask | ProgressBar::PreferredSizeFieldMask | ProgressBar::RangeModelFieldMask);
        _ProgressBar->setEnableProgressString(false);
        _ProgressBar->setIndeterminate(false);
        _ProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
		_ProgressBar->setPreferredSize(Vec2f(100.0f, 25.0f));
        _ProgressBar->setRangeModel(_ProgressBarBoundedRangeModel);
    endEditCP(_ProgressBar, ProgressBar::EnableProgressStringFieldMask | ProgressBar::IndeterminateFieldMask | ProgressBar::OrientationFieldMask | ProgressBar::PreferredSizeFieldMask | ProgressBar::RangeModelFieldMask);
	
	//Layout
	SpringLayoutPtr StatusBarLayout = SpringLayout::create();

	//Image Component
	StatusBarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _IconComponent, 0, SpringLayoutConstraints::NORTH_EDGE, StatusbarPtr(this));
	StatusBarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _IconComponent, 0, SpringLayoutConstraints::SOUTH_EDGE, StatusbarPtr(this));
    StatusBarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _IconComponent, 0, SpringLayoutConstraints::WEST_EDGE, StatusbarPtr(this));
    StatusBarLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _IconComponent, 0, SpringLayoutConstraints::HEIGHT_EDGE, _IconComponent);

	//Progress Bar
	StatusBarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _ProgressBar, 0, SpringLayoutConstraints::NORTH_EDGE, StatusbarPtr(this));
	StatusBarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _ProgressBar, 0, SpringLayoutConstraints::SOUTH_EDGE, StatusbarPtr(this));
    StatusBarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ProgressBar, 0, SpringLayoutConstraints::EAST_EDGE, StatusbarPtr(this));
    StatusBarLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, _ProgressBar, LayoutSpring::width(_ProgressBar));

	//Descriptor Label
	StatusBarLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _DiscriptorLabel, 0, SpringLayoutConstraints::NORTH_EDGE, StatusbarPtr(this));
	StatusBarLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _DiscriptorLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, StatusbarPtr(this));
    StatusBarLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _DiscriptorLabel, 1, SpringLayoutConstraints::EAST_EDGE, _IconComponent);
    StatusBarLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _DiscriptorLabel, -1, SpringLayoutConstraints::WEST_EDGE, _ProgressBar);

	beginEditCP(StatusbarPtr(this), Statusbar::ChildrenFieldMask | Statusbar::LayoutFieldMask);
		getChildren().clear();
		getChildren().push_back(_IconComponent);
		getChildren().push_back(_DiscriptorLabel);
		getChildren().push_back(_ProgressBar);
		setLayout(StatusBarLayout);
	endEditCP(StatusbarPtr(this), Statusbar::ChildrenFieldMask | Statusbar::LayoutFieldMask);
}

void Statusbar::connectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Statusbar::disconnectInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Statusbar::updateInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Statusbar::destroyInterface(ApplicationBuilderPtr TheApplicationBuilder)
{
}

void Statusbar::setStatusIcon(std::string StatusIconName)
{
	//TODO: Implement
}

void Statusbar::setDescription(std::string Description)
{
	beginEditCP(_DiscriptorLabel, Label::TextFieldMask);
		_DiscriptorLabel->setText(Description);
	endEditCP(_DiscriptorLabel, Label::TextFieldMask);
}

std::string Statusbar::getDescription(void) const
{
	return _DiscriptorLabel->getText();
}

void Statusbar::setProgress(const Int32& Value)
{
	_ProgressBarBoundedRangeModel->setValue(Value);
}

Int32 Statusbar::getProgress(void) const
{
	return _ProgressBarBoundedRangeModel->getValue();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Statusbar::Statusbar(void) :
    Inherited()
{
}

Statusbar::Statusbar(const Statusbar &source) :
    Inherited(source)
{
}

Statusbar::~Statusbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Statusbar::changed(BitVector whichField, ::osg::UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Statusbar::dump(      ::osg::UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Statusbar NI" << std::endl;
}

