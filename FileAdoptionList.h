#pragma once
#include <string>
#include <vector>
#include "Dog.h"
class FileAdoptionList
{
protected:
	std::string file_name;
	std::vector<Dog> adoption_list;
public:
	FileAdoptionList();
	virtual ~FileAdoptionList(){};

	/// <summary>
	/// Add a dog to the adoption list
	/// </summary>
	/// <param name="dog">the dog which will be added</param>
	void addDogToUserAdoptionList(const Dog& dog);

	/// <summary>
	/// Get the adoption list
	/// </summary>
	/// <returns>a vector containing the adopted dogs</returns>
	std::vector<Dog> getUserAdoptionList() const;

	/// <summary>
	/// Set the name of the file which will be used for storing the adoption list
	/// </summary>
	/// <param name="_file_name">a string representing the name of the file</param>
	void setFileName(const std::string& _file_name);

	/// <summary>
	/// Write to file the current state of the adoption list
	/// </summary>
	virtual void writeToFile() = 0;

	/// <summary>
	/// Display the adoption list by opening the corresponding application ( excel or chrome )
	/// </summary>
	virtual void displayAdoptionList() = 0;
};