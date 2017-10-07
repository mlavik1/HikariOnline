#ifndef HIKARI_TASK_H
#define HIKARI_TASK_H

#include <functional>

namespace Hikari
{
	class Task
	{
	private:
		std::function<bool(void)> mFunction;
		std::function<void(void)> mCompletionCallback;

	public:
		Task();
		Task(std::function<bool(void)> arg_func);

		void SetCompletionCallback(std::function<void(void)> arg_callback);
		virtual void OnTaskCompleted();

		virtual bool Execute();
	};
}

#endif
