#include "CSVAdoptionList.h"
#include <fstream>
#include "RepositoryExceptions.h"
#include "Windows.h"

void CSVAdoptionList::writeToFile()
{
	std::ofstream fout(file_name);

	if (!fout.is_open())
		throw FileException("The file could not be oppened");

	for (auto s : adoption_list)
		fout << s;

	fout.close();
}

void CSVAdoptionList::displayAdoptionList()
{
	ShellExecuteA(NULL, NULL, "excel.exe", file_name.c_str(), NULL, SW_SHOWMAXIMIZED);
}
