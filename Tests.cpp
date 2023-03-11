#include "Tests.h"
#include <assert.h>
#include <stdexcept>
#include <fstream>
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>

void Tests::testAll()
{
	//initialize
	std::ofstream create_file("Tests.txt");
	create_file.close();

	FileAdoptionList* file_adoption_list = new HTMLAdoptionList();
	file_adoption_list->setFileName("HTMLTest.txt");

	FileRepository file_repo{ "Tests.txt" };
	Repository& repo{ file_repo };
	Service service{ repo, file_adoption_list, DogValidator() };


	//test CSV
	FileAdoptionList* file_adoption_list_csv = new CSVAdoptionList();
	file_adoption_list_csv->setFileName("CSVTest.txt");
	FileRepository file_repo_csv{ "Tests.txt" };
	Repository& repo_csv{ file_repo_csv };
	Service service_csv{ repo_csv, file_adoption_list_csv, DogValidator() };
	service_csv.addDog("Soricar", "Mura", 6, "http://www.mura.com/imagine.jpg");
	service_csv.adoptDog("Mura");
	Dog dog;
	std::ifstream csv_file("CSVTest.txt");
	csv_file >> dog;
	csv_file.close();
	assert(dog == Dog("Soricar", "Mura", 6, "http://www.mura.com/imagine.jpg"));
	delete file_adoption_list_csv;

	//test load file
	std::ofstream test_file("Tests.txt");
	test_file << Dog("Soricar", "Mura", 6, "http://www.mura.com/imagine.jpg");
	test_file.close();

	FileRepository file_repo2{ "Tests.txt" };
	Repository& repo_2{ file_repo2 };
	Service service_2 = Service(repo_2, file_adoption_list, DogValidator());

	assert(service_2.getDog(0) == Dog("Soricar", "Mura", 6, "http://www.mura.com/imagine.jpg"));
	service_2.deleteDog("Mura");

	//test invalid undo/redo

	try {
		service.redo();
		assert(0);
	}
	catch (RepositoryException&)
	{
		assert(1);
	}

	try {
		service.undo();
		assert(0);
	}
	catch (RepositoryException&)
	{
		assert(1);
	}

	//add a new dog
	service.addDog("Mastiff Tibetan", "Boss", 15, "https://i.ytimg.com/vi/u4GK7ZAh1hY/maxresdefault.jpg");
	assert(service.getDog(0) == Dog("Mastiff Tibetan", "Boss", 15, "https://i.ytimg.com/vi/u4GK7ZAh1hY/maxresdefault.jpg"));

	//add a dog with a name already in the repository
	try {
		service.addDog("Mastiff Tibetan", "Boss", 15, "https://i.ytimg.com/vi/u4GK7ZAh1hY/maxresdefault.jpg");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//delete an existing dog

	service.deleteDog("Boss");
	assert(service.getNrOfDogs() == 0);

	//delete a dog that isn't in the repository
	try {
		service.deleteDog("Boss");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the name of a dog (valid name)

	service.addDog("Mastiff Tibetan", "Boss", 15, "https://i.ytimg.com/vi/u4GK7ZAh1hY/maxresdefault.jpg");
	service.updateDogName("Boss", "Bossulica");
	assert(service.getDog(0).getName() == "Bossulica");


	//update the name of a dog ( invalid name format )
	try {
		service.updateDogName("Bossulica", "boss de boss");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the name of a dog (existing new_name)

	service.addDog("Husky", "Labus", 4, "https://extrucan.ro/wp-content/uploads/2021/08/siberian-husky.jpg");
	try {
		service.updateDogName("Bossulica", "Labus");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}


	//update the name of a dog (name doens't exist)

	try {
		service.updateDogName("Ceva caine", "Ceva");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the breed of a dog (valid dog name)
	service.updateDogBreed("Bossulica", "Dalmatian");
	assert(service.getDog(0).getBreed() == "Dalmatian");

	//update the breed of a dog (invalid dog name)

	try {
		service.updateDogBreed("Ceva caine", "Ceva");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the breed of a dog (invalid breed format)
	try {
		service.updateDogBreed("Bossulica", "of");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the age of a dog (valid dog name)

	service.updateDogAge("Bossulica", 23);
	assert(service.getDog(0).getAge() == 23);

	//update the age of a dog (invalid dog name)

	try {
		service.updateDogAge("Ceva caine", 10);
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update the age of a dog ( invalid age format)
	try {
		service.updateDogAge("Bossulica", -32);
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}
	//update dog photograph (valid dog name)

	service.updateDogPhotograph("Bossulica", "http");
	assert(service.getDog(0).getPhotograph() == "http");

	//update dog photograph (invalid dog name)

	try {
		service.updateDogPhotograph("Ceva caine", "http");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//update dog photograph ( invalid link format )
	try {
		service.updateDogPhotograph("Bossulica", "link");
		assert(0);
	}
	catch (const std::exception&)
	{
		assert(1);
	}

	//test resize for the dynamic vector

	service.addDog("Dalmatian", "Pongo", 10, "https://static.wikia.nocookie.net/disney/images/3/3c/profile_-_pongo.png/revision/latest/scale-to-width-down/605?cb=20200504214003");
	service.addDog("Teckel", "Mura", 6, "https://encrypted-tbn0.gstatic.com/images?q=tbn:and9gcsbkv68g5ga_kc4vpzti2lwfvcy6z46d0_l--ebpjafgab9fqz9q1qv3cg0kmqivwnsmnm&usqp=cau");
	service.addDog("Shiba Inu", "Doge", 11, "https://tradingplatforms.com/ro/wp-content/uploads/sites/36/2021/06/dogecoin-logo.jpg");
	service.addDog("Carpathian Shepherd", "Sasha", 7, "https://upload.wikimedia.org/wikipedia/commons/4/41/carpatin.jpg");
	service.addDog("Golden Retriever", "Poofy", 2, "https://static.posters.cz/image/1300/calendar-golden-retriever-i94891.jpg");
	service.addDog("Rottweiller", "Rocky", 6, "https://www.animalepierdute.ro/wp-content/uploads/2019/09/rottweiler.jpg");
	service.addDog("Saint-Bernand", "Bootus", 8, "https://www.monitoruldegalati.ro/media/k2/items/cache/6977e3569c5e82f8351ef994769758f5_xl.jpg");
	service.addDog("German Shepherd", "Deedee", 5, "https://www.thesprucepets.com/thmb/lndljtiok9mvygn4vlxx0dbyk_i=/1333x1000/smart/filters:no_upscale()/breed_profile_germansheperd_1118000_profile_2608-d7a78e7c1cf049879bec1ec19113ee42.jpg");
	service.addDog("German Shepherd", "BooBoo", 6, "https://www.thesprucepets.com/thmb/lndljtiok9mvygn4vlxx0dbyk_i=/1333x1000/smart/filters:no_upscale()/breed_profile_germansheperd_1118000_profile_2608-d7a78e7c1cf049879bec1ec19113ee42.jpg");
	assert(service.getDog(10).getName() == "BooBoo");

	//test get list of deleted dogs

	assert(service.getListOfDeletedDogs()[0] == Dog("Mastiff Tibetan", "Boss", 15, "https://i.ytimg.com/vi/u4GK7ZAh1hY/maxresdefault.jpg"));

	//test adopt dog + HTML
	service.adoptDog("Doge");
	assert(service.getListOfAdoptedDogs()[0].getName() == "Doge");
	std::ifstream html_file("HTMLTest.txt");
	std::string first_line;
	getline(html_file, first_line);
	assert(first_line == "<!DOCTYPE html><html><head><title><Dog adoption list></title></head><body><table border=\"1\"><tr><td>Breed</td><td>Name</td><td>Age</td><td>Photograph Link</td></tr><tr><td>Shiba Inu</td><td>Doge</td><td>11</td><td><a href=\"https://tradingplatforms.com/ro/wp-content/uploads/sites/36/2021/06/dogecoin-logo.jpg\">Link</a></td></tr></table></body></html>");


	//test get dogs of a given breed ( breed = "-1")
	assert(service.getDogsOfAGivenBreedHavingASpecificAge("-1", 10).size() == 8);

	//test get all dogs
	assert(service.getAllDogs().size() == service.getNrOfDogs());

	//test get dogs of a given breed ( breed != "-1")
	auto list_of_dogs = service.getDogsOfAGivenBreedHavingASpecificAge("German Shepherd", 7);
	assert(list_of_dogs.size() == 2);
	assert(list_of_dogs[1].getName() == "BooBoo");

	//test undo/redo add
	service.addDog("Labrador", "Rex", 6, "http://");
	service.undo();
	assert(service.getNrOfDogs() == 10);
	service.redo();
	assert(service.getNrOfDogs() == 11);
	assert(service.getAllDogs()[service.getNrOfDogs() - 1].getName() == "Rex");

	//test undo/redo remvoe
	service.deleteDog("Rex");
	service.undo();
	assert(service.getNrOfDogs() == 11);
	assert(service.getAllDogs()[service.getNrOfDogs() - 1].getName() == "Rex");
	service.redo();
	assert(service.getNrOfDogs() == 10);
	assert(service.getAllDogs()[service.getNrOfDogs() - 1].getName() == "BooBoo");
	service.undo();

	//test undo/redo update
	service.updateDogBreed("Rex", "Bulldog");
	service.updateDogAge("Rex", 8);
	service.updateDogPhotograph("Rex", "http://jeah.com");
	service.updateDogName("Rex", "Linda");
	service.undo();
	service.undo();
	service.undo();
	service.undo();
	assert(service.getAllDogs()[service.getNrOfDogs() - 1] == Dog("Labrador", "Rex", 6, "http://"));
	service.redo();
	service.redo();
	service.redo();
	service.redo();
	assert(service.getAllDogs()[service.getNrOfDogs() - 1] == Dog("Bulldog", "Linda", 8, "http://jeah.com"));


	remove("Tests.txt");
	delete file_adoption_list;
}