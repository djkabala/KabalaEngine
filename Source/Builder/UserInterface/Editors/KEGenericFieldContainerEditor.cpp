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

#include "KEGenericFieldContainerEditor.h"
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include "Builder/UserInterface/Editors/KEFieldContainerEditorFactory.h"

OSG_BEGIN_NAMESPACE

FieldContainerEditorType GenericFieldContainerEditor::_Type("GenericFieldContainerEditor",
                                                            "FieldContainerEditor",
                                                            GenericFieldContainerEditor::create,
                                                            GenericFieldContainerEditor::initMethod);

    
void GenericFieldContainerEditor::initMethod(void)
{
    FieldContainerEditorFactory::the()->setDefaultGenericEditor(&_Type);
}

FieldContainerEditorPtr GenericFieldContainerEditor::create(void)
{
    return FieldContainerEditorPtr(new GenericFieldContainerEditor());
}

const FieldContainerEditorType& GenericFieldContainerEditor::getType(void) const
{
    return _Type;
}

ComponentPtr GenericFieldContainerEditor::createInterface(void)
{
	if(_Target == NullFC)
	{
		beginEditCP(_MainPanel, Panel::ChildrenFieldMask);
			_MainPanel->getChildren().clear();
		endEditCP(_MainPanel, Panel::ChildrenFieldMask);
		return _MainPanel;
	}

    if(_MainPanel == NullFC)
    {
        _MainPanel = Panel::createEmpty();
    }
	beginEditCP(_MainPanel, Panel::ChildrenFieldMask);
		_MainPanel->getChildren().clear();

	::osg::UInt32 NumRows(0);

	//Add Editors for all of the Fields
	FieldContainerType& TheFCType(_Target->getType());
	::osg::UInt32 NumFields(TheFCType.getNumFieldDescs());
	const FieldDescription* Desc;
	Field* TheField(NULL);
	for(::osg::UInt32 i(1) ; i<NumFields+1 ; ++i)
	{
		Desc = TheFCType.getFieldDescription(i);
		if(Desc->isInternal())
		{
			continue;
		}
		
		TheField = _Target->getField(i);

		LabelPtr FieldLabel = Label::create();
		beginEditCP(FieldLabel, Label::TextFieldMask);
			FieldLabel->setText(Desc->getCName());
		endEditCP(FieldLabel, Label::TextFieldMask);
		_MainPanel->getChildren().push_back(FieldLabel);

		//Create Editor for field
		ComponentPtr Editor = createEditor(TheField);
		if(Editor != NullFC)
		{
			_MainPanel->getChildren().push_back(Editor);
		}
		++NumRows;
	}

	//Set up the Layout
	if(_MainPanel->getLayout() == NullFC)
	{
		GridLayoutPtr TheLayout = GridLayout::create();
		beginEditCP(TheLayout, GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask | GridLayout::RowsFieldMask);
			TheLayout->setColumns(2);
			TheLayout->setHorizontalGap(4);
			TheLayout->setVerticalGap(4);
		    TheLayout->setRows(NumRows);
		endEditCP(TheLayout, GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask | GridLayout::RowsFieldMask);

		beginEditCP(_MainPanel, Panel::LayoutFieldMask);
			_MainPanel->setLayout(TheLayout);
		endEditCP(_MainPanel, Panel::LayoutFieldMask);
	}
    else
    {
	    beginEditCP(_MainPanel->getLayout(), GridLayout::RowsFieldMask);
		    GridLayout::Ptr::dcast(_MainPanel->getLayout())->setRows(NumRows);
	    endEditCP(_MainPanel->getLayout(), GridLayout::RowsFieldMask);
    }

	endEditCP(_MainPanel, Panel::ChildrenFieldMask);

	beginEditCP(_MainPanel, Panel::PreferredSizeFieldMask);
		_MainPanel->setPreferredSize(Vec2f(500.0f,200.0f));
    endEditCP(_MainPanel, Panel::PreferredSizeFieldMask);

    return _MainPanel;
}

void GenericFieldContainerEditor::attachTarget(void)
{
    Inherited::attachTarget();
}

void GenericFieldContainerEditor::detachTarget(void)
{
    Inherited::detachTarget();
}

ComponentPtr GenericFieldContainerEditor::createEditor(Field*  TheField)
{
	if(TheField == NULL)
	{
		return NullFC;
	}

	ComponentPtr Editor(NullFC);
	//Single Fields
	if(TheField->getCardinality() == FieldType::SINGLE_FIELD)
	{
		if(TheField->getContentType() == FieldDataTraits< Int8 >::getType() ||
           TheField->getContentType() == FieldDataTraits< Int16 >::getType() ||
           TheField->getContentType() == FieldDataTraits< Int32 >::getType() ||
           TheField->getContentType() == FieldDataTraits< Int64 >::getType() ||
           TheField->getContentType() == FieldDataTraits< UInt8 >::getType() ||
           TheField->getContentType() == FieldDataTraits< UInt16 >::getType() ||
           TheField->getContentType() == FieldDataTraits< UInt32 >::getType() ||
           TheField->getContentType() == FieldDataTraits< UInt64 >::getType() ||
           TheField->getContentType() == FieldDataTraits< Real32 >::getType() ||
           TheField->getContentType() == FieldDataTraits< Real64 >::getType())
		{
			SpinnerModelPtr TheModel = createDefaultNumberSpinnerModel(TheField);
			
			SpinnerPtr EditorSpinner = Spinner::create();
			EditorSpinner->setModel(TheModel);

			Editor = EditorSpinner;
		}
		else if(TheField->getContentType() == FieldDataTraits< Color3f >::getType())
		{
			LabelPtr ColorLabel = Label::create();
			Color3f Value(dynamic_cast<SFColor3f*>(TheField)->getValue());
			
			
			ColorLayerPtr LabelBackgrounds = ColorLayer::create();
			beginEditCP(LabelBackgrounds, ColorLayer::ColorFieldMask);
				LabelBackgrounds->setColor(Color4f(Value.red(), Value.green(), Value.blue(), 1.0));
			endEditCP(LabelBackgrounds, ColorLayer::ColorFieldMask);

			beginEditCP(ColorLabel, Label::BackgroundsFieldMask);
			ColorLabel->setBackgrounds(LabelBackgrounds);
			endEditCP(ColorLabel, Label::BackgroundsFieldMask);
			Editor = ColorLabel;
		}
		else if(TheField->getType() == SFColor4f::getClassType())
		{
			LabelPtr ColorLabel = Label::create();
			Color4f Value(dynamic_cast<SFColor4f*>(TheField)->getValue());
			
			
			ColorLayerPtr LabelBackgrounds = ColorLayer::create();
			beginEditCP(LabelBackgrounds, ColorLayer::ColorFieldMask);
				LabelBackgrounds->setColor(Value);
			endEditCP(LabelBackgrounds, ColorLayer::ColorFieldMask);
			

			beginEditCP(ColorLabel, Label::BackgroundsFieldMask);
			ColorLabel->setBackgrounds(LabelBackgrounds);
			endEditCP(ColorLabel, Label::BackgroundsFieldMask);
			Editor = ColorLabel;
		}
		else if(TheField->getType() == SFBool::getClassType())
		{
			CheckboxButtonPtr BoolCheckboxButton = osg::CheckboxButton::create();
			beginEditCP(BoolCheckboxButton, CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask);
				BoolCheckboxButton->setAlignment(Vec2f(0.5,0.5));
				BoolCheckboxButton->setSelected(dynamic_cast<SFBool*>(TheField)->getValue());
		    endEditCP(BoolCheckboxButton, CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask);
			Editor = BoolCheckboxButton;
		}
		else
		{
			Editor = Label::create();
		}
	}
	//Multi Fields
	else if(TheField->getCardinality() == FieldType::MULTI_FIELD)
	{
		Editor = Label::create();
	}
	return Editor;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

GenericFieldContainerEditor::~GenericFieldContainerEditor(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

OSG_END_NAMESPACE
