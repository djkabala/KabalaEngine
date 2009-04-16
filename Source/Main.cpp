

#include "KEConfig.h"
#include <OpenSG/OSGBaseFunctions.h>
#include <Application/KEMainApplication.h>

int main(int argc, char **argv)
{
    // OSG init
	osg::osgInit(argc,argv);

	//Start the Main Application
	ke::MainApplicationPtr TheApplication = ke::MainApplication::create();

	Int32 AppReturnValue = TheApplication->run(argc, argv);

	//OSG exit
    osg::osgExit();

    return AppReturnValue;
}
