#pragma once
#include "a11_12.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qcommandlinkbutton.h>
#include "DogService.h"

class TestGui : public QWidget
{
private:
	Service& service;
	QLineEdit* criteriaBox;
	QListWidget* repoList;
	void populateList();
public:
	TestGui(Service& service);
};