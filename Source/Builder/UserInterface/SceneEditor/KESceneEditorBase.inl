/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                                                                           *
 *   contact: djkabala@gmail.com                                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
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
 **     class SceneEditor!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SceneEditorBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SceneEditorBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
SceneEditorPtr SceneEditorBase::create(void) 
{
    SceneEditorPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = SceneEditorPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
SceneEditorPtr SceneEditorBase::createEmpty(void) 
{ 
    SceneEditorPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the SceneEditor::_mfEditors field.
inline
const MFSceneComponentEditorPtr *SceneEditorBase::getMFEditors(void) const
{
    return &_mfEditors;
}

//! Get the SceneEditor::_mfEditors field.
inline
MFSceneComponentEditorPtr *SceneEditorBase::editMFEditors(void)
{
    return &_mfEditors;
}

#ifndef OSG_2_PREP
//! Get the SceneEditor::_mfEditors field.
inline
MFSceneComponentEditorPtr *SceneEditorBase::getMFEditors(void)
{
    return &_mfEditors;
}
#endif

//! Get the SceneEditor::_sfEditingScene field.
inline
const SFScenePtr *SceneEditorBase::getSFEditingScene(void) const
{
    return &_sfEditingScene;
}

//! Get the SceneEditor::_sfEditingScene field.
inline
SFScenePtr *SceneEditorBase::editSFEditingScene(void)
{
    return &_sfEditingScene;
}

#ifndef OSG_2_PREP
//! Get the SceneEditor::_sfEditingScene field.
inline
SFScenePtr *SceneEditorBase::getSFEditingScene(void)
{
    return &_sfEditingScene;
}
#endif


//! Get the value of the SceneEditor::_sfEditingScene field.
inline
ScenePtr &SceneEditorBase::editEditingScene(void)
{
    return _sfEditingScene.getValue();
}

//! Get the value of the SceneEditor::_sfEditingScene field.
inline
const ScenePtr &SceneEditorBase::getEditingScene(void) const
{
    return _sfEditingScene.getValue();
}

#ifndef OSG_2_PREP
//! Get the value of the SceneEditor::_sfEditingScene field.
inline
ScenePtr &SceneEditorBase::getEditingScene(void)
{
    return _sfEditingScene.getValue();
}
#endif

//! Set the value of the SceneEditor::_sfEditingScene field.
inline
void SceneEditorBase::setEditingScene(const ScenePtr &value)
{
    _sfEditingScene.setValue(value);
}


//! Get the value of the \a index element the SceneEditor::_mfEditors field.
inline
SceneComponentEditorPtr &SceneEditorBase::editEditors(const UInt32 index)
{
    return _mfEditors[index];
}

//! Get the value of the \a index element the SceneEditor::_mfEditors field.
inline
const SceneComponentEditorPtr &SceneEditorBase::getEditors(const UInt32 index) const
{
    return _mfEditors[index];
}

#ifndef OSG_2_PREP
//! Get the value of the \a index element the SceneEditor::_mfEditors field.
inline
SceneComponentEditorPtr &SceneEditorBase::getEditors(const UInt32 index)
{
    return _mfEditors[index];
}

//! Get the SceneEditor::_mfEditors field.
inline
MFSceneComponentEditorPtr &SceneEditorBase::getEditors(void)
{
    return _mfEditors;
}

//! Get the SceneEditor::_mfEditors field.
inline
const MFSceneComponentEditorPtr &SceneEditorBase::getEditors(void) const
{
    return _mfEditors;
}

#endif

OSG_END_NAMESPACE

