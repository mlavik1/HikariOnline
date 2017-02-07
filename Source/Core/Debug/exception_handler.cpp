#include "exception_handler.h"
#include <signal.h>
#include "debug.h"

namespace Hikari
{
	void ExceptionHandler::initialiseHandlers()
	{
		std::set_terminate(terminateHandler);
		signal(SIGSEGV, signalHandler);
	}


	void ExceptionHandler::signalHandler(int sig)
	{
		LOG_ERROR() << "Received SIGSEGV signal.";
	}

	void ExceptionHandler::terminateHandler()
	{
		std::exception_ptr exptr = std::current_exception();
		try {
			std::rethrow_exception(exptr);
		}
		catch (std::exception &ex) {
			LOG_EXCEPTION() << "Unhandled exception: " << ex.what();
		}
	}
}
