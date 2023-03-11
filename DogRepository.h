#pragma once
#include <vector>
#include "Dog.h"
class Repository
{
protected:
	std::vector<Dog> dogs;
	std::vector<Dog> delete_history;

public:
	/// <summary>
	/// The default constructor for the repository
	/// </summary>
	Repository();
	
	///Destructor for repository
	~Repository();

	/// <summary>
	/// Add a dog to the dogs list
	/// </summary>
	/// <param name="dog">the dog which will be added</param>
	virtual void addDog(const Dog& dog);

	/// <summary>
	/// Delete a dog from the dogs list
	/// </summary>
	/// <param name="name">a string representing the name of the dog</param>
	virtual Dog deleteDog(const std::string name);

	/// <summary>
	/// Update the name of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a string representing the new name of the dog</param>
	virtual Dog updateDogName(const std::string name, const std::string new_name);

	/// <summary>
	/// Update the breed of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_breed">a string representing the new breed of the dog</param>
	virtual Dog updateDogBreed(const std::string name, const std::string new_breed);

	/// <summary>
	/// Update the age of a dog
	/// </summary>
	/// <param name="name">a integer representing the actual name of the dog</param>
	/// <param name="new_age">a integer representing the new age of the dog</param>
	virtual Dog updateDogAge(const std::string name, const int new_age);

	/// <summary>
	/// Update the link of the photograph of a dog
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_photograph">a string representing the new photograph link of the dog</param>
	virtual Dog updateDogPhotograph(const std::string name, const std::string new_photograph);

	/// <summary>
	/// Find a dog in the dogs list by name
	/// </summary>
	/// <param name="name">a string rerpesenting the name of the dog which we are looking for</param>
	/// <returns>a integer representing the position of the dog in the list</returns>
	int findDog(std::string name);

	/// <summary>
	/// Get a dog from the list of dogs by the position in the list
	/// </summary>
	/// <param name="index">a integer representing the position of the dog in the list</param>
	/// <returns>a Dog object</returns>
	Dog getDog(int index);

	/// <summary>
	/// Get the number of dogs in the list of dogs
	/// </summary>
	/// <returns>a integer representing the number of dogs in the list of dogs</returns>
	int getNrOfDogs() const;
	
	/// <summary>
	/// Get the list of dogs
	/// </summary>
	/// <returns>a dynamic vector with elements of type TElem which contains all of the dogs in the repository</returns>
	std::vector<Dog> getListOfDogs() const;

	/// <summary>
	/// Get the list of dogs who left the shelter
	/// </summary>
	/// <returns>a DynamicVector object containing the dogs</returns>
	std::vector<Dog> getListOfDeletedDogs() const;

	/// <summary>
	/// Add a dog to the user adoption list and remove it from the shelter
	/// </summary>
	/// <param name="name">a string representing the name of the dog which we want to adopt</param>
	void addDogToUserAdoptionList(const std::string name);

	/// <summary>
	/// Get the list of adopted dogs
	/// </summary>
	/// <returns>a dynamic vector of elements of type TElem which contains the adopted dogs</returns>
	std::vector<Dog> getUserAdoptionList() const;
};
