#include "task_manager.h"

namespace Hikari
{
	void TaskManager::QueueTask(Task* arg_task)
	{
		mQueuedTasks.push(arg_task);
	}

	void TaskManager::ProcessTasks()
	{
		// Process tasks in progress
		std::queue<Task*> newTasksInProcessQueue;
		while (!mTasksInProcess.empty())
		{
			Task* currTask = mTasksInProcess.front();
			mTasksInProcess.pop();
			bool taskCompleted = currTask->Execute();
			if (taskCompleted)
			{
				currTask->OnTaskCompleted();
				delete(currTask);
			}
			else
			{
				newTasksInProcessQueue.push(currTask);
			}
		}
		mTasksInProcess = newTasksInProcessQueue;

		// Process new tasks
		const size_t queueSize = mQueuedTasks.size();
		for(int i = 0; i < queueSize && !mQueuedTasks.empty(); i++)
		{
			Task* currTask = mQueuedTasks.front();
			mQueuedTasks.pop();
			bool taskCompleted = currTask->Execute();
			if (taskCompleted)
			{
				currTask->OnTaskCompleted();
				delete(currTask);
			}
			else
			{
				mTasksInProcess.push(currTask);
			}
		}
	}
}
