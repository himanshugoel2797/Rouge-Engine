#include "System.h"

INITIALIZE_EASYLOGGINGPP

void System::Initialize(int argc, char **argv)
{
	curThreadID = threadIDs++;	//Set the current thread's ID to 0

#pragma region Initialize Logging
	START_EASYLOGGINGPP(argc, argv);
	el::Configurations defaultConf;
	defaultConf.setToDefault();

#if !defined(ENGINE_DEBUG)	//Don't output stuff to a console when not debugging
	defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
#endif
	el::Loggers::setDefaultConfigurations(defaultConf, true);
#pragma endregion

	LOG__INFO("Initializing Engine");

	LOG__VERBOSE(2, "Initializing MemoryManager");
	MemoryManager::Initialize();	//Initialize the memory management system
	LOG__VERBOSE(2, "Done");

	LOG__VERBOSE(2, "Initializing MessageBus");
	MessageBus::Initialize();		//Initialize the message bus
	LOG__VERBOSE(2, "Done");

	LOG__VERBOSE(2, "Initializing TaskManager");
	TaskManager::Initialize();		//Initialize the task manager
	LOG__VERBOSE(2, "Done");

	LOG__INFO("Engine Initialized");
}
