#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
NewCommand::NewCommand(HierarchyPanelPtr HierarchyPanel,FieldContainerType* FCType) : Inherited(),
_HierarchyPanel(HierarchyPanel),
_NewNode(NullFC),
_FCType(FCType)
{
}

inline
NewCommand::NewCommand(const NewCommand& source) : Inherited(source)
{
	_HierarchyPanel = source._HierarchyPanel;
	_NewNode= source._NewNode;
	_FCType= source._FCType;
	_Name= source._Name;
}

inline 
const CommandType &NewCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
