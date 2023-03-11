#pragma once

#include <QWidget>
#include "ui_UserGUI.h"
#include "DogService.h"

class UserGUI : public QWidget
{
	Q_OBJECT

public:
	UserGUI(Service& service, QWidget* parent = Q_NULLPTR);
	~UserGUI();

private:
	Service& service;
	int currentIndex;
	std::vector<Dog> dogList;
	Ui::UserGUI ui;

public slots:
	void seeAllDogs();
	void next();
	void adoptDog();
	void seeDogsByBreedAndAge();
	void seeAdoptionList();
	void seePhoto();
};
