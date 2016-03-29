#ifdef LOGGING_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API __declspec(dllimport)
#endif

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <time.h>

using namespace std;

namespace logging_framework
{

	struct datainf
	{
		string LogName;
		int level;
	};

	class CLogger
	{

		datainf dataInf;
		ofstream outstream;

	public:
		LOG_API CLogger();
		LOG_API ~CLogger();
		LOG_API void ReadLevel();
		LOG_API void Log(int level, const char* message);
		friend ifstream &operator >> (ifstream &in, datainf &obj);
	};
}

#define NEW_LOG(level, message) CLogger::Log(level, message);

