#pragma once

#include <QWidget>
#include "ui_AdministratorGUI.h"
#include "DogService.h"



class AdministratorGUI : public QWidget
{
	Q_OBJECT

public:
	AdministratorGUI(Service& service, QWidget* parent = Q_NULLPTR );
	~AdministratorGUI();

private:
	Service& service;
	void populateList();
	Ui::AdministratorGUI ui;

public slots:
	void addDog();
	void removeDog();
	void updateDog();
	void updateDogLineEdits();
	void displayChart();
	void undo();
	void redo();
};
