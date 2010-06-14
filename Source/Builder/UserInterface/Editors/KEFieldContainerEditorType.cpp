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
#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "KEFieldContainerEditorType.h"
#include "KEFieldContainerEditorFactory.h"

OSG_BEGIN_NAMESPACE

FieldContainerEditorPtr FieldContainerEditorType::create(void) const
{
    if(!_CreationMethod.empty())
    {
        return _CreationMethod();
    }
    else
    {
        return FieldContainerEditorPtr();
    }
}

void FieldContainerEditorType::init(void) const
{
    if(!_InitializeMethod.empty())
    {
        _InitializeMethod();
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerEditorType::FieldContainerEditorType(const Char8  *szName,
                   const Char8  *szParentName,
                   FieldContainerEditorCreationMethod CreationMethod,
                   FieldContainerEditorInitMethod InitializeMethod,
                   const UInt32  uiNameSpace ) :
    Inherited(szName, szParentName, uiNameSpace),
    _uiFieldContainerEditorTypeId(0),
    _uiFieldContainerEditorTypeRootId(0),
    _CreationMethod(CreationMethod),
    _InitializeMethod(InitializeMethod)
{
    _uiFieldContainerEditorTypeId = FieldContainerEditorFactory::the()->registerType(this);
}

FieldContainerEditorType::FieldContainerEditorType(const FieldContainerEditorType &source) :
    Inherited(source),
    _uiFieldContainerEditorTypeId(source._uiFieldContainerEditorTypeId),
    _uiFieldContainerEditorTypeRootId(source._uiFieldContainerEditorTypeRootId),
    _CreationMethod(source._CreationMethod),
    _InitializeMethod(source._InitializeMethod)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerEditorType::~FieldContainerEditorType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool FieldContainerEditorType::operator ==(const FieldContainerEditorType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool FieldContainerEditorType::operator !=(const FieldContainerEditorType &other) const
{
    return ! (*this == other);
}

OSG_END_NAMESPACE
