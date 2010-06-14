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

#include "KEDefaultIconManager.h"
#include "Application/KEApplicationSettings.h"
#include "Application/KEMainApplication.h"
#include <boost/filesystem.hpp>
#include <OpenSG/OSGImageFileHandler.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultIconManager
A DefaultIconManager. 
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

std::string DefaultIconManager::statusToString(IconSet::IconStatusType Status) const
{
	switch(Status)
	{
	case IconSet::ICON_NORMAL:
		return std::string("Normal");
		break;
	case IconSet::ICON_ROLLOVER:
		return std::string("Rollover");
		break;
	case IconSet::ICON_FOCUSED:
		return std::string("Focused");
		break;
	case IconSet::ICON_DISABLED:
		return std::string("Disabled");
		break;
	case IconSet::ICON_ACTIVE:
		return std::string("Active");
		break;
	default:
		return std::string("");
		break;
	}
}
	
Path DefaultIconManager::getTextureFilePath(const std::string& IconSetName, IconSet::IconStatusType Status)
{
	return Path(MainApplication::the()->getSettings()->getDataDirectory() / std::string("Images") / std::string("Icons") / IconSetName / (IconSetName + statusToString(Status) + std::string(".png")));
}

bool DefaultIconManager::canCreateIconSet(const std::string& IconSetName)
{
	return boost::filesystem::exists(Path(MainApplication::the()->getSettings()->getDataDirectory() / std::string("Images") / std::string("Icons") / IconSetName));
}

DefaultIconManagerPtr DefaultIconManager::create(void)
{
	return Ptr(new DefaultIconManager());
}


TextureChunkPtr DefaultIconManager::createTexture(const Path& TexturePath)
{
	if(boost::filesystem::exists(TexturePath))
	{
		ImagePtr LoadedImage = ImageFileHandler::the().read(TexturePath.string().c_str());
		if(LoadedImage != NullFC)
		{
			TextureChunkPtr NewTexture = TextureChunk::create();
			beginEditCP(NewTexture);
			{
				NewTexture->setImage(LoadedImage);
				NewTexture->setWrapS(GL_CLAMP);
				NewTexture->setWrapT(GL_CLAMP);
				NewTexture->setMinFilter(GL_LINEAR_MIPMAP_NEAREST);
				NewTexture->setMagFilter(GL_LINEAR);
				NewTexture->setEnvMode(GL_MODULATE);
			}
			endEditCP(NewTexture);

			return NewTexture;
		}
	}
	return NullFC;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultIconManager::~DefaultIconManager(void)
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

