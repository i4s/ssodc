#pragma once

#include "Logger.h"
#include "CFiles.h"
#include "LogTime.h"
#include "CConsole.h"
#include "sys_Mutex.h"
#include <iostream>
#include <time.h>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#endif

#define DEFAULT_LOG_FILENAME "default_log.txt"
#define DEFAULT_CONFIG_NAME "configLog.cfg"

using namespace std;

namespace logging_framework
{

	datainf CLogger::dataInf;
	bool CLogger::initialise = false;
	sys::Mutex CLogger::g_mutex;

	LogLevel CLogger::stringTolevel(string level)
	{
		if (level == "DEBUG")
			return logDebug;
		if (level == "TRACE")
			return logTrace;
		if (level == "WARNING")
			return logWarning;
		if (level == "ERROR")
			return logError;

		return logTrace;
	}

	string CLogger::levelToString(LogLevel level)
	{
		switch (level)
		{
		case logTrace:
			return "TRACE";
		case logDebug:
			return "DEBUG";
		case logWarning:
			return "WARNING";
		case logError:
			return "ERROR";
		default:
			return "TRACE";
		}
	}

    void CLogger::readConfig()
	{
		ifstream ins;
		ins.open(DEFAULT_CONFIG_NAME);
		if (!ins)
		{
			defaultConfiguration();
		}
		else
		{
			char buff[255];
			while (ins.getline(buff, 255))
			{
				parseConfig(buff);
			}
			ins.close();
		}
	}

	void CLogger::parseConfig(const char *str)
	{
		string buff = str;
		int commentPos = buff.find("#");
		if (commentPos > -1)
		{
			buff = buff.substr(0, commentPos);
		}
		if (buff.find("level") < -1)
		{
			string key, value;
			getValue(buff, key, value);
			dataInf.level = logTrace;
			dataInf.level = CLogger::stringTolevel(value);
		}
		if (buff.find("filename") < -1)
		{
			string key, value;
			getValue(buff, key, value);
			dataInf.LogName = value;
		}
	}

	void CLogger::getValue(string source, string &key, string &value)
	{
		int pos = source.find("=");
		key = source.substr(0, pos);
		value = source.substr(pos + 1);
	}

	void CLogger::defaultConfiguration()
	{
		LogTime logTime;
		struct tm *timeinfo = logTime.getCurrentTime();
		dataInf.LogName = DEFAULT_LOG_FILENAME;
		dataInf.level = logTrace;
	}

	
	void CLogger::log(LogLevel level ,int line, const char *message, const char* location)
	{
		g_mutex.Lock();
		if (!initialise)
		{
			readConfig();
			initialise = true;
		}
		if (level <= dataInf.level)
		{
			string filename = dataInf.LogName;
			CFiles file(filename);
			CConsole console;
			string information = preparingInformation(level, line, message, location);
			console.printInConsole(information);
			file.saveToFile(information);
		}
		g_mutex.Unlock();
	}

	void CLogger::setLevel(string level)
	{
		if (!initialise)
		{
			readConfig();
			initialise = true;
		}
		LogLevel setLogLevel = stringTolevel(level);
		dataInf.level = setLogLevel;
	}

	string CLogger::preparingInformation(LogLevel level, int line, const char* message, const char* location)
	{
		std::ostringstream oss;
		LogTime logTime;
		oss << logTime.timeToString(*logTime.getCurrentTime());
		oss << "\t" << levelToString(level);
		oss << "\t" << message;
		oss << "\n" << "\t" << location;
		oss << "\t" << line;
		return	oss.str();
	}
}

