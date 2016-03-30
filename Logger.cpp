#include "Logger.h"
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

namespace logging_framework
{

	ifstream &operator>>(ifstream &in, datainf &obj)
	{
		in >> obj.level;
		in >> obj.LogName;
		return in;
	}

	CLogger::CLogger()
	{

		ReadLevel();
		outstream .open(dataInf.LogName, ios::app | ios_base::ate);
	}

	CLogger::~CLogger()
	{
		outstream.close();
	}

	void CLogger::ReadLevel()
	{
		ifstream  information;

		information.open("AndreiBikeLogger.txt" , ios::in);
		information >> dataInf;
		information.close();
	}

	void CLogger::Log(int level, const char *message)
	{
		time_t current_time;
		current_time = time(NULL);
		struct tm * timeinfo;
		timeinfo = localtime(&current_time);

		outstream << timeinfo->tm_mday << "/" << timeinfo->tm_mon << "/" << timeinfo->tm_year + 1900 << " " <<
			timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "\t" << level << "\t";
		outstream << message << endl;
	}

	

}

