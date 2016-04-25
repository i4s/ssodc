#pragma once

#include "Logger.h"
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;



namespace logging_framework
{

	datainf CLogger::dataInf;
	bool CLogger::initialise = false;

	ifstream &operator>>(ifstream &in, datainf &obj)
	{
		in >> obj.level;
		in >> obj.LogName;
		return in;
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
			dataInf.level = 0;
			istringstream(value) >> dataInf.level;
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

	void CLogger::log(int line, const char *message)
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
		file.saveToFile(line ,*timeinfo, message);
	}

	CFiles::CFiles(string fileName)
	{
		out.open(fileName, ios::app);
	}

	CFiles::~CFiles()
	{
		out.close();
	}

	void CFiles::saveToFile(int line, struct tm timeinfo, const char *message)
	{
		out << timeinfo.tm_mday << "/" << timeinfo.tm_mon << "/" << timeinfo.tm_year + 1900 << " " <<
		  timeinfo.tm_hour << ":" << timeinfo.tm_min << ":" << timeinfo.tm_sec <<"\t";
		out << message<< "\t" << line << endl;
	}
}

