#include "LogTime.h"

namespace logging_framework
{
	struct tm* LogTime::getCurrentTime()
	{
		time_t current_time;
		struct tm *timeinfo;
		time(&current_time);
		timeinfo = localtime(&current_time);
		return timeinfo;
	}

	string LogTime::timeToString(struct tm timeinfo)
	{
		std::ostringstream oss;
		oss << timeinfo.tm_mday << "/" << timeinfo.tm_mon << "/" << timeinfo.tm_year + 1900 << " " <<
			timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec;
		return oss.str();
	}
}