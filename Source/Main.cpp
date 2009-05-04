

#include "KEConfig.h"
#include <OpenSG/OSGBaseFunctions.h>
#include <Application/KEMainApplication.h>

int main(int argc, char **argv)
{
    // OSG init
	osg::osgInit(argc,argv);

	//Start the Main Application
    Int32 AppReturnValue = ke::MainApplication::the()->run(argc, argv);

	//OSG exit
    osg::osgExit();

    return AppReturnValue;
}
