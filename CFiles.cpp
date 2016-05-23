#pragma once

#include "Logger.h"
#include "CFiles.h"
#include <fstream>

using namespace std;

namespace logging_framework
{
	CFiles::CFiles(string fileName)
	{
		out.open(fileName, ios::app);
	}

	CFiles::~CFiles()
	{
		out.close();
	}

	void CFiles::saveToFile(string information)
	{
		out << information << endl;
	}
}