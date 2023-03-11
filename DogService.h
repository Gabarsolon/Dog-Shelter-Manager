#pragma once
#include "DogRepository.h"
#include "DogFileRepository.h"
#include "DogValidator.h"
#include "FileAdoptionList.h"
#include "RepositoryExceptions.h"
#include <memory>
#include "undo.h"

class Service
{
private:
	Repository & repository;
	FileAdoptionList* file_adoption_list;
	DogValidator validator;
	std::vector<std::unique_ptr<UndoRedoAction>> undoActions;
	std::vector<std::unique_ptr<UndoRedoAction>> redoActions;

public:
	/// <summary>
	/// The parametrized constructor for service
	/// </summary>
	/// <param name="repository">a Repository object used for working with</param>
	Service(Repository & _repository, FileAdoptionList* _adoption_list, DogValidator _validator);

	~Service();
	/// <summary>
	/// Add a dog to the repository
	/// </summary>
	/// <param name="breed">a string representing the breed</param>
	/// <param name="name">a string representing the name</param>
	/// <param name="age">a integer representing the age</param>
	/// <param name="photograph">a string representing the link of the photograph</param>
	void addDog(std::string breed, std::string name, int age, std::string photograph);

	/// <summary>
	/// Delete a dog from the repository
	/// </summary>
	/// <param name="name">a string representing the name</param>
	void deleteDog(std::string name);

	/// <summary>
	/// Update the name of a dog from the repository
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a string representing the new name of the dog</param>
	void updateDogName(std::string name, std::string new_name);

	/// <summary>
	/// Update the breed of a dog from the repository
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a string representing the new breed of the dog</param>
	void updateDogBreed(std::string name,std::string new_breed);

	/// <summary>
	/// Update the age of a dog from the repository
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a integer representing the new age of the dog</param>
	void updateDogAge( std::string name,  int new_age);

	/// <summary>
	/// Update the link of a photograph of a dog from the repository
	/// </summary>
	/// <param name="name">a string representing the actual name of the dog</param>
	/// <param name="new_name">a string representing the new link of the photograph of the dog</param>
	void updateDogPhotograph( std::string name, std::string new_photograph);

	/// <summary>
	/// Undo the last performed operation
	/// </summary>
	void undo();

	/// <summary>
	/// Redo the last performed operation
	/// </summary>
	void redo();

	/// <summary>
	/// Get a dog from the repository by the position in it
	/// </summary>
	/// <param name="index">a integer representing the position of the dog in the repository</param>
	/// <returns>a Dog object representing the dog which we are looking for</returns>
	Dog getDog(int index);

	/// <summary>
	/// Get the number of dogs in the repository
	/// </summary>
	/// <returns>a integer representing the number of dogs</returns>
	int getNrOfDogs() const;

	/// <summary>
	/// Get a dog from the list of deleted dogs from the repository by the position of the dog in the list
	/// </summary>
	/// <param name="index">a integer representing the positino of the dog in the list</param>
	/// <returns>a Dog object representing the required dog</returns>
	std::vector<Dog> getListOfDeletedDogs();

	/// <summary>
	/// Adopt a dog
	/// </summary>
	/// <param name="name">a string representing the name of the dog which we want to adopt</param>
	void adoptDog(std::string name);

	/// <summary>
	/// Get the list of dogs
	/// </summary>
	/// <returns>a dynamic vector with elements of type TElem which contains all of the dogs in the repository</returns>
	std::vector<Dog> getAllDogs() const;

	/// <summary>
	/// Get the list of adopted dogs
	/// </summary>
	/// <returns>a dynamic vector of elements of type TElem which contains the adopted dogs</returns>
	std::vector<Dog> getListOfAdoptedDogs();

	/// <summary>
	/// Get the list of dogs having a given breed and a age lower than a given one
	/// </summary>
	/// <param name="breed"></param>
	/// <param name="age"></param>
	/// <returns></returns>
	std::vector<Dog> getDogsOfAGivenBreedHavingASpecificAge(std::string breed, int age);
	
	/// <summary>
	/// Display the adoption list by opening the corresponding application ( excel or chrome )
	/// </summary>
	void displayAdoptionList();

	/// <summary>
	/// Change the format of the adoption list
	/// </summary>
	/// <param name="_fileAdoptionList">the file adoption list</param>
	void setFileAdoptionList(FileAdoptionList* _fileAdoptionList);

	/// <summary>
	/// Get the adoption list
	/// </summary>
	/// <returns>a pointer to a FileAdoptionList</returns>
	FileAdoptionList* getFileAdoptionList();

	/// <summary>
	/// Get the list of all dog breeds which are presents in the shelter
	/// </summary>
	/// <returns>a vector of strings representing the dog breeds</returns>
	std::vector<std::string> getDogBreeds();
};
