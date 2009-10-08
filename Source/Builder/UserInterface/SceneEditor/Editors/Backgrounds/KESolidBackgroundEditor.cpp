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

#include "KESolidBackgroundEditor.h"
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/OSGSolidBackground.h>

#include "Builder/UserInterface/Editors/KEFieldContainerEditorFactory.h"

OSG_BEGIN_NAMESPACE

FieldContainerEditorType SolidBackgroundEditor::_Type("SolidBackgroundEditor",
                                                            "FieldContainerEditor",
                                                            SolidBackgroundEditor::create,
                                                            SolidBackgroundEditor::initMethod);

    
void SolidBackgroundEditor::initMethod(void)
{
    FieldContainerEditorFactory::the()->setDefaultEditor(&SolidBackground::getClassType(), &_Type);
}

FieldContainerEditorPtr SolidBackgroundEditor::create(void)
{
    return FieldContainerEditorPtr(new SolidBackgroundEditor());
}

const FieldContainerEditorType& SolidBackgroundEditor::getType(void) const
{
    return _Type;
}

ComponentPtr SolidBackgroundEditor::createInterface(void)
{
    if(_Chooser == NullFC)
    {
        //Create Color Chooser Panel
	    _Chooser = ColorChooser::create();
        _Chooser->setSelectionModel(&_ColorModel);
		_ColorModel.addChangeListener(&_ColorChangeListener);
    }
    return _Chooser;
}

void SolidBackgroundEditor::attachTarget(void)
{
    Inherited::attachTarget();

    _ColorModel.attachColorField(_Target, SolidBackground::getClassType().findFieldDescription("color")->getFieldId());
}

void SolidBackgroundEditor::detachTarget(void)
{
    _ColorModel.attachColorField(NullFC, 0);

    Inherited::detachTarget();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SolidBackgroundEditor::SolidBackgroundEditor(void) : Inherited(),
													_ColorChangeListener(SolidBackgroundEditorPtr(this))
{
}
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SolidBackgroundEditor::~SolidBackgroundEditor(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */


//Other
void SolidBackgroundEditor::ColorChangeListener::stateChanged(const ChangeEventPtr e)
{
}
OSG_END_NAMESPACE
