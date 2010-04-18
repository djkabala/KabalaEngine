#include "KEUtils.h"



OSG_USING_NAMESPACE

bool attachName (AttachmentContainerPtr AttContainer)
{
    // Get attachment pointer
    AttachmentPtr att = 
        AttContainer->findAttachment(Name::getClassType().getGroupId());

    if(att == NullFC ||
		NamePtr::dcast(att) == NullFC)
	{
		std::string DefaultName(AttContainer->getType().getCName());

		DefaultName.append(" ");
		DefaultName.append(TypeTraits< ::osg::UInt32>::putToString(AttContainer.getFieldContainerId()));

		setName(AttContainer,DefaultName);

        return true;
	}
	else
	{
		return false;
	}
}

void recurseSetTravMask(NodePtr RootNode, 
                        UInt32 TravMask)
{
    if(RootNode->getTravMask() != TravMask)
    {
        beginEditCP(RootNode, Node::TravMaskFieldMask);
            RootNode->setTravMask(TravMask);
        endEditCP(RootNode, Node::TravMaskFieldMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMask(RootNode->getChild(i),TravMask);
    }
}

void recurseSetTravMasRecord(NodePtr RootNode, 
                             UInt32 TravMask,
                             std::vector<std::pair<NodePtr, UInt32> >& NodesChanged)
{
    if(RootNode->getTravMask() != TravMask)
    {
        NodesChanged.push_back(std::pair<NodePtr, UInt32>(RootNode, RootNode->getTravMask()));
        beginEditCP(RootNode, Node::TravMaskFieldMask);
            RootNode->setTravMask(TravMask);
        endEditCP(RootNode, Node::TravMaskFieldMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMasRecord(RootNode->getChild(i),TravMask, NodesChanged);
    }
}

