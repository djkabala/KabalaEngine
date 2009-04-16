#include "FieldContainerViewCtl.h"

#include <iostream>

#include <qcombobox.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qmultilineedit.h>
#include <qcheckbox.h>
#include <qbuttongroup.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qlistbox.h>
#include <qdir.h>

/* 
 *  Constructs a FieldContainerViewCtl which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FieldContainerViewCtl::FieldContainerViewCtl( const char *file )
	: FieldContainerView(0,0,FALSE,0),
		_activePart(0), _activePartIndex(0),
		_lineUpdate(false),
		_procGroup(0)
{
	int i;

	for (i = 0; true; i++) 
		if (FieldContainer::pointerFieldTypesStr(i))
			pointerFieldTypesCombo->insertItem(QString(FieldContainer::pointerFieldTypesStr(i)));
		else
			break;

	for (i = 0; true; i++) 
		if (FieldContainer::abstractStr(i))
			structureCombo->insertItem(QString(FieldContainer::abstractStr(i)));
		else
			break;

	
	for (i = 0; true; i++) 
		if (Field::typeStr(i))
			partTypeCombo->insertItem(QString(Field::typeStr(i)));
		else
			break;

	for (i = 0; true; i++)
		if (Field::cardinalityStr(i))
			partCardinalityCombo->insertItem(QString(Field::cardinalityStr(i)));
		else
			break;

	for (i = 0; true; i++)
		if (Field::visibilityStr(i))
			partVisibilityCombo->insertItem(QString(Field::visibilityStr(i)));
		else
			break;

	for (i = 0; true; i++)
		if (Field::accessStr(i))
			partAccessCombo->insertItem(QString(Field::accessStr(i)));
		else
			break;

	if (file && *file)
		loadFieldContainer(file);
	
	if (_fieldContainer.numOfFields() == 0)
		partFrame->setEnabled(FALSE);			 
}

/*  
 *  Destroys the object and frees any allocated resources
 */
FieldContainerViewCtl::~FieldContainerViewCtl()
{
    // no need to delete child widgets, Qt does it all for us
}

void FieldContainerViewCtl::sync(void)
{
	QString str = nodeDescriptionInput->text().simplifyWhiteSpace();

	_fieldContainer.setDescription(str.latin1());
}

void FieldContainerViewCtl::updateList(void) 
{
	char line[1024];
	std::list<Field>::iterator nPI;

	partListBox->clear();

	for ( nPI = _fieldContainer.fieldList().begin();
				nPI != _fieldContainer.fieldList().end(); ++nPI ) {
		nPI->getLine(line);
		partListBox->insertItem (QString(line));
	}
}

void FieldContainerViewCtl::updateActiveListItem(void) 
{
	char line[1024];

	_activePart->getLine(line);
	_lineUpdate = true;
	partListBox->changeItem(QString(line),_activePartIndex);
	_lineUpdate = false;
}

void FieldContainerViewCtl::updateFieldContainerView(void)
{
    // without the block signals the slots are called and it crashes!
    nodeNameInput->blockSignals(true);
    nodeNameInput->setText(QString(_fieldContainer.name()));
    nodeNameInput->blockSignals(false);

    nodeParentInput->blockSignals(true);
    nodeParentInput->setText(QString(_fieldContainer.parentFieldContainer()));
    nodeParentInput->blockSignals(false);
    
    nodeLibraryInput->blockSignals(true);
    nodeLibraryInput->setText(QString(_fieldContainer.library()));
    nodeLibraryInput->blockSignals(false);
    
    nodeDescriptionInput->blockSignals(true);
    nodeDescriptionInput->setText(QString(_fieldContainer.description()));
    nodeDescriptionInput->blockSignals(false);
    
    pointerFieldTypesCombo->blockSignals(true);
    pointerFieldTypesCombo->setCurrentItem(_fieldContainer.pointerFieldTypes());
    pointerFieldTypesCombo->blockSignals(false);
    
    structureCombo->blockSignals(true);
    structureCombo->setCurrentItem(_fieldContainer.abstract());
    structureCombo->blockSignals(false);
    
    sysComp->blockSignals(true);
    sysComp->setChecked(_fieldContainer.systemComponent());
    sysComp->blockSignals(false);
    
    parentSysComp->blockSignals(true);
    parentSysComp->setChecked(_fieldContainer.parentSystemComponent());
    parentSysComp->blockSignals(false);
    
    decoratableSwitch->blockSignals(true);
    decoratableSwitch->setChecked(_fieldContainer.decoratable());
    decoratableSwitch->blockSignals(false);
    
    localIncludes->blockSignals(true);
    localIncludes->setChecked(_fieldContainer.useLocalIncludes());
    localIncludes->blockSignals(false);
}

void FieldContainerViewCtl::updateActivePartView(void)
{
    // without the block signals the slots are called and it crashes!
    if (_activePart) {
        partNameInput->blockSignals(true);
        partNameInput->setText(QString(_activePart->name()));
        partNameInput->blockSignals(false);
        
        partTypeCombo->blockSignals(true);
        partTypeCombo->setEditText(_activePart->type());
        partTypeCombo->blockSignals(false);
        
        partVisibilityCombo->blockSignals(true);
        partVisibilityCombo->setCurrentItem(int(_activePart->visibility()));
        partVisibilityCombo->blockSignals(false);
        
        partCardinalityCombo->blockSignals(true);
        partCardinalityCombo->setCurrentItem(int(_activePart->cardinality()));
        partCardinalityCombo->blockSignals(false);
        
        partAccessCombo->blockSignals(true);
        partAccessCombo->setCurrentItem(int(_activePart->access()));
        partAccessCombo->blockSignals(false);
        
        partIncludeInput->blockSignals(true);
        partIncludeInput->setText(QString(_activePart->header()));
        partIncludeInput->blockSignals(false);
        
        partDefaultValueInput->blockSignals(true);
        partDefaultValueInput->setText(QString(_activePart->defaultValue()));
        partDefaultValueInput->blockSignals(false);
        
        partDefaultHeaderInput->blockSignals(true);
        partDefaultHeaderInput->setText(QString(_activePart->defaultHeader()));
        partDefaultHeaderInput->blockSignals(false);
        
        partDescriptionInput->blockSignals(true);
        partDescriptionInput->setText(QString(_activePart->description()));
        partDescriptionInput->blockSignals(false);
    }
    else {
        partNameInput->blockSignals(true);
        partNameInput->clear();
        partNameInput->blockSignals(false);
        
        partTypeCombo->blockSignals(true);
        partTypeCombo->setCurrentItem(0);
        partTypeCombo->blockSignals(false);
        
        partVisibilityCombo->blockSignals(true);
        partVisibilityCombo->setCurrentItem(0);
        partVisibilityCombo->blockSignals(false);
        
        partCardinalityCombo->blockSignals(true);
        partCardinalityCombo->setCurrentItem(0);
        partCardinalityCombo->blockSignals(false);
        
        partAccessCombo->blockSignals(true);
        partAccessCombo->setCurrentItem(0);
        partAccessCombo->blockSignals(false);
        
        partIncludeInput->blockSignals(true);
        partIncludeInput->clear();
        partIncludeInput->blockSignals(false);
        
        partDefaultValueInput->blockSignals(true);
        partDefaultValueInput->clear();
        partDefaultValueInput->blockSignals(false);
        
        partDescriptionInput->blockSignals(true);
        partDescriptionInput->clear();
        partDescriptionInput->blockSignals(false);
    }

}

void FieldContainerViewCtl::loadFieldContainer(const char *fileName)
{
	int i;

	if (fileName) {
		_fieldContainer.readDesc(fileName);
        setCaption( trUtf8( QString("OpenSG Field Container Editor : " ) +
                    fileName ) );
                _activePart = NULL;
                _activePartIndex = -1;
                
		updateFieldContainerView();
		if (_fieldContainer.fieldList().size()) {
			partTypeCombo->clear();
			for (i = 0; true; i++) 
				if (Field::typeStr(i))
					partTypeCombo->insertItem(QString(Field::typeStr(i)));
				else
					break;
			partFrame->setEnabled(TRUE);
			updateList();
			_activePartIndex = 0;
			_activePart = _fieldContainer.getField(_activePartIndex);
			updateActivePartView();
		}
		else {
			partFrame->setEnabled(FALSE);
			_activePartIndex = -1;
			_activePart = 0;
			updateList();
			updateActivePartView();
		}
	}
}

/* 
 * public slot
 */
void FieldContainerViewCtl::activePartChanged(int index)
{
	//	std::cerr << "activePartChanged:" << index << std::endl;

	if (!_lineUpdate) {
		_activePartIndex = index;
		_activePart = _fieldContainer.getField(_activePartIndex);
		if (_activePart) 
			updateActivePartView();
	}
}
/* 
 * public slot
 */
void FieldContainerViewCtl::clonePartSlot()
{
	int newPart;

	if (_activePart) {
		newPart = _activePartIndex = _fieldContainer.newField(*_activePart);
		_activePart = _fieldContainer.getField(_activePartIndex);

		partListBox->setSelected(_activePartIndex, FALSE);
		
		updateActivePartView();
		
		updateList();

		partListBox->setSelected(newPart, TRUE);
	}
}
/* 
 * public slot
 */
void FieldContainerViewCtl::deletePartSlot()
{
	int partNum;

	if (_activePart) {
		_fieldContainer.delField(_activePartIndex);
		partNum = _fieldContainer.numOfFields();
		if (partNum) {
			_activePartIndex = partNum - 1;
			_activePart = _fieldContainer.getField(_activePartIndex);
			//partListBox->setSelected(_activePartIndex, FALSE);
			updateActivePartView();			
			updateList();
			partListBox->setSelected(_activePartIndex, TRUE);
		}
		else {
			partFrame->setEnabled(FALSE);
			_activePartIndex = -1;
			_activePart = 0;
			updateActivePartView();			
			updateList();
		}
	}
}

/* 
 * public slot
 */
void FieldContainerViewCtl::exitSlot()
{
	::exit(0);
}

/* 
 * public slot
 */
void FieldContainerViewCtl::loadSlot()
{
	QString fN (QFileDialog::getOpenFileName ( QString::null,
																						 "FieldContainer Description File (*.fcd)",
																						 this ) );

	if (!fN.isEmpty()) {
		loadFieldContainer(fN);
	}
	
}

/* 
 * public slot
 */
void FieldContainerViewCtl::nameChanged(const QString &value)
{
	_fieldContainer.setName(value);
}

/* 
 * public slot
 */
void FieldContainerViewCtl::libraryChanged(const QString &value)
{
	_fieldContainer.setLibrary(value);
}

/* 
 * public slot
 */
void FieldContainerViewCtl::newPartSlot()
{
	Field part;

	_activePartIndex = _fieldContainer.newField(part);
	_activePart = _fieldContainer.getField(_activePartIndex);

	partListBox->setCurrentItem(_activePartIndex);

	partFrame->setEnabled(TRUE);

	partNameInput->setFocus();

	updateActivePartView();

	updateList();

	partListBox->setSelected(_activePartIndex,TRUE);

}

void FieldContainerViewCtl::upPartSlot()
{
	int newPos;

	if (_activePart && _fieldContainer.moveFieldLeft(_activePartIndex)) {
			newPos = _activePartIndex - 1;
			updateList();
			partListBox->setCurrentItem(newPos);
	}
}

void FieldContainerViewCtl::downPartSlot()
{
	int newPos;

	if (_activePart && _fieldContainer.moveFieldRight(_activePartIndex)) {
			newPos = _activePartIndex + 1;
			updateList();
			partListBox->setCurrentItem(newPos);
	}
}

/* 
 * public slot
 */
void FieldContainerViewCtl::parentChanged(const QString &value)
{
	_fieldContainer.setParentFieldContainer(value);
}

/* 
 * public slot
 */
void FieldContainerViewCtl::partDefaultValueChanged(const QString &value)
{
	if (_activePart) {
		_activePart->setDefaultValue(value);
		updateActiveListItem();
	}
}
/* 
 * public slot
 */
void FieldContainerViewCtl::partDescriptionChanged(const QString &value)
{
	if (_activePart) {
		_activePart->setDescription(value);
		updateActiveListItem();
	}
}
/* 
 * public slot
 */
void FieldContainerViewCtl::partNameChanged(const QString &value)
{
	if (_activePart) {
		_activePart->setName(value);
		updateActiveListItem();
	}
}
/* 
 * public slot
 */
void FieldContainerViewCtl::partTypeChanged(const QString &value)
{
	if (_activePart) {
		_activePart->setType(value);
		updateActiveListItem();
	}
}

/* 
 * public slot
 */
void FieldContainerViewCtl::partCardinalityChanged(int index)
{
	if (_activePart) {
		_activePart->setCardinality(index);
		updateActiveListItem();
	}	
}

/* 
 * public slot
 */
void FieldContainerViewCtl::saveSlot()
{
	sync();

	if (_fieldContainer.name())
		_fieldContainer.writeDesc();
	else
		QMessageBox::information ( this, "No Name",
															 "The current FieldContainer doesn't have a name\n"
															 "Can't write the fcd file"
															 );
}

/* 
 * public slot
 */
void FieldContainerViewCtl::partVisibilityChanged(int index)
{
	if (_activePart) {
		_activePart->setVisibility(index);
		updateActiveListItem();
	}
}

/* 
 * public slot
 */
void FieldContainerViewCtl::writeFieldContainerBaseSlot()
{
	char file[1024];

	sync();

	if (_fieldContainer.name()) {
		QString s( QFileDialog::getExistingDirectory( QDir::current().path(), NULL,
			"name", QString("Choose directory to save base files to"), true ) );

		if ( s.isEmpty() )
			return;

		sprintf( file,"%s/%s%sFields.%s", s.ascii(), 
                    _fieldContainer.filePrefix(), 
						        _fieldContainer.name(), 
                    _fieldContainer.decFileSuffix());
                    
		if (!_fieldContainer.writeCodeFields(file))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the fields file ");
            return;
    }

		sprintf( file,"%s/%s%sBase.%s", s.ascii(), 
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.decFileSuffix());
                    
		if (!_fieldContainer.writeBaseCodeDec(file))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the dec file ");
            return;
    }

		sprintf( file,"%s/%s%sBase.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.inlFileSuffix());
                    
		if (!_fieldContainer.writeBaseCodeInl(file))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the inl file ");
            return;
    }

		sprintf( file,"%s/%s%sBase.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.impFileSuffix());
                    
		if (!_fieldContainer.writeBaseCodeImp(file))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the imp file ");
            return;
    }

	  char bdec[1024],binl[1024],bimp[1024],fields[1024];

		sprintf( fields,"%s/%s%sDecoratorFields.%s", s.ascii(), 
                    _fieldContainer.filePrefix(), 
						        _fieldContainer.name(), 
                    _fieldContainer.decFileSuffix());
		sprintf( bdec,"%s/%s%sDecoratorBase.%s", s.ascii(), 
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.decFileSuffix());
		sprintf( binl,"%s/%s%sDecoratorBase.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.inlFileSuffix());
		sprintf( bimp,"%s/%s%sDecoratorBase.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.impFileSuffix());
                    
		if (!_fieldContainer.writeDecoratorBase(bdec,binl,bimp,fields))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the decorator files ");
            return;
    }
	}
	else
		QMessageBox::warning ( this, "Write error",
													 "No node name");

						
}

/* 
 * public slot
 */
void FieldContainerViewCtl::writeFieldContainerSlot()
{
	char file[6][1024];

	sync();

	if (_fieldContainer.name()) {
		QString s( QFileDialog::getExistingDirectory( QDir::current().path(), NULL,
			"name", QString("Choose directory to save files to"), true ) );

		if ( s.isEmpty() )
			return;

		sprintf( file[0],"%s/%s%s.%s", s.ascii(), 
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.decFileSuffix());

		sprintf( file[1],"%s/%s%s.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.inlFileSuffix());

		sprintf( file[2],"%s/%s%s.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.impFileSuffix());

		sprintf( file[3],"%s/%s%sDecorator.%s", s.ascii(), 
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.decFileSuffix());
		sprintf( file[4],"%s/%s%sDecorator.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.inlFileSuffix());
		sprintf( file[5],"%s/%s%sDecorator.%s", s.ascii(),  
                _fieldContainer.filePrefix(),
						    _fieldContainer.name(), 
                _fieldContainer.impFileSuffix());

				
		// Check if the files already exist and don't overwrite them
		QString ex;		 
    for(int i = 0; i < 6; i++)
    {
		    QFile f( file[i] );
		    if ( f.exists() )
		    {
			    ex += file[i];
			    ex += "\n";
		    }
    } 

		if ( ex.length() )
		{
			QString mes("Some files already exist:\n");
			mes += ex;
			mes += "Are you sure you want to overwrite them?";
			
			if ( QMessageBox::warning ( this, "Overwrite Warning", mes, 
					"Yes", "No", NULL, 0, 1) )
				return;
		}
		
                     
		if (!_fieldContainer.writeCodeDec(file[0]))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the dec file ");
            return;
    }
                    
		if (!_fieldContainer.writeCodeInl(file[1]))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the inl file ");
            return;
    }
                    
		if (!_fieldContainer.writeCodeImp(file[2]))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the imp file ");
            return;
    }
                   
		if (!_fieldContainer.writeDecoratorCode(file[3],file[4],file[5]))
    {
            QMessageBox::warning ( this, "Write error",
														 "Couldn't write the decorator files ");
            return;
    }
	}
	else
		QMessageBox::warning ( this, "Write error",
													 "No node name");

						
}

/* 
 * public slot
 */
void FieldContainerViewCtl::aboutSlot()
{
	QMessageBox::about ( this, "About",
											 "OpenSG FieldContainer Description File Editor\n\n"
											 "http://www.opensg.org"
											 );
}

/* 
 * public slot
 */
void FieldContainerViewCtl::saveAsSlot()
{
	QString fN (QFileDialog::getSaveFileName ( QString::null,
																						 "FieldContainer Description File (*.fcd)",
																						 this ) );
	if (!fN.isEmpty())
    {
        setCaption( trUtf8( QString("OpenSG Field Container Editor : " ) +
                    fN ) );
		_fieldContainer.writeDesc(fN);
    }
}

/* 
 * public slot
 */
void FieldContainerViewCtl::loadParentSlot()
{
	char fileName[256];

	if (_fieldContainer.parentFieldContainer()) {
		sprintf(fileName,"%s.fcd", _fieldContainer.parentFieldContainer());
		loadFieldContainer(fileName);
	}
	else
		QMessageBox::information ( this, "No Parent",
													 "The current FieldContainer doesn't have a parent node"
													 );
													 
}

void FieldContainerViewCtl::loadFieldTypesSlot(void)
{
	int i;
	QString fN (QFileDialog::getOpenFileName ( QString::null,
																						 "Type list file (*.ftd)", this ) );

	if (!fN.isEmpty()) {
		newSlot();
		Field::loadFieldTypeList(fN);
		partTypeCombo->clear();
		for (i = 0; true; i++) 
			if (Field::typeStr(i))
				partTypeCombo->insertItem(QString(Field::typeStr(i)));
			else
				break;
	}
}

void FieldContainerViewCtl::resetFieldTypesSlot(void)
{
	int i;

	Field::loadDefaultFieldTypeList();
	partTypeCombo->clear();
	for (i = 0; true; i++) 
		if (Field::typeStr(i))
			partTypeCombo->insertItem(QString(Field::typeStr(i)));
		else
			break;
}

void FieldContainerViewCtl::newSlot(void)
{
    QString emptyStr("");
    _fieldContainer.clear();
    
    setCaption( trUtf8( "OpenSG Field Container Editor " ) );
    
    nodeNameInput->blockSignals(true);
    nodeNameInput->setText(emptyStr);
    nodeNameInput->blockSignals(false);
    
    nodeParentInput->blockSignals(true);
    nodeParentInput->setText(emptyStr);
    nodeParentInput->blockSignals(false);
    
    nodeLibraryInput->blockSignals(true);
    nodeLibraryInput->setText(emptyStr);
    nodeLibraryInput->blockSignals(false);
    
    pointerFieldTypesCombo->blockSignals(true);
    pointerFieldTypesCombo->setCurrentItem(0);
    pointerFieldTypesCombo->blockSignals(false);
    
    nodeDescriptionInput->blockSignals(true);
    nodeDescriptionInput->setText(emptyStr);
    nodeDescriptionInput->blockSignals(false);
    
    partFrame->setEnabled(FALSE);
    _activePartIndex = -1;
    _activePart = 0;
    updateActivePartView();			
    updateList();
}

void FieldContainerViewCtl::pointerFieldTypesChanged(int index)
{
	_fieldContainer.setPointerFieldTypes(index);
}

void FieldContainerViewCtl::structureChanged(int index)
{
	std::cerr << "set abstract: " << index << std::endl;

	_fieldContainer.setAbstract(index);
}

void FieldContainerViewCtl::sysCompChanged(int index)
{
	_fieldContainer.setSystemComponent(index);
	
	if ( index )
	{
		parentSysComp->setChecked( true );
		parentSysComp->setDisabled( true );
	}
	else
	{
		parentSysComp->setDisabled( false );
	}
}

void FieldContainerViewCtl::parentSysCompChanged(int index)
{
	_fieldContainer.setParentSystemComponent(index);
}

void FieldContainerViewCtl::decoratableSwitch_stateChanged(int index)
{
	_fieldContainer.setDecoratable(index);
	
	if ( index && _fieldContainer.pointerFieldTypes() == 0)
	{
    _fieldContainer.setPointerFieldTypes(1);
    pointerFieldTypesCombo->setCurrentItem(1);
	}
}

void FieldContainerViewCtl::localIncludesChanged(int index)
{
	_fieldContainer.setUseLocalIncludes(index);
}

void FieldContainerViewCtl::partAccessChanged(int index)
{
	if (_activePart) {
		_activePart->setAccess(index);
		updateActiveListItem();
	}
}

void FieldContainerViewCtl::partIncludeChanged(const QString &str)
{
	if (_activePart) {
		_activePart->setHeader(str);
		updateActiveListItem();
	}
}

void FieldContainerViewCtl::partDefaultHeaderChanged(const QString &str)
{
	if (_activePart) {
		_activePart->setDefaultHeader(str);
		updateActiveListItem();
	}
}



