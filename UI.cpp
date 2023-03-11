#include "UI.h"
#include <iostream>
#include <Windows.h>

void UI::printDog(Dog dog)
{
	std::cout << "\nBreed: " << dog.getBreed()
		<< "\nName: " << dog.getName()
		<< "\nAge: " << dog.getAge()
		<< "\nPhotograph: " << dog.getPhotograph() << "\n\n";
}

void UI::printAdoptionMenu(std::vector<Dog> list_of_dogs)
{

	int index = 0;
	while (list_of_dogs.size() > 0)
	{
		Dog dog = list_of_dogs[index];
		printDog(dog);
		//ShellExecuteA(NULL, NULL, "chrome.exe", dog.getPhotograph().c_str(), NULL, SW_SHOWMAXIMIZED);
		std::cout << "1.Adopt the dog\n";
		std::cout << "2.See the next dog\n";
		std::cout << "3.Exit\n";
		std::cout << "Input a option: ";
		std::string adoption_option_string;
		getline(std::cin, adoption_option_string);
		int adoption_option = stoi(adoption_option_string);
		if (adoption_option == 1)
		{
			service.adoptDog(dog.getName());
			list_of_dogs.erase(list_of_dogs.begin() + index);
			std::cout << "Dog adopted successfully\n";
		}
		else if (adoption_option == 3)
		{
			return;
		}
		index++;
		if (index >= list_of_dogs.size())
			index = 0;
	}
	std::cout << "No more dogs in the shelter";
}

bool UI::chooseAdoptionFileType()
{
	while (true)
	{
		std::cout << "How do you want to store the adoption list( enter CSV if you want it as a csv file or HTML otherwise ) \n";
		std::string option;
		getline(std::cin, option);
		if (option == "CSV")
			return 0;
		if (option == "HTML")
			return 1;
		std::cout << "Invalid option.Try again\n";
	}
}

UI::UI(Service & service) : service(service)
{
}

UI::~UI()
{
}

void UI::startUI()
{
	while (true)
	{
		try {
			std::cout << "1.Administrator mode\n";
			std::cout << "2.User mode\n";
			std::cout << "3.Exit\n";
			std::cout << "Input a option: ";
			std::string option_string;
			getline(std::cin, option_string);
			int option = stoi(option_string);
			if (option == 1)
			{			
				std::cout << "\n1.Add a dog in the shelter\n";
				std::cout << "2.Delete a dog from the shelter\n";
				std::cout << "3.Update a dog from the shelter\n";
				std::cout << "4.Display all dogs who are in the shelter\n";
				std::cout << "5.Get the list of all dogs who left the shelter\n";
				std::cout << "Input a option: ";
				std::string admin_string;
				getline(std::cin, admin_string);
				int admin_option = stoi(admin_string);
				if (admin_option == 1)
				{
					std::string breed;
					std::string name;
					std::string age_string;
					std::string photograph;
					std::cout << "Input the breed: ";
					getline(std::cin, breed);
					std::cout << "Input the name: ";
					getline(std::cin, name);
					std::cout << "Input the age: ";
					getline(std::cin, age_string);
					int age = stoi(age_string);
					std::cout << "Input the link of the photograph: ";
					getline(std::cin, photograph);
					service.addDog(breed, name, age, photograph);
					std::cout << "Dog addded succesfully";
				}
				else if (admin_option == 2)
				{
					std::string name;
					std::cout << "Input the name: ";
					getline(std::cin, name);
					service.deleteDog(name);
					std::cout << "Dog deleted succesfully";
				}
				else if (admin_option == 3)
				{
					std::string name;
					std::cout << "Input the name: ";
					getline(std::cin, name);
					std::cout << "1.Update the breed\n";
					std::cout << "2.Update the name\n";
					std::cout << "3.Update the age\n";
					std::cout << "4.Update the photograph link\n";
					std::cout << "Input a option: ";
					std::string update_option_string;
					getline(std::cin, update_option_string);
					int update_option = stoi(update_option_string);
					if (update_option == 1)
					{
						std::string new_breed;
						std::cout << "Input the new breed: ";
						getline(std::cin, new_breed);
						service.updateDogBreed(name, new_breed);
						std::cout << "Breed updated successfully";
					}
					else if (update_option == 2)
					{
						std::string new_name;
						std::cout << "Input the new name: ";
						getline(std::cin, new_name);
						service.updateDogBreed(name, new_name);
						std::cout << "Name updated successfully";
					}
					else if (update_option == 3)
					{
						std::cout << "Input the new age: ";
						std::string age_string;
						getline(std::cin, age_string);
						int new_age = stoi(age_string);
						service.updateDogAge(name, new_age);
						std::cout << "Age updated successfully";
					}
					else if (update_option == 4)
					{
						std::string new_photograph;
						std::cout << "Input a new photograph link: ";
						getline(std::cin, new_photograph);
						service.updateDogPhotograph(name, new_photograph);
						std::cout << "Photograph link updated successfully";
					}
					else
						throw std::runtime_error("Invalid option");
				}
				else if (admin_option == 4)
				{
					for (const auto dog : service.getAllDogs())
						printDog(dog);
				}
				else if (admin_option == 5)
				{
					for (const auto dog: service.getListOfDeletedDogs())
						printDog(dog);
				}
				else
					throw std::runtime_error("Invalid option");
			}
			else if (option == 2)
			{
				std::cout << "\n1.See the dogs in the database, one by one";
				std::cout << "\n2.See all the dogs of a given breed, having an age less than a given number";
				std::cout << "\n3.See the adoption list";
				std::cout << "\nInput a option: ";
				std::string user_option_string;
				getline(std::cin, user_option_string);
				int user_option = stoi(user_option_string);
				if (user_option == 1)
					printAdoptionMenu(service.getAllDogs());
				else if (user_option == 2)
				{
					std::string breed;
					std::string age;
					std::cout << "Input the breed (enter -1 if you want to consider all of the dogs): ";
					getline(std::cin, breed);
					std::cout << "Input the age: ";
					getline(std::cin, age);
					int age_i = stoi(age);
					auto list_of_dogs = service.getDogsOfAGivenBreedHavingASpecificAge(breed, age_i);
					printAdoptionMenu(list_of_dogs);
				}
				else if (user_option == 3)
				{
					service.displayAdoptionList();
				}
				else
					throw std::runtime_error("Invalid option");
			}
			else if (option == 3)
				break;
			else
				throw std::runtime_error("Invalid option");
			std::cout << "\n\n";
		}
		catch (DogException& ex)
		{
			std::cout << ex.what();
		}
		catch (DuplicateDogException& ex)
		{
			std::cout << ex.what();
		}
		catch (InexistentDogException& ex)
		{
			std::cout << ex.what();
		}
		catch (const std::exception& error_message)
		{	
			std::string message = error_message.what();
			if (message == "invalid stoi argument")
				std::cout << "You must input a valid number\n";
			else
				std::cout << message << "\n\n";
		}
	}
}
