#pragma once

#include <QWidget>
#include "ui_AdoptionListGUI.h"
#include "DogModel.h"

class AdoptionListGUI : public QWidget
{
	Q_OBJECT

public:
	AdoptionListGUI(DogModel* dogModel, QWidget *parent = Q_NULLPTR);
	~AdoptionListGUI();

private:
	Ui::AdoptionListGUI ui;
};
