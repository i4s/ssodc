#pragma once

#include "Logger.h"

namespace logging_framework
{
	class CConsole : public CLogger
	{
	public:
#ifdef _WIN32
		LOG_API void printInConsole(string information);
#else
		void printInConsole(string information);
#endif
	};
}