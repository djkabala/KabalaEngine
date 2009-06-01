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
