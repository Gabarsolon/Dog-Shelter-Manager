#pragma once
#include "FileAdoptionList.h"
class CSVAdoptionList : public FileAdoptionList
{
public:
	/// <summary>
	/// Write the current state of the adoption list to the csv file
	/// </summary>
	void writeToFile() override;
	
	/// <summary>
	/// Display the adoption list by opening the csv file with 
	/// </summary>
	void displayAdoptionList() override;
};