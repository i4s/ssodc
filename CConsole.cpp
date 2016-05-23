#include "CConsole.h"

namespace logging_framework
{
	void CConsole::printInConsole(string information)
	{
		setlocale(LC_ALL, "Russian");
		cout << information << endl;
	}
}