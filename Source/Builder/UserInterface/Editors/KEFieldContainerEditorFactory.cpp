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
#include "KEConfig.h"

#include <iostream>

#include "KEFieldContainerEditorFactory.h"

KE_BEGIN_NAMESPACE

FieldContainerEditorFactory *FieldContainerEditorFactory::_the = NULL;

FieldContainerEditorFactory *FieldContainerEditorFactory::the(void)
{
    if(_the == NULL)
        _the = new FieldContainerEditorFactory;

    return _the;
}

FieldContainerEditorPtr FieldContainerEditorFactory::createDefaultEditor(FieldContainerType* FCType)
{
    if(FCType != NULL &&
       _DefaultEditorMap.find(FCType->getId()) != _DefaultEditorMap.end())
    {
        return createEditor(_DefaultEditorMap[FCType->getId()]);
    }
    else
    {
        return FieldContainerEditorPtr();
    }
}

FieldContainerEditorPtr FieldContainerEditorFactory::createEditor(const TypeBase* TheType)
{
    if(TheType != NULL &&
       dynamic_cast<const FieldContainerEditorType const*>(TheType) != NULL)
    {
        return dynamic_cast<const FieldContainerEditorType&>(*TheType).create();
    }
    else
    {
        return FieldContainerEditorPtr();
    }
}

FieldContainerEditorPtr FieldContainerEditorFactory::createEditor(const std::string& TypeName)
{
    return createEditor(TypeFactory::findType(TypeName.c_str()));
}

FieldContainerEditorPtr FieldContainerEditorFactory::createEditor(const UInt32 TypeID)
{
    return createEditor(findType(TypeID));
}
    
const FieldContainerEditorType* FieldContainerEditorFactory::findEditor(const std::string& TypeName)
{
    return dynamic_cast<const FieldContainerEditorType const*>(TypeFactory::findType(TypeName.c_str()));
}

const FieldContainerEditorType* FieldContainerEditorFactory::findEditor(const UInt32 TypeID)
{
    return dynamic_cast<const FieldContainerEditorType const*>(findType(TypeID));
}

void FieldContainerEditorFactory::setDefaultEditor(FieldContainerType* FCType, FieldContainerEditorType* EditorType)
{
    if(FCType != NULL && EditorType != NULL)
    {
        _DefaultEditorMap[FCType->getId()] = EditorType->getId();
    }
}

void FieldContainerEditorFactory::init(void)
{
    if(!_IsInitialized)
    {
        for(TypeStoreConstIt Itor(_vTypeStore.begin()) ; Itor != _vTypeStore.end(); ++Itor)
        {
            if( dynamic_cast<FieldContainerEditorType*>(*Itor) != NULL)
            {
                dynamic_cast<FieldContainerEditorType*>(*Itor)->init();
            }
        }
        _IsInitialized = true;
    }
}

UInt32 FieldContainerEditorFactory::registerType(TypeBase *pType)
{
    UInt32 Result( TypeFactory::registerType(pType) );

    if(Result > 0 && _IsInitialized)
    {
        dynamic_cast<FieldContainerEditorType*>(pType)->init();
    }

    return Result;
}

void FieldContainerEditorFactory::setDefaultGenericEditor(FieldContainerEditorType* EditorType)
{
    if(EditorType != NULL)
    {
        _DefaultGenericEditor = EditorType->getId();
    }
}

FieldContainerEditorType* FieldContainerEditorFactory::getDefaultGenericEditor(void) const
{
    if(_DefaultGenericEditor != 0 &&
        const_cast<FieldContainerEditorFactory*>(this)->findType(_DefaultGenericEditor) != NULL)
    {
        return dynamic_cast<FieldContainerEditorType*>( const_cast<FieldContainerEditorFactory*>(this)->findType(_DefaultGenericEditor) );
    }
    else
    {
        return NULL;
    }
}

TypeBase* FieldContainerEditorFactory::findType(UInt32 uiTypeId)
{
    for(TypeStoreConstIt Itor(_vTypeStore.begin()) ; Itor != _vTypeStore.end(); ++Itor)
    {
        if( (*Itor) != NULL && (*Itor)->getId() == uiTypeId)
        {
            return (*Itor);
        }
    }
    return NULL;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerEditorFactory::FieldContainerEditorFactory(void) : Inherited(), _IsInitialized(false)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerEditorFactory::~FieldContainerEditorFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

KE_END_NAMESPACE
