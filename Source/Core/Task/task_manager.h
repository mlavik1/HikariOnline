#ifndef HIKARI_TASKMANAGER_H
#define HIKARI_TASKMANAGER_H

#include "task.h"
#include <queue>

namespace Hikari
{
	class TaskManager
	{
	private:
		std::queue<Task*> mQueuedTasks;
		std::queue<Task*> mTasksInProcess;
		std::queue<Task*> mQueuedAsyncTasks;

	public:
		void QueueTask(Task* arg_task);

		void ProcessTasks();
	};
}

#endif
