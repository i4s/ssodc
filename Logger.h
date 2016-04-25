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
		 static bool initialise;
	protected:
		 static datainf dataInf;
	public:
		LOG_API static void readConfig();
		LOG_API static void parseConfig(const char *buff);
		LOG_API static void getValue(string source, string &key, string &value);
		LOG_API static void log(int line ,const char* message);
		friend ifstream &operator >> (ifstream &in, datainf &obj);
	};

	

	class CFiles: public CLogger
	{
		ofstream out;
	public:
		LOG_API CFiles(string filename);
		LOG_API ~CFiles();
		LOG_API void saveToFile(int line, struct tm timeInfo, const char *message);
		//LOG_API static void readFromFile();
	};

}


#define NEW_LOG(message) CLogger::log(__LINE__, message);


