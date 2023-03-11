#include "UserGUI.h"
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <Windows.h>
#include <QtNetwork/QNetworkAccessManager>


UserGUI::UserGUI(Service& service, QWidget* parent)
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
}

UserGUI::~UserGUI()
{
}

void UserGUI::seeAllDogs()
{
	dogList = service.getAllDogs();
	currentIndex = -1;
	next();
}

void UserGUI::next()
{
	if (dogList.size() == 0)
	{
		ui.breedLineEdit->clear();
		ui.nameLineEdit->clear();
		ui.ageLineEdit->clear();
		ui.linkLineEdit->clear();
		auto errorBox = new QMessageBox{};
		errorBox->setText("No more dogs to show");
		errorBox->setIcon(QMessageBox::Warning);
		errorBox->exec();
	}
	else {
		currentIndex++;
		if (currentIndex >= dogList.size())
			currentIndex = 0;
		Dog currentDog = dogList[currentIndex];
		ui.breedLineEdit->setText(QString::fromStdString(currentDog.getBreed()));
		ui.nameLineEdit->setText(QString::fromStdString(currentDog.getName()));
		ui.ageLineEdit->setText(QString::fromStdString(std::to_string(currentDog.getAge())));
		ui.linkLineEdit->setText(QString::fromStdString(currentDog.getPhotograph()));
	}
}

void UserGUI::adoptDog()
{
	if (dogList.size() == 0)
	{
		auto errorBox = new QMessageBox{};
		errorBox->setText("There isn't any dog to adopt");
		errorBox->setIcon(QMessageBox::Warning);
		errorBox->exec();
	}
	else {
		service.adoptDog(dogList[currentIndex].getName());
		dogList.erase(dogList.begin() + currentIndex);
		currentIndex--;
		next();
		auto infoBox = new QMessageBox{};
		infoBox->setText("Dog adopted successfully");
		infoBox->setIcon(QMessageBox::Warning);
		infoBox->exec();
	}
}

void UserGUI::seeDogsByBreedAndAge()
{
	std::string breed = ui.specificBreedLineEdit->text().toStdString();
	int age = ui.specificAgeLineEdit->text().toInt();
	dogList = service.getDogsOfAGivenBreedHavingASpecificAge(breed, age);
	currentIndex = -1;
	next();
}

void UserGUI::seeAdoptionList()
{
	service.displayAdoptionList();
}

void UserGUI::seePhoto()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", ui.linkLineEdit->text().toStdString().c_str(), NULL, SW_SHOWMAXIMIZED);
}
