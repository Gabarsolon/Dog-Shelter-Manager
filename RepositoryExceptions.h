#include <string>
#include <exception>
class FileException : public std::exception
{
protected:
	std::string message;
public:

	/// <summary>
	/// The parameterized constructor
	/// </summary>
	/// <param name="message">a string representing the error message</param>
	FileException(const std::string& message);

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>the message as a pointer to a string of characters</returns>
	virtual const char* what();
};

class RepositoryException : public std::exception
{
protected:
	std::string message;

public:
	RepositoryException();

	/// <summary>
	/// The parameterized constructor
	/// </summary>
	/// <param name="msg">a string representing the error message</param>
	RepositoryException(const std::string& msg);
	virtual ~RepositoryException() {}

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>the message as a pointer to a string of characters</returns>
	virtual const char* what();
};

class DuplicateDogException : public RepositoryException
{
public:

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>the message as a pointer to a string of characters</returns>
	const char* what();
};

class InexistentDogException : public RepositoryException
{
public:

	/// <summary>
	/// Get the error message
	/// </summary>
	/// <returns>the message as a pointer to a string of characters</returns>
	const char* what();
};