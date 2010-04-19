#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
PasteCommand::PasteCommand(ApplicationPlayerPtr ApplicationPlayer,
                           HierarchyPanelPtr HierarchyPanel,
                           NodePtr ParentNode,
                           bool DeepClone) : Inherited(),
    _ApplicationPlayer(ApplicationPlayer),
    _HierarchyPanel(HierarchyPanel),
    _PastedNode(NullFC),
    _ParentNode(ParentNode),
    _DeepClone(DeepClone)
{
}

inline
PasteCommand::PasteCommand(const PasteCommand& source) : Inherited(source),
    _ApplicationPlayer(source._ApplicationPlayer),
    _HierarchyPanel(source._HierarchyPanel),
    _PastedNode(NullFC),
    _ParentNode(source._ParentNode),
    _DeepClone(source._DeepClone)

{
}

inline 
const CommandType &PasteCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
