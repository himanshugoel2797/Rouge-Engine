#include "CommonHelpers.h"
#include "MemoryManager\MemoryManager.h"

INITIALIZE_EASYLOGGINGPP

void main(int argc, char **argv)
{
	curThreadID = threadIDs++;

#pragma region Initialize Logging
	START_EASYLOGGINGPP(argc, argv);
	el::Configurations defaultConf;
	defaultConf.setToDefault();

#if !defined(ENGINE_DEBUG)	//Don't output stuff to a console when not debugging
	defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
#endif
	el::Loggers::setDefaultConfigurations(defaultConf, true);
#pragma endregion

	MemoryManager::Init();
	//Setup a large message bus to communicate between all the engine's systems
	LOG__INFO("Engine Exit");
	getchar();
}