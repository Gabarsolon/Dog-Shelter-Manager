#pragma once
#include <string>

class Dog {
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;

public:
	/// <summary>
	/// Default constructor for dog
	/// </summary>
	Dog();

	/// <summary>
	/// Parameterized constructor for dog
	/// </summary>
	/// <param name="breed">a string representing the breed</param>
	/// <param name="name">a string representing the name</param>
	/// <param name="age">a integer representing the age</param>
	/// <param name="photograph">a string representing the photograph link</param>
	Dog(std::string breed, std::string name, int age, std::string photograph);

	/// <summary>
	/// The copy constructor for dog
	/// </summary>
	/// <param name="dog">a Dog object used for copy</param>
	Dog(const Dog& dog);

	~Dog();
	/// <summary>
	/// Check if 2 dogs are equal
	/// </summary>
	/// <param name="lhs">a Dog object used for comparsion</param>
	/// <param name="rhs">a Dog object used for comparsion</param>
	/// <returns>True, if they are equal, false otherwise</returns>
	friend bool operator==(const Dog& lhs, const Dog& rhs);

	/// <summary>
	/// Get the breed of a dog
	/// </summary>
	/// <returns>a string representing the breed</returns>
	std::string getBreed() const;

	/// <summary>
	/// Get the name of a dog
	/// </summary>
	/// <returns>a string representing the name</returns>
	std::string getName() const;

	/// <summary>
	/// Get the age of a dog
	/// </summary>
	/// <returns>a integer representing the age</returns>
	int getAge() const;

	/// <summary>
	/// Get the link of the photograph of a dog
	/// </summary>
	/// <returns>a string representing the link of the photograph</returns>
	std::string getPhotograph() const;

	/// <summary>
	/// Set the breed for a dog
	/// </summary>
	/// <param name="_breed">a string representing the new breed</param>
	void setBreed(std::string _breed);

	/// <summary>
	/// Set the name for a dog
	/// </summary>
	/// <param name="_breed">a string representing the new name</param>
	void setName(std::string _name);

	/// <summary>
	/// Set the age for a dog
	/// </summary>
	/// <param name="_breed">a integer representing the new age</param>
	void setAge(int _age);

	/// <summary>
	/// Set the photograph link for a dog
	/// </summary>
	/// <param name="_breed">a string representing the new photograph link</param>
	void setPhotograph(std::string _photograph);

	/// <summary>
	/// Overload the extraction operator
	/// </summary>
	/// <param name="stream">a istream object from which we get the dog information</param>
	/// <param name="dog">the dog object</param>
	/// <returns>the istream object</returns>
	friend std::istream& operator>>(std::istream& stream, Dog& dog);

	/// <summary>
	/// Overload the insertion operator
	/// </summary>
	/// <param name="stream">a ostream object to which we will store the dog information</param>
	/// <param name="dog">the dog object</param>
	/// <returns>the ostream object</returns>
	friend std::ostream& operator<<(std::ostream& stream, const Dog& dog);
};
