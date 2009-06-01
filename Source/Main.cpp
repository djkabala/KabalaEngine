

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include "Application/KEMainApplication.h"

int main(int argc, char **argv)
{
    // OSG init
	osg::osgInit(argc,argv);

	//Start the Main Application
    osg::Int32 AppReturnValue = osg::MainApplication::the()->run(argc, argv);

	//OSG exit
    osg::osgExit();

    return AppReturnValue;
}
