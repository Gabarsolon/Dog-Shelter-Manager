#include "Dog.h"
#include <vector>
#include <sstream>

Dog::Dog():breed(""), name(""), age(0), photograph("")
{
}

Dog::Dog(std::string breed, std::string name, int age, std::string photograph)
:breed(breed), name(name), age(age), photograph(photograph)
{
}

Dog::Dog(const Dog& dog)
	:breed(dog.breed), name(dog.name), age(dog.age), photograph(dog.photograph)
{
}


Dog::~Dog()
{
}

std::string Dog::getBreed() const
{
	return breed;
}

std::string Dog::getName() const
{
	return name;
}

int Dog::getAge() const
{
	return age;
}

std::string Dog::getPhotograph() const
{
	return photograph;
}

void Dog::setBreed(std::string _breed)
{
	breed = _breed;
}

void Dog::setName(std::string _name)
{
	name = _name;
}

void Dog::setAge(int _age)
{
	age = _age;
}

void Dog::setPhotograph(std::string _photograph)
{
	photograph = _photograph;
}


bool operator==(const Dog& lhs, const Dog& rhs)
{
	return lhs.breed == rhs.breed
		&& lhs.name == rhs.name
		&& lhs.age == rhs.age
		&& lhs.photograph == rhs.photograph;
}

std::istream& operator>>(std::istream& stream, Dog& dog)
{
	std::string line;
	getline(stream, line);
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string token;
	while (getline(ss, token, ','))
		tokens.push_back(token);
	if (tokens.size() != 4)
		return stream;
	dog.breed = tokens[0];
	dog.name = tokens[1];
	dog.age = stoi(tokens[2]);
	dog.photograph = tokens[3];
	
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Dog& dog)
{
	stream << dog.breed << ',' << dog.name << ',' << dog.age << ',' << dog.photograph << '\n';
	return stream;
}
