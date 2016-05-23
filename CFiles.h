#pragma once

#include "Logger.h"

namespace logging_framework
{
	class CFiles : public CLogger
	{
		ofstream out;
	public:
#ifdef _WIN32
		LOG_API CFiles(string filename);
		LOG_API ~CFiles();
		LOG_API void saveToFile(string information);
#else
		CFiles(string filename);
	    ~CFiles();
		void saveToFile(string information);
#endif
	};
}