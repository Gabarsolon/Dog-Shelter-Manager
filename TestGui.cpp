#include "TestGui.h"
#include <sstream>
#include<string>

void TestGui::populateList()
{
	repoList->clear();
	std::string criteria = criteriaBox->text().toStdString();
	for (auto dog : service.getAllDogs())
	{
		std::stringstream ss;
		ss << dog;
		std::string dog_string = ss.str();

		if(dog_string.find(criteria) != std::string::npos)
			repoList->addItem(QString::fromStdString(ss.str()));
	}
}

TestGui::TestGui(Service& service)
	:service(service)
{
	criteriaBox = new QLineEdit{};
	repoList = new QListWidget{};
	auto* layout = new QVBoxLayout{};

	layout->addWidget(criteriaBox);
	layout->addWidget(repoList);

	this->setLayout(layout);
	this->populateList();

	QObject::connect(criteriaBox, &QLineEdit::textChanged, this, &TestGui::populateList);

}
