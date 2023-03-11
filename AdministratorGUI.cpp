#include "AdministratorGUI.h"
#include <sstream>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QChart.h>
#include <QtCharts/QPieSeries.h>
#include <QtCharts/QBarSeries.h>
#include <QtCharts/QBarSet.h>
#include <QtCharts/QBarCategoryAxis.h>
#include <QtCharts/QValueAxis.h>
#include <QStringList>
#include <qshortcut.h>



AdministratorGUI::AdministratorGUI(Service& service, QWidget* parent )
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
	ui.dogsListWidget->setStyleSheet(QString("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:0, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
	QShortcut * undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y),  this);
	QObject::connect(undoShortcut, &QShortcut::activated, this, &AdministratorGUI::undo);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &AdministratorGUI::redo);
	populateList();
}

AdministratorGUI::~AdministratorGUI()
{
}

void AdministratorGUI::addDog()
{
	std::string breed = ui.breedLineEdit->text().toStdString();
	std::string name = ui.nameLineEdit->text().toStdString();
	int age = ui.ageLineEdit->text().toInt();
	std::string photograph = ui.linkLineEdit->text().toStdString();

	try {
		service.addDog(breed, name, age, photograph);
		populateList();
	}
	catch (DogException& exception)
	{
		QMessageBox* errorBox = new QMessageBox{};
		errorBox->setText(exception.what());
		errorBox->setWindowTitle("Invalid dog data");
		errorBox->setIcon(QMessageBox::Critical);
		errorBox->exec();
	}
	catch (RepositoryException& exception)
	{
		QMessageBox* errorBox = new QMessageBox{};
		errorBox->setWindowTitle("Error adding the dog");
		errorBox->setIcon(QMessageBox::Critical);
		errorBox->setText(exception.what());
		errorBox->exec();
	}
}

void AdministratorGUI::populateList()
{
	ui.dogsListWidget->clear();
	for (const auto& dog : service.getAllDogs())
	{
		std::stringstream dog_string;
		dog_string << dog;
		ui.dogsListWidget->addItem(QString::fromStdString(dog_string.str()));
	}

}

void AdministratorGUI::removeDog()
{
	std::string name = ui.nameLineEdit->text().toStdString();

	try {
		service.deleteDog(name);
		populateList();
	}
	catch (RepositoryException& exception)
	{
		QMessageBox* errorBox = new QMessageBox{};
		errorBox->setWindowTitle("Error adding the dog");
		errorBox->setIcon(QMessageBox::Critical);
		errorBox->setText(exception.what());
		errorBox->exec();
	}
}

void AdministratorGUI::updateDog()
{
	std::string new_breed = ui.breedLineEdit->text().toStdString();
	std::string new_name = ui.nameLineEdit->text().toStdString();
	int new_age = ui.ageLineEdit->text().toInt();
	std::string new_photograph = ui.linkLineEdit->text().toStdString();
	try {
		auto selectedIndex = ui.dogsListWidget->selectionModel()->selectedIndexes();
		if (!selectedIndex.isEmpty())
		{
			int index = selectedIndex.at(0).row();
			Dog selectedDog = service.getDog(index);
			std::string currentName = selectedDog.getName();
			if (currentName != new_name)
				service.updateDogName(currentName, new_name);
			if (selectedDog.getBreed() != new_breed)
				service.updateDogBreed(currentName, new_breed);
			if (selectedDog.getAge() != new_age)
				service.updateDogAge(currentName, new_age);
			if (selectedDog.getPhotograph() != new_photograph)
				service.updateDogPhotograph(currentName, new_photograph);
			populateList();
		}
		else
		{
			QMessageBox* errorBox = new QMessageBox{};
			errorBox->setText("You must select a dog");
			errorBox->setWindowTitle("Error updating the dog");
			errorBox->setIcon(QMessageBox::Critical);
			errorBox->exec();
		}
			
	}
	catch (DogException& exception)
	{
		QMessageBox* errorBox = new QMessageBox{};
		errorBox->setText(exception.what());
		errorBox->setWindowTitle("Invalid dog data");
		errorBox->setIcon(QMessageBox::Critical);
		errorBox->exec();
	}
	catch (RepositoryException& exception)
	{
		QMessageBox* errorBox = new QMessageBox{};
		errorBox->setWindowTitle("Error updating the dog");
		errorBox->setIcon(QMessageBox::Critical);
		errorBox->setText(exception.what());
		errorBox->exec();
	}
}

void AdministratorGUI::updateDogLineEdits()
{
	auto selectedIndex = ui.dogsListWidget->selectionModel()->selectedIndexes();
	if (!selectedIndex.isEmpty())
	{
		int index = selectedIndex.at(0).row();
		auto dog = service.getDog(index);
		
		ui.breedLineEdit->setText(QString::fromStdString(dog.getBreed()));
		ui.nameLineEdit->setText(QString::fromStdString(dog.getName()));
		ui.ageLineEdit->setText(QString::fromStdString(std::to_string(dog.getAge())));
		ui.linkLineEdit->setText(QString::fromStdString(dog.getPhotograph()));
	}
}

void AdministratorGUI::displayChart()
{
	std::vector<std::string> breeds = service.getDogBreeds();
	auto* chart = new QChart();
	int maximumNrOfDogsHavingTheSameBreed = 0;
	for (auto breed : breeds)
	{
		auto* barSeries = new QBarSeries{};
		auto* currentSet = new QBarSet(QString::fromStdString(breed));
		int currentNrOfDogs = service.getDogsOfAGivenBreedHavingASpecificAge(breed, -1).size();
		*currentSet << currentNrOfDogs;
		barSeries->append(currentSet);
		barSeries->setLabelsVisible(true);
		barSeries->labelsPosition();
		chart->addSeries(barSeries);
		if (currentNrOfDogs > maximumNrOfDogsHavingTheSameBreed)
			maximumNrOfDogsHavingTheSameBreed = currentNrOfDogs;
	}

	QStringList axisXStrings;
	for (auto breed : breeds)
		axisXStrings << QString::fromStdString(breed);

	auto* axisX = new QBarCategoryAxis();
	axisX->setLabelsVisible(true);
	axisX->append(axisXStrings);

	auto* axisY = new QValueAxis();
	axisY->setLabelsVisible(true);
	axisY->setMin(0);
	axisY->setMax(maximumNrOfDogsHavingTheSameBreed);
	axisY->setTitleText("Number of dogs");

	chart->createDefaultAxes();
	chart->legend()->hide();
	chart->setAxisX(axisX);
	chart->setAxisY(axisY);

	auto* chartView = new QChartView{};
	chartView->setChart(chart);

	auto* chartLayout = new QVBoxLayout{};
	auto* chartWidget = new QWidget{};
	chartLayout->addWidget(chartView);
	chartView->show();
}

void AdministratorGUI::undo()
{
	try
	{
		service.undo();
		populateList();
	}
	catch (RepositoryException& exception)
	{
		auto error_message = new QMessageBox{};
		error_message->setText(exception.what());
		error_message->setIcon(QMessageBox::Critical);
		error_message->exec();
	}
}

void AdministratorGUI::redo()
{
	try
	{
		service.redo();
		populateList();
	}
	catch (RepositoryException& exception)
	{
		auto error_message = new QMessageBox{};
		error_message->setText(exception.what());
		error_message->setIcon(QMessageBox::Critical);
		error_message->exec();
	}
}

//void AdministratorGUI::displayChart()
//{
//	std::vector<std::string> breeds = service.getDogBreeds();
//	auto* chart = new QChart();
//	auto* pieSeries = new QPieSeries();
//	for (auto breed : breeds)
//	{
//		int currentNrOfDogs = service.getDogsOfAGivenBreedHavingASpecificAge(breed, -1).size();
//		pieSeries->append(QString::fromStdString(breed + ": " + std::to_string(currentNrOfDogs)), currentNrOfDogs);
//		//pieSeries->slices().back()->setLabel(QString::fromStdString(std::to_string(service.getDogsOfAGivenBreedHavingASpecificAge(breed, -1).size())));
//		pieSeries->setLabelsVisible(true);
//	}
//	chart->addSeries(pieSeries);
//
//	chart->legend()->setAlignment(Qt::AlignBottom);
//	auto* chartView = new QChartView{};
//	chartView->setChart(chart);
//
//	auto* chartLayout = new QHBoxLayout{};
//	auto* chartWidget = new QWidget{};
//	chartLayout->addWidget(chartView);
//	chartWidget->setLayout(chartLayout);
//	
//	chartWidget->show();
//}