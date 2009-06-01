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

#ifndef _KEICONSET_H_
#define _KEICONSET_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>
#include <OpenSG/OSGTextureChunk.h>

OSG_BEGIN_NAMESPACE

class IconSet;
typedef boost::intrusive_ptr<IconSet> IconSetPtr;

class KE_KABALAENGINELIB_DLLMAPPING IconSet : public IntrusivePtrImplBase
{
   /*=========================  PUBLIC  ===============================*/
protected:
	friend class IconSetManager;

	typedef IntrusivePtrImplBase Inherited;
    typedef IconSetPtr  Ptr;
    typedef IconSet  Self;

	IconSet(void);

	IconSet(const IconSet& source);
	
    void operator =(const IconSet& source);

	TextureChunkPtr _IconNormalTexture;
	TextureChunkPtr _IconRolloverTexture;
	TextureChunkPtr _IconFocusedTexture;
	TextureChunkPtr _IconDisabledTexture;
	TextureChunkPtr _IconActiveTexture;
public:
	enum IconStatusType{ICON_NORMAL=0, ICON_ROLLOVER, ICON_FOCUSED, ICON_DISABLED, ICON_ACTIVE};

	virtual ~IconSet();

	virtual TextureChunkPtr getTexture(IconStatusType Status = ICON_NORMAL);
	virtual void setTexture(IconStatusType Status, TextureChunkPtr Texture);
	
	virtual void setNormalTexture(TextureChunkPtr Texture);
	virtual void setRolloverTexture(TextureChunkPtr Texture);
	virtual void setFocusedTexture(TextureChunkPtr Texture);
	virtual void setDisabledTexture(TextureChunkPtr Texture);
	virtual void setActiveTexture(TextureChunkPtr Texture);

	static IconSetPtr create(void);
};


OSG_END_NAMESPACE

#include "KEIconSet.inl"

#endif /* _KEICONSET_H_ */
