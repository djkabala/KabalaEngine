/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
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

#ifndef _KEDEFAULTICONMANAGER_H_
#define _KEDEFAULTICONMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include "KEIconManager.h"

OSG_BEGIN_NAMESPACE

class DefaultIconManager;
typedef boost::intrusive_ptr<DefaultIconManager> DefaultIconManagerPtr;

class KE_KABALAENGINELIB_DLLMAPPING DefaultIconManager : public IconManager
{
   /*=========================  PUBLIC  ===============================*/
protected:

	typedef IconManager Inherited;
    typedef DefaultIconManagerPtr  Ptr;
    typedef DefaultIconManager  Self;

	DefaultIconManager(void);

	DefaultIconManager(const DefaultIconManager& source);
	
    void operator =(const DefaultIconManager& source);

	virtual TextureChunkPtr createTexture(const Path& TexturePath);

	std::string statusToString(IconSet::IconStatusType Status) const;
public:

	virtual ~DefaultIconManager();
	
	virtual Path getTextureFilePath(const std::string& IconSetName, IconSet::IconStatusType Status = IconSet::ICON_NORMAL);

	virtual bool canCreateIconSet(const std::string& IconSetName);

	static DefaultIconManagerPtr create(void);
};


OSG_END_NAMESPACE

#include "KEDefaultIconManager.inl"

#endif /* _KEDEFAULTICONMANAGER_H_ */
