#include "DogValidator.h"

DogException::DogException(const std::string& msg) : message(msg)
{
}

const char* DogException::what()
{
	return message.c_str();
}

void DogValidator::validateBreed(const std::string& breed)
{
	if (breed.size() < 3)
		throw DogException("The dog's breed cannot be less than 3 characters\n");
}

void DogValidator::validateName(const std::string& name)
{
	if (!isupper(name[0]))
		throw DogException("The dog's name must begin with a upper case letter\n");
}

void DogValidator::validateAge(const int& age)
{
	if (age <= 0)
		throw DogException("The dog's age must be greater than 0\n");
}

void DogValidator::validatePhotographLink(const std::string& photograph_link)
{
	if (photograph_link.find("http") != 0)
		throw DogException("The given link is invalid (it must start with http) \n");
}
