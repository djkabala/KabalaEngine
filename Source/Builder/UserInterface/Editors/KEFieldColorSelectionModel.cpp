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

#include <OpenSG/OSGConfig.h>

#include "KEFieldColorSelectionModel.h"
#include <OpenSG/OSGFieldDescription.h>
#include <OpenSG/OSGBaseFieldDataType.h>
#include <OpenSG/OSGSFBaseTypes.h>
#include <OpenSG/OSGField.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FieldColorSelectionModel
A FieldColorSelectionModel. 
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

Color4f FieldColorSelectionModel::getSelectedColor(void) const
{
    if(_Target != NullFC &&
        _Target->getType().getNumFieldDescs() > _ColorFieldID)
    {

        if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color3f >::getType())
        {
            Color3f Value(dynamic_cast<SFColor3f*>(_Target->getField(_ColorFieldID))->getValue());
            return Color4f( Value.red(),Value.green(),Value.blue(), 1.0 );
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color3ub >::getType())
        {
            Color3ub Value(dynamic_cast<SFColor3ub*>(_Target->getField(_ColorFieldID))->getValue());
            return Color4f( Value.red(),Value.green(),Value.blue(), 1.0 );
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color4f >::getType())
        {
            return dynamic_cast<SFColor4f*>(_Target->getField(_ColorFieldID))->getValue();
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color4ub >::getType())
        {
            Color4ub Value(dynamic_cast<SFColor4ub*>(_Target->getField(_ColorFieldID))->getValue());
            return Color4f( Value.red(),Value.green(),Value.blue(), Value.alpha() );
        }
    }

    return Color4f();
}

void FieldColorSelectionModel::setSelectedColor(const Color4f& Value, bool isValueAdjusting)
{
	_IsValueAdjusting = isValueAdjusting;
    if(_Target != NullFC &&
        _Target->getType().getNumFieldDescs() > _ColorFieldID)
    {

        if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color3f >::getType())
        {
            dynamic_cast<SFColor3f*>(_Target->getField(_ColorFieldID))->setValue( Color3f(Value.red(),Value.green(),Value.blue()) );
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color3ub >::getType())
        {
            dynamic_cast<SFColor3ub*>(_Target->getField(_ColorFieldID))->setValue( Color3ub(Value.red(),Value.green(),Value.blue()) );
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color4f >::getType())
        {
            dynamic_cast<SFColor4f*>(_Target->getField(_ColorFieldID))->setValue( Value );
        }
        else if(_Target->getField(_ColorFieldID)->getContentType() == FieldDataTraits< Color4ub >::getType())
        {
            dynamic_cast<SFColor4ub*>(_Target->getField(_ColorFieldID))->setValue( Color4ub(Value.red(),Value.green(),Value.blue(), Value.alpha()) );
        }
		produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}


void FieldColorSelectionModel::attachColorField(FieldContainerPtr Target, UInt32 FieldId)
{
    _Target = NullFC;
    _ColorFieldID = 0;
    if(Target != NullFC &&
        Target->getType().getNumFieldDescs() > FieldId)
    {

        if(Target->getField(FieldId)->getCardinality() == FieldType::SINGLE_FIELD &&
            (Target->getField(FieldId)->getContentType() == FieldDataTraits< Color3f >::getType() ||
                Target->getField(FieldId)->getContentType() == FieldDataTraits< Color3ub >::getType() ||
                Target->getField(FieldId)->getContentType() == FieldDataTraits< Color4f >::getType() ||
                Target->getField(FieldId)->getContentType() == FieldDataTraits< Color4ub >::getType()))
        {
            _Target = Target;
            _ColorFieldID = FieldId;
        }
    }
    produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FieldColorSelectionModel::FieldColorSelectionModel(void) : _IsValueAdjusting(false)
{
}

/*----------------------------- class specific ----------------------------*/
OSG_END_NAMESPACE

