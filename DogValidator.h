#include <vector>
#include <string>
#include "Dog.h"
#include <exception>

class DogException : public std::exception
{
private:
	std::string message;
public:
	DogException() {};

	/// <summary>
	/// The parameterized constructor
	/// </summary>
	/// <param name="msg"></param>
	DogException(const std::string& msg);

	~DogException() {};

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>the message as a pointer to a string of characters</returns>
	const char* what();
};

class DogValidator
{
public:
	/// <summary>
	/// Check if a dog breed is valid
	/// </summary>
	/// <param name="breed">a string representing the breed of the dog</param>
	static void validateBreed(const std::string& breed);

	/// <summary>
	/// Check if a dog name is valid
	/// </summary>
	/// <param name="breed">a string representing the name of the dog</param>
	static void validateName(const std::string& name);

	/// <summary>
	/// Check if a dog age is valid
	/// </summary>
	/// <param name="age">a integer representing the age of the dog</param>
	static void validateAge(const int & age);

	/// <summary>
	/// Check if a dog photograph link is valid
	/// </summary>
	/// <param name="breed">a string representing the photograph link of the dog</param>
	static void validatePhotographLink(const std::string& photograph_link);
};