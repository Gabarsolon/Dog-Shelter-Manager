#pragma once
#include "DogService.h"
class UI
{
private:
	Service &service;
	void printDog(Dog dog);
	void printAdoptionMenu(std::vector<Dog> list_of_dogs);
public:
	static bool chooseAdoptionFileType();
	UI(Service &service);
	~UI();
	void startUI();
};
