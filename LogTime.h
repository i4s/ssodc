#pragma once

#include "Logger.h"

namespace logging_framework
{

	class LogTime
	{
	public:
#ifdef _WIN32
		LOG_API struct tm* getCurrentTime();
		LOG_API string timeToString(struct tm timeInfo);
#else
		struct tm* getCurrentTime();
		string timeToString(struct tm timeInfo);
#endif
	};
}
