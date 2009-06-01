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

#ifndef _KEICONMANAGER_H_
#define _KEICONMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/Toolbox/OSGPathType.h>
#include "KEIconSet.h"

#include <map>
#include <string>

OSG_BEGIN_NAMESPACE

class IconManager;
typedef boost::intrusive_ptr<IconManager> IconManagerPtr;

class KE_KABALAENGINELIB_DLLMAPPING IconManager : public IntrusivePtrImplBase
{
   /*=========================  PUBLIC  ===============================*/
protected:
	friend class IconManagerManager;

	typedef IntrusivePtrImplBase Inherited;
    typedef IconManagerPtr  Ptr;
    typedef IconManager  Self;

	IconManager(void);

	IconManager(const IconManager& source);
	
    void operator =(const IconManager& source);

	typedef std::map<std::string, IconSetPtr> IconSetMap;

	IconSetMap _IconSetMap;

	virtual IconSetPtr createIconSet(const std::string& IconSetName);
	virtual TextureChunkPtr createTexture(const Path& TexturePath) = 0;
public:

	virtual ~IconManager();

	virtual TextureChunkPtr getIconTexture(const std::string& IconSetName, IconSet::IconStatusType Status = IconSet::ICON_NORMAL);

	virtual IconSetPtr getIconSet(const std::string& IconSetName);

	virtual ImageComponentPtr createIconImageComponent(const std::string& IconSetName);

	virtual ButtonPtr createButton(const std::string& IconSetName, Vec2f Size = Vec2f(-1.0f,-1.0f));
	virtual void applyIconSet(ButtonPtr TheButton, const std::string& IconSetName, Vec2f Size = Vec2f(-1.0f,-1.0f));
	
	virtual Path getTextureFilePath(const std::string& IconSetName, IconSet::IconStatusType Status) = 0;

	virtual bool canCreateIconSet(const std::string& IconSetName) = 0;
};


OSG_END_NAMESPACE

#include "KEIconManager.inl"

#endif /* _KEICONMANAGER_H_ */
