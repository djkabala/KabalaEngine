#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
NewCommand::NewCommand(HierarchyPanelPtr HierarchyPanel,FieldContainerType* FCType) : Inherited(),
_HierarchyPanel(HierarchyPanel),
_newNode(NullFC),
_FCType(FCType)
//_name("")
{
}

inline
NewCommand::NewCommand(const NewCommand& source) : Inherited(source)
{
	_HierarchyPanel = source._HierarchyPanel;
	_newNode= source._newNode;
	_FCType= source._FCType;
	_name= source._name;
}

inline 
const CommandType &NewCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
