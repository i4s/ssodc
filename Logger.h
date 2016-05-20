#pragma once

#ifdef LOGGING_EXPORTS
#define LOG_API  __declspec(dllexport)
#else
#define LOG_API  __declspec(dllimport)
#endif

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <time.h>
#include <Windows.h>
#include "sys_Mutex.h"

using namespace std;

enum LogLevel
{
	logError,
	logWarning,
	logDebug,
	logTrace,
};

namespace logging_framework
{

	struct datainf
	{
		string LogName;
		LogLevel level;
	};

	class CLogger
	{
		 static sys::Mutex g_mutex;
		 static bool initialise;
	protected:
		 static datainf dataInf;
	public:
		LOG_API static void readConfig();
		LOG_API static void parseConfig(const char *buff);
		LOG_API static void getValue(string source, string &key, string &value);
		LOG_API static void log(LogLevel level ,const char* message);
		LOG_API static void log_crit(LogLevel level ,int line, const char* message, const char* location);
		LOG_API static void setLevel(string level);
		LOG_API static LogLevel stringTolevel(string level);
		LOG_API static string levelToString(LogLevel level);
	};


	class CFiles: public CLogger
	{
		ofstream out;
	public:
		LOG_API CFiles(string filename);
		LOG_API ~CFiles();
		LOG_API void saveToFile(LogLevel level, struct tm timeInfo, const char *message);
		LOG_API void saveToFile(LogLevel level, int line, struct tm timeInfo, const char *message, const char* location);
	};

	class CConsole : public CLogger
	{

	};
}

#define NEW_LOG_TRACE(message) CLogger::log(logTrace, message);
#define NEW_LOG_DEBUG(message) CLogger::log(logDebug, message);
#define NEW_LOG_WARNING(message) CLogger::log_crit(logWarning, __LINE__, message, __FILE__);
#define NEW_LOG_ERROR(message) CLogger::log_crit(logError, __LINE__, message, __FILE__);


