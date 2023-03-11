#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "DogService.h"
#include "qmessagebox.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(Service& service, QWidget* parent = Q_NULLPTR);
	~GUI();

private:
	Ui::GUI ui;
	Service& service;
	FileAdoptionList* adoption_list;
	void setAdoptionFile();

public slots:
	void showAdminGUI();
	void showUserGUI();
	void showAdoptionListGUI();
};
