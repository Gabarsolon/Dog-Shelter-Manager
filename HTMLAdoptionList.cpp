#include "HTMLAdoptionList.h"
#include "RepositoryExceptions.h"
#include <fstream>
#include <Windows.h>
#include <filesystem>

void HTMLAdoptionList::writeToFile()
{
	std::ofstream fout(file_name);

	if (!fout.is_open())
		throw FileException("The file doens't exist");
	
	fout << "<!DOCTYPE html><html><head><title><Dog adoption list></title>";
	fout << "</head><body><table border=\"1\"><tr><td>Breed</td><td>Name</td><td>Age</td><td>Photograph Link</td></tr>";
	for (auto dog : adoption_list)
	{
		fout<<"<tr><td>" << dog.getBreed() << 
			"</td><td>" << dog.getName() << 
			"</td><td>" << dog.getAge() <<
			"</td><td><a href=\"" << dog.getPhotograph() <<
			"\">Link</a></td></tr>";
	}
	fout << "</table></body></html>";
	fout.close();
}

void HTMLAdoptionList::displayAdoptionList()
{
	std::string path = "C:\\Users\\Turcu\\source\\repos\\cs-ubbcluj-ro\\a14-Gabarsolon\\a11_12\\" + file_name;
	ShellExecuteA(NULL, NULL, "chrome.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}
