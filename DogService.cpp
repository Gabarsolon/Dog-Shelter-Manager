#include "DogService.h"
#include <algorithm>
#include <iostream>
Service::Service(Repository & _repository, FileAdoptionList* _adoption_list , DogValidator _validator) : repository(_repository), file_adoption_list(_adoption_list), validator(_validator)
{
}

Service::~Service()
{
}

void Service::addDog(std::string breed, std::string name, int age, std::string photograph)
{
	validator.validateBreed(breed);
	validator.validateName(name);
	validator.validateAge(age);
	validator.validatePhotographLink(photograph);
	Dog dogToAdd(breed, name, age, photograph);
	repository.addDog(dogToAdd);

	undoActions.push_back(std::make_unique<UndoRedoAdd>(repository, dogToAdd));
	redoActions.clear();
}

void Service::deleteDog(std::string name)
{
	auto oldDog = repository.deleteDog(name);
	
	undoActions.push_back(std::make_unique<UndoRedoRemove>(repository, oldDog));
	redoActions.clear();
}

void Service::updateDogName(std::string name, std::string new_name)
{
	validator.validateName(new_name);
	Dog oldDog = repository.updateDogName(name, new_name);
	Dog newDog(oldDog.getBreed(), new_name, oldDog.getAge(), oldDog.getPhotograph());
	undoActions.push_back(std::make_unique<UndoRedoUpdate>(repository, oldDog, newDog));
	redoActions.clear();
}

void Service::updateDogBreed(std::string name, std::string new_breed)
{
	validator.validateBreed(new_breed);
	Dog oldDog = repository.updateDogBreed(name, new_breed);
	Dog newDog(new_breed, name , oldDog.getAge(), oldDog.getPhotograph());
	newDog.setBreed(new_breed);
	undoActions.push_back(std::make_unique<UndoRedoUpdate>(repository, oldDog, newDog));
	redoActions.clear();
}

void Service::updateDogAge(std::string name, int new_age)
{
	validator.validateAge(new_age);
	Dog oldDog = repository.updateDogAge(name, new_age);
	Dog newDog(oldDog.getBreed(), name, new_age, oldDog.getPhotograph());
	newDog.setAge(new_age);
	undoActions.push_back(std::make_unique<UndoRedoUpdate>(repository, oldDog, newDog));
	redoActions.clear();
}

void Service::updateDogPhotograph(std::string name, std::string new_photograph)
{
	validator.validatePhotographLink(new_photograph);
	Dog oldDog = repository.updateDogPhotograph(name, new_photograph);
	Dog newDog(oldDog.getBreed(), name, oldDog.getAge(), new_photograph);
	newDog.setPhotograph(new_photograph);
	undoActions.push_back(std::make_unique<UndoRedoUpdate>(repository, oldDog, newDog));
	redoActions.clear();
}

void Service::undo()
{
	if (undoActions.empty())
		throw RepositoryException("Cannot undo anymore");
	std::unique_ptr<UndoRedoAction> last = move(undoActions.back());
	last->undo();
	undoActions.pop_back();
	redoActions.push_back(move(last));
}

void Service::redo()
{
	if (redoActions.empty())
		throw RepositoryException("Cannot redo anymore");
	std::unique_ptr<UndoRedoAction> last = move(redoActions.back());
	last->redo();
	redoActions.pop_back();
	undoActions.push_back(move(last));
}

Dog Service::getDog(int index)
{
	return repository.getDog(index);
}

int Service::getNrOfDogs() const
{
	return repository.getNrOfDogs();
}

std::vector<Dog> Service::getListOfDeletedDogs()
{
	return repository.getListOfDeletedDogs();
}

void Service::adoptDog(std::string name)
{
	file_adoption_list->addDogToUserAdoptionList(repository.getDog(repository.findDog(name)));
	repository.deleteDog(name);
	file_adoption_list->writeToFile();
}

std::vector<Dog> Service::getAllDogs () const
{
	return repository.getListOfDogs();
}

std::vector<Dog> Service::getListOfAdoptedDogs()
{
	return file_adoption_list->getUserAdoptionList();
}

std::vector<Dog> Service::getDogsOfAGivenBreedHavingASpecificAge(std::string breed, int age)
{
	auto dogs = repository.getListOfDogs();
	std::vector<Dog> required_dogs_list;
	auto it = std::copy_if(dogs.begin(), dogs.end(), std::back_inserter(required_dogs_list), 
		[breed, age](auto dog) {return (dog.getBreed() == breed || breed == "-1") && ( dog.getAge() < age || age==-1 ); });
	//required_dogs_list.resize(std::distance(required_dogs_list.begin(), it));
	return required_dogs_list;
}

void Service::displayAdoptionList()
{
	file_adoption_list->displayAdoptionList();
}

void Service::setFileAdoptionList(FileAdoptionList* _fileAdoptionList)
{
	file_adoption_list = _fileAdoptionList;
}

FileAdoptionList* Service::getFileAdoptionList()
{
	return file_adoption_list;
}

std::vector<std::string> Service::getDogBreeds()
{
	std::vector<std::string> dogBreedsList;
	for (auto dog : repository.getListOfDogs())
	{
		std::string breed = dog.getBreed();
		if (std::find_if(dogBreedsList.begin(), dogBreedsList.end(),
			[breed](auto breed_to_compare) { return breed == breed_to_compare; }) == dogBreedsList.end())
			dogBreedsList.push_back(breed);
	}
	return dogBreedsList;
}
