#include "RepositoryExceptions.h"

FileException::FileException(const std::string& message) : message(message)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message("")
{
}

RepositoryException::RepositoryException(const std::string& message) : message(message)
{
}

const char* RepositoryException::what()
{
	return message.c_str();
}

const char* DuplicateDogException::what()
{
	return "There is another dog with the same name\n";
}

const char* InexistentDogException::what()
{
	return "There are no dogs with the given name\n";
}
