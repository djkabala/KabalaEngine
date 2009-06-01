#ifndef NODEVIEWCTL_H
#define NODEVIEWCTL_H

#include "uic_FieldContainerView.h"
#include "FieldContainer.h"

class Field;

class FieldContainerViewCtl : public FieldContainerView
{ 
    Q_OBJECT;

		FieldContainer     _fieldContainer;
		
		Field *_activePart;
		int   _activePartIndex;

		bool _lineUpdate;

		void updateList(void);
		void updateActiveListItem(void);

		void updateFieldContainerView(void);
		void updateActivePartView(void);

		void loadFieldContainer(const char *fileNam);
		
		char *_procGroup;

		void sync(void);

public:

		FieldContainerViewCtl( const char *file = 0 );
    ~FieldContainerViewCtl();

public slots:

    virtual void aboutSlot();
    virtual void activePartChanged(int);
    virtual void clonePartSlot();
    virtual void deletePartSlot();
    virtual void downPartSlot();
    virtual void exitSlot();
    virtual void libraryChanged(const QString &);
    virtual void loadFieldTypesSlot();
    virtual void loadParentSlot();
    virtual void loadSlot();
    virtual void nameChanged(const QString &);
    virtual void newPartSlot();
    virtual void newSlot();
    virtual void parentSysCompChanged(int);
    virtual void sysCompChanged(int);
    virtual void decoratableSwitch_stateChanged(int);
    virtual void localIncludesChanged(int);
    virtual void partIncludeChanged(const QString &);
    virtual void parentChanged(const QString &);
    virtual void partAccessChanged(int);
    virtual void partCardinalityChanged(int);
    virtual void partDefaultValueChanged(const QString &);
    virtual void partDescriptionChanged(const QString &);
    virtual void partNameChanged(const QString &);
    virtual void partTypeChanged(const QString &);
    virtual void partVisibilityChanged(int);
    virtual void partDefaultHeaderChanged(const QString &);
    virtual void pointerFieldTypesChanged(int);
    virtual void resetFieldTypesSlot();
    virtual void saveAsSlot();
    virtual void saveSlot();
    virtual void structureChanged(int);
    virtual void upPartSlot();
    virtual void writeFieldContainerBaseSlot();
    virtual void writeFieldContainerSlot();

};

#endif // NODEVIEWCTL_H
