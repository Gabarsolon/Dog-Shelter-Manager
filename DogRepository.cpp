#include "DogRepository.h"
#include "Dog.h"
#include <stdexcept>
#include <algorithm>
#include "RepositoryExceptions.h"

Repository::Repository()
{
}

Repository::~Repository()
{
}

int Repository::findDog(std::string name)
{
	auto it = std::find_if(dogs.begin(), dogs.end(),
		[name](auto dog_to_compare) { return dog_to_compare.getName() == name; });
	if (dogs.end() == it)
		return -1;
	return int(it - dogs.begin());
}

Dog Repository::getDog(int index)
{
	return dogs[index];
}

int Repository::getNrOfDogs() const
{
	return int(dogs.size());
}

std::vector<Dog> Repository::getListOfDogs() const
{
	return dogs;
}

std::vector<Dog> Repository::getListOfDeletedDogs() const
{
	return delete_history;
}

void Repository::addDog(const Dog& dog)
{
	int index = findDog(dog.getName());
	if(index!=-1 && dogs.size() > 0)
		throw DuplicateDogException();
	else {
		dogs.push_back(dog);
	}
}

Dog Repository::deleteDog(const std::string name)
{
	int index = findDog(name);
	if (index == -1)
		throw InexistentDogException();
	Dog oldDog = dogs[index];
	delete_history.push_back(oldDog);
	dogs.erase(dogs.begin() + index);
	return oldDog;
}

Dog Repository::updateDogName(const std::string name, const std::string new_name)
{
	int index = findDog(new_name);
	if (index != -1)
		throw DuplicateDogException();
	index = findDog(name);
	if(index == -1)
		throw InexistentDogException();
	Dog oldDog = dogs[index];
	dogs[index].setName(new_name);
	return oldDog;
}

Dog Repository::updateDogBreed(const std::string name, const std::string new_breed)
{
	int index = findDog(name);
	if (index == -1)
		throw InexistentDogException();
	Dog oldDog = dogs[index];
	dogs[index].setBreed(new_breed);
	return oldDog;
}

Dog Repository::updateDogAge(const std::string name, const int new_age)
{
	int index = findDog(name);
	if (index == -1)
		throw InexistentDogException();
	Dog oldDog = dogs[index];
	dogs[index].setAge(new_age);
	return oldDog;
}

Dog Repository::updateDogPhotograph(const std::string name, const std::string new_photograph)
{
	int index = findDog(name);
	if (index == -1)
		throw InexistentDogException();
	Dog oldDog = dogs[index];
	dogs[index].setPhotograph(new_photograph);
	return oldDog;
}
