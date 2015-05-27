#include "TaskManager.h"

u_int32 TaskManager::ThreadCount = 0;
std::thread *TaskManager::Workers;
Task TaskManager::Tasks[TaskManager::MAX_TASK_COUNT];

void TaskManager::Initialize()
{
	ThreadCount = std::thread::hardware_concurrency();	//Get the number of threads available
	LOG__INFO("ThreadCount = %v", ThreadCount);
	if (ThreadCount == 0) {		//If ThreadCount is still zero, we will need to default to just one thread and record a log message
		LOG__WARN("Failed to detect threads, defaulting to 1 core");
		++ThreadCount;
	}
	else if (ThreadCount != 1) {
		ThreadCount--;	//Reduce thread count by one because one core must be used for the main thread
	}

	//Now initialize and start the worker threads
	Workers = (std::thread*)MemoryManager::Alloc(sizeof(std::thread)*ThreadCount);	//Allocate a dynamic array for the threads
	for (u_int32 i = 0; i < ThreadCount; i++) {
		new (Workers + sizeof(std::thread) * i) std::thread(TaskManager::WorkerLoop);
	}

	//Workers grab tasks from the task pool, each system on recieving a message can decide if it needs updating, in which case it can ask the gameloop to call it in the next loop, allowing it to submit tasks
}

void TaskManager::WorkerLoop()
{
}
