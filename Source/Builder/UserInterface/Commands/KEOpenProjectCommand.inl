#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
OpenProjectCommand::OpenProjectCommand(ApplicationBuilderPtr TheApplicationBuilder) : Inherited(),
_TheApplicationBuilder(TheApplicationBuilder)
{
}

inline
OpenProjectCommand::OpenProjectCommand(const OpenProjectCommand& source) : Inherited(source),
_TheApplicationBuilder(source._TheApplicationBuilder)
{
}

inline 
void OpenProjectCommand::operator =(const OpenProjectCommand& source)
{
	Inherited::operator=(source);
	_TheApplicationBuilder = source._TheApplicationBuilder;
}

inline 
const CommandType &OpenProjectCommand::getClassType(void)
{
	return _Type;
}

OSG_END_NAMESPACE
