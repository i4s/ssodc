#pragma once

#include "Logger.h"
#include "sys_Mutex.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <Windows.h>


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
		ins = ifstream("configLog.cfg");
		char buff[255];
		while (ins.getline(buff, 255))
		{
			parseConfig(buff);
		}
		ins.close();
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

	void CLogger::log(LogLevel level, const char *message)
	{
		g_mutex.Lock();
		if (!initialise) 
		{
			readConfig();
			initialise = true;
		}
		time_t current_time;
		struct tm *timeinfo;
		time(&current_time);
		timeinfo = localtime(&current_time);
		string filename = dataInf.LogName;
		CFiles file(filename);
		file.saveToFile(level, *timeinfo, message);
		g_mutex.Unlock();
	}

	void CLogger::log_crit(LogLevel level ,int line, const char *message, const char* location)
	{
		if (!initialise)
		{
			readConfig();
			initialise = true;
		}
		time_t current_time;
		struct tm *timeinfo;
		time(&current_time);
		timeinfo = localtime(&current_time);
		string filename = dataInf.LogName;
		CFiles file(filename);
		file.saveToFile(level, line, *timeinfo, message, location);
	}

	CFiles::CFiles(string fileName)
	{
		out.open(fileName, ios::app);
	}

	CFiles::~CFiles()
	{
		out.close();
	}

	void CFiles::saveToFile(LogLevel level, struct tm timeinfo, const char *message)
	{
		out << timeinfo.tm_mday << "/" << timeinfo.tm_mon << "/" << timeinfo.tm_year + 1900 << " " <<
		  timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec <<"\t";
		out<<levelToString(level)<< "\t" << message << endl;
	}

	void CFiles::saveToFile(LogLevel level, int line, struct tm timeinfo, const char *message, const char *location)
	{
		saveToFile(level, timeinfo, message);
		out << "\t" << location<< "\t" << line << endl;
	}

	void CLogger::setLevel(string level)
	{

	}
}

