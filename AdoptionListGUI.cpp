#include "AdoptionListGUI.h"
#include <QSortFilterProxyModel>

AdoptionListGUI::AdoptionListGUI(DogModel* dogModel, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
	proxyModel->setSourceModel(dogModel);
	proxyModel->setSortRole(Qt::UserRole);
	ui.dogAdoptionListTableView->setModel(proxyModel);
	ui.dogAdoptionListTableView->setSortingEnabled(true);
}

AdoptionListGUI::~AdoptionListGUI()
{
}
