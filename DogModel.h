#pragma once
#include <QAbstractTableModel>
#include "FileAdoptionList.h"
class DogModel : public QAbstractTableModel
{
private:
	FileAdoptionList* adoptionList;
public:
	DogModel(FileAdoptionList* _adoptionList);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


};

