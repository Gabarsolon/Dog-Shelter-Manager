#pragma once
#include <string>
#include "DogRepository.h"

class FileRepository : public Repository {
private:
	std::string file_name;

	/// <summary>
	/// Save the current state of the repository into the file
	/// </summary>
	void saveData();

	/// <summary>
	/// Load every entity from the file
	/// </summary>
	void loadData();
public:
	FileRepository();

	/// <summary>
	/// The parameterized constructor
	/// </summary>
	/// <param name="_file_name">a string representing the name of the file where the repository will be stored</param>
	FileRepository(std::string _file_name);

	/// <summary>
	/// Add a dog to the dogs list
	/// </summary>
	/// <param name="dog">the dog which will be added</param>
	void addDog(const Dog& dog) override;

	/// <summary>
	/// Delete a dog from the dogs list
	/// </summary>
	/// <param name="name">a string representing the name of the dog</param>
	Dog deleteDog(const std::string name) override;

	/// <summary>
	/// Update the name of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a string representing the new name of the dog</param>
	Dog updateDogName(const std::string name, const std::string new_name) override;

	/// <summary>
	/// Update the breed of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_breed">a string representing the new breed of the dog</param>
	Dog updateDogBreed(const std::string name, const std::string new_breed) override;

	/// <summary>
	/// Update the age of a dog
	/// </summary>
	/// <param name="name">a integer representing the actual name of the dog</param>
	/// <param name="new_age">a integer representing the new age of the dog</param>
	Dog updateDogAge(const std::string name, const int new_age) override;

	/// <summary>
	/// Update the link of the photograph of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_photograph">a string representing the new photograph link of the dog</param>
	Dog updateDogPhotograph(const std::string name, const std::string new_photograph) override;


};