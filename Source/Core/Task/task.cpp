#include "task.h"

namespace Hikari
{
	Task::Task()
	{

	}

	Task::Task(std::function<bool(void)> arg_func)
	{
		mFunction = arg_func;
	}


	bool Task::Execute()
	{
		bool taskCompleted = true;

		if (mFunction != nullptr)
		{
			taskCompleted = mFunction();
		}

		return taskCompleted;
	}

	void Task::SetCompletionCallback(std::function<void(void)> arg_callback)
	{
		mCompletionCallback = arg_callback;
	}

	void Task::OnTaskCompleted()
	{
		if (mCompletionCallback != nullptr)
		{
			mCompletionCallback();
		}
	}

}
