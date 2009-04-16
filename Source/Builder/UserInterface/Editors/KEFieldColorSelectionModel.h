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

#ifndef _KE_FIELD_COLOR_SELECTION_MODEL_H_
#define _KE_FIELD_COLOR_SELECTION_MODEL_H_

#include "KEConfig.h"
#include "KEKabalaEngineDef.h"

#include <OpenSG/UserInterface/OSGAbstractColorSelectionModel.h>

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

class KE_KABALAENGINELIB_DLLMAPPING FieldColorSelectionModel : public AbstractColorSelectionModel
{
    /*==========================  PUBLIC  =================================*/
  public:
	  
	virtual Color4f getSelectedColor(void) const;

	virtual void setSelectedColor(const Color4f& Value);

    void attachColorField(FieldContainerPtr Target, UInt32 FieldId);

  protected:
    FieldContainerPtr _Target;
    UInt32            _ColorFieldID;

    /*==========================  PRIVATE  ================================*/
  private:
};

typedef FieldColorSelectionModel *FieldColorSelectionModelPtr;

KE_END_NAMESPACE

#include "KEFieldColorSelectionModel.inl"

#endif /* _KE_FIELD_COLOR_SELECTION_MODEL_H_ */
