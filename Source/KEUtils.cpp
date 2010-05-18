#include "KEUtils.h"
#include <boost/lexical_cast.hpp>

OSG_USING_NAMESPACE

bool attachName (AttachmentContainerRefPtr AttContainer)
{
    // Get attachment pointer
    AttachmentRefPtr att = 
        AttContainer->findAttachment(Name::getClassType().getGroupId());

    if(att == NULL ||
       dynamic_pointer_cast<Name>(att) == NULL)
    {
        std::string DefaultName(AttContainer->getType().getCName()
                              + std::string(" ")
                              + boost::lexical_cast<std::string>(AttContainer->getId()));

        setName(AttContainer,DefaultName);

        return true;
    }
    else
    {
        return false;
    }
}

void recurseSetTravMask(NodeRefPtr RootNode, 
                        UInt32 TravMask)
{
    if(RootNode->getTravMask() != TravMask)
    {
        RootNode->setTravMask(TravMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMask(RootNode->getChild(i),TravMask);
    }
}

void recurseSetTravMasRecord(NodeRefPtr RootNode, 
                             UInt32 TravMask,
                             std::vector<std::pair<NodeRefPtr, UInt32> >& NodesChanged)
{
    if(RootNode->getTravMask() != TravMask)
    {
        NodesChanged.push_back(std::pair<NodeRefPtr, UInt32>(RootNode, RootNode->getTravMask()));
        RootNode->setTravMask(TravMask);
    }

    for(UInt32 i(0) ; i<RootNode->getNChildren() ; ++i)
    {
        recurseSetTravMasRecord(RootNode->getChild(i),TravMask, NodesChanged);
    }
}

