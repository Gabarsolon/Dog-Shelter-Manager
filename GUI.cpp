#include "GUI.h"
#include "AdministratorGUI.h"
#include "UserGUI.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include "AdoptionListGUI.h"
#include "DogModel.h"

GUI::GUI(Service& service, QWidget* parent)
	: QWidget(parent), service(service), adoption_list(nullptr)
{
	ui.setupUi(this);
}

GUI::~GUI()
{
}

void GUI::setAdoptionFile()
{	
	if (adoption_list != nullptr)
		delete adoption_list;
	if (ui.CSVradioButton->isChecked())
	{
		adoption_list = new CSVAdoptionList{};
		adoption_list->setFileName("DogAdoptionList.csv");
		service.setFileAdoptionList(adoption_list);
	}
	else
	{
		adoption_list = new HTMLAdoptionList{};
		adoption_list->setFileName("DogAdoptionList.html");
		service.setFileAdoptionList(adoption_list);
	}
}

void GUI::showUserGUI()
{
	setAdoptionFile();
	UserGUI* userGUI = new UserGUI{service};
	//this->hide();
	userGUI->show();
}

void GUI::showAdoptionListGUI()
{
	if (adoption_list == nullptr)
	{
		auto error_message = new QMessageBox{};
		error_message->setText("You must adopt some dogs first");
		error_message->setIcon(QMessageBox::Critical);
		error_message->exec();
	}
	else {
		DogModel* dogModel = new DogModel{ service.getFileAdoptionList() };
		AdoptionListGUI* adoptionListGui = new AdoptionListGUI{ dogModel };
		adoptionListGui->show();
	}
	
}

void GUI::showAdminGUI()
{
	AdministratorGUI* administratorGUI = new AdministratorGUI{service};
	//this->hide();
	administratorGUI->show();
}