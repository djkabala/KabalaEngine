#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
AboutKabalaEngineCommand::AboutKabalaEngineCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
AboutKabalaEngineCommand::AboutKabalaEngineCommand(const AboutKabalaEngineCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void AboutKabalaEngineCommand::operator =(const AboutKabalaEngineCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &AboutKabalaEngineCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
