#ifndef HIKARI_EXCEPTIONHANDLER_H
#define HIKARI_EXCEPTIONHANDLER_H

#include <exception>

namespace Hikari
{
	class ExceptionHandler
	{
	public:
		static void initialiseHandlers();

	private:
		static void signalHandler(int sig);
		static void terminateHandler();
	};
}

#endif
