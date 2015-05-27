#pragma once
#include <thread>
#include "../CommonHelpers.h"
#include "../MemoryManager/MemoryManager.h"
#include "Task.h"

class TaskManager
{
public:
	static const u_int32 MAX_TASK_COUNT = 1024;	//Limit the system to a maximum number of queued tasks

	static u_int32 ThreadCount;
	static std::thread *Workers;
	static Task Tasks[MAX_TASK_COUNT];

		static void Initialize();
	static void AddTask();
	static void WorkerLoop();
	static void Destroy();
};

