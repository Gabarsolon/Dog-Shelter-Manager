#include "DogFileRepository.h"
#include <fstream>
#include "RepositoryExceptions.h"

FileRepository::FileRepository()
{
}

FileRepository::FileRepository(std::string _file_name)
{
	file_name = _file_name;
	loadData();
}

void FileRepository::saveData()
{
	std::ofstream fout(file_name);

	if (!fout.is_open())
		throw FileException("The file could not be opened");

	if (dogs.size() == 0)
		fout << "";
	else
		for (auto dog : dogs)
			fout << dog;
	fout.close();
}

void FileRepository::loadData()
{
	std::ifstream fin(file_name);

	if (!fin.is_open())
		throw FileException("The file could not be opened");

	Dog dog;
	while (fin >> dog)
		dogs.push_back(dog);

	fin.close();
}

void FileRepository::addDog(const Dog& dog)
{
	Repository::addDog(dog);
	saveData();
}

Dog FileRepository::deleteDog(const std::string name)
{
	Dog oldDog = Repository::deleteDog(name);
	saveData();
	return oldDog;
}

Dog FileRepository::updateDogName(const std::string name, const std::string new_name)
{
	Dog oldDog = Repository::updateDogName(name, new_name);
	saveData();
	return oldDog;
}

Dog FileRepository::updateDogBreed(const std::string name, const std::string new_breed)
{
	Dog oldDog = Repository::updateDogBreed(name, new_breed);
	saveData();
	return oldDog;
}

Dog FileRepository::updateDogAge(const std::string name, const int new_age)
{
	Dog oldDog = Repository::updateDogAge(name, new_age);
	saveData();
	return oldDog;
}

Dog FileRepository::updateDogPhotograph(const std::string name, const std::string new_photograph)
{
	Dog oldDog = Repository::updateDogPhotograph(name, new_photograph);
	saveData();
	return oldDog;
}
