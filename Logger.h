#pragma once

#ifdef _WIN32
#ifdef LOGGING_EXPORTS
#define LOG_API  __declspec(dllimport)
#else
#define LOG_API  __declspec(dllexport)
#endif
#endif


#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "sys_Mutex.h"
#include "LogMacros.h"

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
#ifdef _WIN32
		LOG_API static void readConfig();
		LOG_API static void parseConfig(const char *buff);
		LOG_API static void getValue(string source, string &key, string &value);
		LOG_API static void defaultConfiguration();
		LOG_API static void log(LogLevel level ,int line, const char* message, const char* location);
		LOG_API static void setLevel(string level);
		LOG_API static LogLevel stringTolevel(string level);
		LOG_API static string levelToString(LogLevel level);
		LOG_API static string preparingInformation(LogLevel level, int line, const char* message, const char* location);
#else
		static void readConfig();
		static void parseConfig(const char *buff);
		static void getValue(string source, string &key, string &value);
		static void defaultConfiguration();
		static void log(LogLevel level, int line, const char* message, const char* location);
		static void setLevel(string level);
		static LogLevel stringTolevel(string level);
		static string levelToString(LogLevel level);
		static string preparingInformation(LogLevel level, int line, const char* message, const char* location);
#endif
	};
}


