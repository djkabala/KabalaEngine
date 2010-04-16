/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#define KE_COMPILEKABALAENGINELIB

#include <OpenSG/OSGConfig.h>

#include "KEIconManager.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::IconManager
A IconManager. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

IconSetPtr IconManager::createIconSet(const std::string& IconSetName)
{
	if(canCreateIconSet(IconSetName))
	{
		IconSetPtr NewSet = IconSet::create();
		NewSet->setTexture(IconSet::ICON_NORMAL, createTexture(getTextureFilePath(IconSetName,IconSet::ICON_NORMAL)));
		NewSet->setTexture(IconSet::ICON_ROLLOVER, createTexture(getTextureFilePath(IconSetName,IconSet::ICON_ROLLOVER)));
		NewSet->setTexture(IconSet::ICON_FOCUSED, createTexture(getTextureFilePath(IconSetName,IconSet::ICON_FOCUSED)));
		NewSet->setTexture(IconSet::ICON_DISABLED, createTexture(getTextureFilePath(IconSetName,IconSet::ICON_DISABLED)));
		NewSet->setTexture(IconSet::ICON_ACTIVE, createTexture(getTextureFilePath(IconSetName,IconSet::ICON_ACTIVE)));

		return NewSet;
	}
	else
	{
		return NULL;
	}
}

IconSetPtr IconManager::getIconSet(const std::string& IconSetName)
{
	IconSetMap::const_iterator SearchItor(_IconSetMap.find(IconSetName));

	if(SearchItor == _IconSetMap.end())
	{
		//Attempt to create it
		IconSetPtr NewSet = createIconSet(IconSetName);

		if(NewSet != NULL)
		{
			_IconSetMap[IconSetName] = NewSet;
		}

		return NewSet;
	}
	else
	{
		return SearchItor->second;
	}
}

TextureChunkPtr IconManager::getIconTexture(const std::string& IconSetName, IconSet::IconStatusType Status)
{
	IconSetPtr TheSet(getIconSet(IconSetName));
	if(TheSet != NULL)
	{
		return TheSet->getTexture(Status);
	}
	else
	{
		return NullFC;
	}
}

ImageComponentPtr IconManager::createIconImageComponent(const std::string& IconSetName)
{
	IconSetPtr TheSet(getIconSet(IconSetName));
	if(TheSet != NULL)
	{
		//Editor Icon
		ImageComponentPtr IconImageComponent = ImageComponent::create();
		beginEditCP(IconImageComponent, ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::FocusedTextureFieldMask | ImageComponent::DisabledTextureFieldMask);
			IconImageComponent->setTexture(TheSet->getTexture(IconSet::ICON_NORMAL));
			IconImageComponent->setRolloverTexture(TheSet->getTexture(IconSet::ICON_ROLLOVER));
			IconImageComponent->setFocusedTexture(TheSet->getTexture(IconSet::ICON_FOCUSED));
			IconImageComponent->setDisabledTexture(TheSet->getTexture(IconSet::ICON_DISABLED));
			IconImageComponent->setScale(ImageComponent::SCALE_MIN_AXIS);
		endEditCP(IconImageComponent, ImageComponent::TextureFieldMask | ImageComponent::RolloverTextureFieldMask | ImageComponent::FocusedTextureFieldMask | ImageComponent::DisabledTextureFieldMask);

		return IconImageComponent;
	}
	else
	{
		return ImageComponent::create();
	}

}


ButtonPtr IconManager::createButton(const std::string& IconSetName, Vec2f Size)
{
	ButtonPtr IconButton = ::osg::Button::create();

    applyIconSet(IconButton, IconSetName, Size);

	return IconButton;
}

void IconManager::applyIconSet(ButtonPtr TheButton, const std::string& IconSetName, Vec2f Size)
{
    
	IconSetPtr TheSet(getIconSet(IconSetName));
	if(TheSet != NULL && TheButton != NullFC)
	{
	    TheButton->setTexture(TheSet->getTexture(IconSet::ICON_NORMAL), Size);
	    if(TheSet->getTexture(IconSet::ICON_ROLLOVER) != NullFC)
	    {
		    TheButton->setRolloverTexture(TheSet->getTexture(IconSet::ICON_ROLLOVER), Size);
	    }
	    else
	    {
		    TheButton->setRolloverTexture(TheSet->getTexture(IconSet::ICON_NORMAL), Size);
	    }
	    if(TheSet->getTexture(IconSet::ICON_FOCUSED) != NullFC)
	    {
		    TheButton->setFocusedTexture(TheSet->getTexture(IconSet::ICON_FOCUSED), Size);
	    }
	    else
	    {
		    TheButton->setFocusedTexture(TheSet->getTexture(IconSet::ICON_NORMAL), Size);
	    }
	    if(TheSet->getTexture(IconSet::ICON_DISABLED) != NullFC)
	    {
		    TheButton->setDisabledTexture(TheSet->getTexture(IconSet::ICON_DISABLED), Size);
	    }
	    else
	    {
		    TheButton->setDisabledTexture(TheSet->getTexture(IconSet::ICON_NORMAL), Size);
	    }
	    if(TheSet->getTexture(IconSet::ICON_ACTIVE) != NullFC)
	    {
		    TheButton->setActiveTexture(TheSet->getTexture(IconSet::ICON_ACTIVE), Size);
	    }
	    else
	    {
		    TheButton->setActiveTexture(TheSet->getTexture(IconSet::ICON_NORMAL), Size);
	    }
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

IconManager::~IconManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

