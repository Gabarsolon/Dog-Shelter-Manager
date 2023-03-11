#include "FileAdoptionList.h"
#include "DogRepository.h"


FileAdoptionList::FileAdoptionList()
{
}

void FileAdoptionList::addDogToUserAdoptionList(const Dog& dog)
{
	adoption_list.push_back(dog);
}

void FileAdoptionList::setFileName(const std::string& _file_name)
{
	file_name = _file_name;
}

std::vector<Dog> FileAdoptionList::getUserAdoptionList() const
{
	return adoption_list;
}