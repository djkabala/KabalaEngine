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

#include "KEIconSet.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::IconSet
A IconSet. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

IconSetPtr IconSet::create(void)
{
	return Ptr(new IconSet());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


TextureChunkPtr IconSet::getTexture(IconStatusType Status)
{
	switch(Status)
	{
	case ICON_NORMAL:
		return _IconNormalTexture;
		break;
	case ICON_ROLLOVER:
		return _IconRolloverTexture;
		break;
	case ICON_FOCUSED:
		return _IconFocusedTexture;
		break;
	case ICON_DISABLED:
		return _IconDisabledTexture;
		break;
	case ICON_ACTIVE:
		return _IconActiveTexture;
		break;
	default:
		return NullFC;
		break;
	}
}

void IconSet::setTexture(IconStatusType Status, TextureChunkPtr Texture)
{
	switch(Status)
	{
	case ICON_NORMAL:
		setNormalTexture(Texture);
		break;
	case ICON_ROLLOVER:
		setRolloverTexture(Texture);
		break;
	case ICON_FOCUSED:
		setFocusedTexture(Texture);
		break;
	case ICON_DISABLED:
		setDisabledTexture(Texture);
		break;
	case ICON_ACTIVE:
		setActiveTexture(Texture);
		break;
	}
}

void IconSet::setNormalTexture(TextureChunkPtr Texture)
{
	if(_IconNormalTexture != NullFC)
	{
		subRefCP(_IconNormalTexture);
	}
	_IconNormalTexture = Texture;
	if(_IconNormalTexture != NullFC)
	{
		addRefCP(_IconNormalTexture);
	}
}

void IconSet::setRolloverTexture(TextureChunkPtr Texture)
{
	if(_IconRolloverTexture != NullFC)
	{
		subRefCP(_IconRolloverTexture);
	}
	_IconRolloverTexture = Texture;
	if(_IconRolloverTexture != NullFC)
	{
		addRefCP(_IconRolloverTexture);
	}
}

void IconSet::setFocusedTexture(TextureChunkPtr Texture)
{
	if(_IconFocusedTexture != NullFC)
	{
		subRefCP(_IconFocusedTexture);
	}
	_IconFocusedTexture = Texture;
	if(_IconFocusedTexture != NullFC)
	{
		addRefCP(_IconFocusedTexture);
	}
}

void IconSet::setDisabledTexture(TextureChunkPtr Texture)
{
	if(_IconDisabledTexture != NullFC)
	{
		subRefCP(_IconDisabledTexture);
	}
	_IconDisabledTexture = Texture;
	if(_IconDisabledTexture != NullFC)
	{
		addRefCP(_IconDisabledTexture);
	}
}

void IconSet::setActiveTexture(TextureChunkPtr Texture)
{
	if(_IconActiveTexture != NullFC)
	{
		subRefCP(_IconActiveTexture);
	}
	_IconActiveTexture = Texture;
	if(_IconActiveTexture != NullFC)
	{
		addRefCP(_IconActiveTexture);
	}
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

IconSet::~IconSet(void)
{
	if(_IconNormalTexture != NullFC)
	{
		subRefCP(_IconNormalTexture);
	}
	if(_IconRolloverTexture != NullFC)
	{
		subRefCP(_IconRolloverTexture);
	}
	if(_IconFocusedTexture != NullFC)
	{
		subRefCP(_IconFocusedTexture);
	}
	if(_IconDisabledTexture != NullFC)
	{
		subRefCP(_IconDisabledTexture);
	}
	if(_IconActiveTexture != NullFC)
	{
		subRefCP(_IconActiveTexture);
	}
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

