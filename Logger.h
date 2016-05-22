#pragma once

#ifdef LOGGING_EXPORTS
#define LOG_API  __declspec(dllimport)
#else
#define LOG_API  __declspec(dllexport)
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
	logError = 0,
	logWarning = 1,
	logDebug = 2,
	logTrace = 3,
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
		LOG_API static void defaultConfiguration();
		LOG_API static void log(LogLevel level ,int line, const char* message, const char* location);
		LOG_API static void setLevel(string level);
		LOG_API static LogLevel stringTolevel(string level);
		LOG_API static string levelToString(LogLevel level);
		LOG_API static string preparingInformation(LogLevel level, int line, const char* message, const char* location);
	};

	class LogTime
	{
	public:
		LOG_API struct tm* getCurrentTime();
		LOG_API string timeToString(struct tm timeInfo);
	};

	class CFiles: public CLogger
	{
		ofstream out;
	public:
		LOG_API CFiles(string filename);
		LOG_API ~CFiles();
		LOG_API void saveToFile(string information);
	};

	class CConsole : public CLogger
	{
	public:
		LOG_API void printInConsole(string information);
	};
}


#define NEW_LOG_TRACE(message) CLogger::log(logTrace, __LINE__, message, __FILE__);
#define NEW_LOG_DEBUG(message) CLogger::log(logDebug, __LINE__, message, __FILE__);
#define NEW_LOG_WARNING(message) CLogger::log(logWarning, __LINE__, message, __FILE__);
#define NEW_LOG_ERROR(message) CLogger::log(logError, __LINE__, message, __FILE__);
#define SET_LEVEL(level) CLogger::setLevel(level)

