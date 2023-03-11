#pragma once
#include "FileAdoptionList.h"

class HTMLAdoptionList : public FileAdoptionList
{
public:
	/// <summary>
	/// Write the current state of the adoption list to the html file
	/// </summary>
	void writeToFile() override;

	/// <summary>
	/// Display the adoption list by opening the html file with chrome
	/// </summary>
	void displayAdoptionList() override;
};
