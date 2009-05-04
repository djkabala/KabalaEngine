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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class BuilderInterface!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include "KEConfig.h"

KE_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &BuilderInterfaceBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 BuilderInterfaceBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
BuilderInterfacePtr BuilderInterfaceBase::create(void) 
{
    BuilderInterfacePtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = BuilderInterfacePtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
BuilderInterfacePtr BuilderInterfaceBase::createEmpty(void) 
{ 
    BuilderInterfacePtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the BuilderInterface::_sfMenuBar field.
inline
SFMenuBarPtr *BuilderInterfaceBase::getSFMenuBar(void)
{
    return &_sfMenuBar;
}

//! Get the BuilderInterface::_sfToolbar field.
inline
SFToolbarPtr *BuilderInterfaceBase::getSFToolbar(void)
{
    return &_sfToolbar;
}

//! Get the BuilderInterface::_sfStatusbar field.
inline
SFStatusbarPtr *BuilderInterfaceBase::getSFStatusbar(void)
{
    return &_sfStatusbar;
}

//! Get the BuilderInterface::_sfEditor field.
inline
SFEditorInterfacePtr *BuilderInterfaceBase::getSFEditor(void)
{
    return &_sfEditor;
}

//! Get the BuilderInterface::_sfDrawingSurface field.
inline
SFUIDrawingSurfacePtr *BuilderInterfaceBase::getSFDrawingSurface(void)
{
    return &_sfDrawingSurface;
}

//! Get the BuilderInterface::_sfMainInternalWindow field.
inline
SFInternalWindowPtr *BuilderInterfaceBase::getSFMainInternalWindow(void)
{
    return &_sfMainInternalWindow;
}


//! Get the value of the BuilderInterface::_sfMenuBar field.
inline
MenuBarPtr &BuilderInterfaceBase::getMenuBar(void)
{
    return _sfMenuBar.getValue();
}

//! Get the value of the BuilderInterface::_sfMenuBar field.
inline
const MenuBarPtr &BuilderInterfaceBase::getMenuBar(void) const
{
    return _sfMenuBar.getValue();
}

//! Set the value of the BuilderInterface::_sfMenuBar field.
inline
void BuilderInterfaceBase::setMenuBar(const MenuBarPtr &value)
{
    _sfMenuBar.setValue(value);
}

//! Get the value of the BuilderInterface::_sfToolbar field.
inline
ToolbarPtr &BuilderInterfaceBase::getToolbar(void)
{
    return _sfToolbar.getValue();
}

//! Get the value of the BuilderInterface::_sfToolbar field.
inline
const ToolbarPtr &BuilderInterfaceBase::getToolbar(void) const
{
    return _sfToolbar.getValue();
}

//! Set the value of the BuilderInterface::_sfToolbar field.
inline
void BuilderInterfaceBase::setToolbar(const ToolbarPtr &value)
{
    _sfToolbar.setValue(value);
}

//! Get the value of the BuilderInterface::_sfStatusbar field.
inline
StatusbarPtr &BuilderInterfaceBase::getStatusbar(void)
{
    return _sfStatusbar.getValue();
}

//! Get the value of the BuilderInterface::_sfStatusbar field.
inline
const StatusbarPtr &BuilderInterfaceBase::getStatusbar(void) const
{
    return _sfStatusbar.getValue();
}

//! Set the value of the BuilderInterface::_sfStatusbar field.
inline
void BuilderInterfaceBase::setStatusbar(const StatusbarPtr &value)
{
    _sfStatusbar.setValue(value);
}

//! Get the value of the BuilderInterface::_sfEditor field.
inline
EditorInterfacePtr &BuilderInterfaceBase::getEditor(void)
{
    return _sfEditor.getValue();
}

//! Get the value of the BuilderInterface::_sfEditor field.
inline
const EditorInterfacePtr &BuilderInterfaceBase::getEditor(void) const
{
    return _sfEditor.getValue();
}

//! Set the value of the BuilderInterface::_sfEditor field.
inline
void BuilderInterfaceBase::setEditor(const EditorInterfacePtr &value)
{
    _sfEditor.setValue(value);
}

//! Get the value of the BuilderInterface::_sfDrawingSurface field.
inline
UIDrawingSurfacePtr &BuilderInterfaceBase::getDrawingSurface(void)
{
    return _sfDrawingSurface.getValue();
}

//! Get the value of the BuilderInterface::_sfDrawingSurface field.
inline
const UIDrawingSurfacePtr &BuilderInterfaceBase::getDrawingSurface(void) const
{
    return _sfDrawingSurface.getValue();
}

//! Set the value of the BuilderInterface::_sfDrawingSurface field.
inline
void BuilderInterfaceBase::setDrawingSurface(const UIDrawingSurfacePtr &value)
{
    _sfDrawingSurface.setValue(value);
}

//! Get the value of the BuilderInterface::_sfMainInternalWindow field.
inline
InternalWindowPtr &BuilderInterfaceBase::getMainInternalWindow(void)
{
    return _sfMainInternalWindow.getValue();
}

//! Get the value of the BuilderInterface::_sfMainInternalWindow field.
inline
const InternalWindowPtr &BuilderInterfaceBase::getMainInternalWindow(void) const
{
    return _sfMainInternalWindow.getValue();
}

//! Set the value of the BuilderInterface::_sfMainInternalWindow field.
inline
void BuilderInterfaceBase::setMainInternalWindow(const InternalWindowPtr &value)
{
    _sfMainInternalWindow.setValue(value);
}


KE_END_NAMESPACE
