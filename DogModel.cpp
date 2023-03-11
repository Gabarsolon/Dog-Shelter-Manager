#include "DogModel.h"

DogModel::DogModel(FileAdoptionList* _adoptionList)
	:adoptionList(_adoptionList)
{
}

int DogModel::rowCount(const QModelIndex& parent) const
{
	return adoptionList->getUserAdoptionList().size();
}

int DogModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant DogModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Dog dog = adoptionList->getUserAdoptionList()[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(dog.getBreed());
		case 1:
			return QString::fromStdString(dog.getName());
		case 2:
			return QString::number(dog.getAge());
		case 3:
			return QString::fromStdString(dog.getPhotograph());
		default:
			break;
		}
	}

	return QVariant();
}

QVariant DogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			switch (section)
			{
			case 0:
				return QString("Breed");
			case 1:
				return QString("Name");
			case 2:
				return QString("Age");
			case 3:
				return QString("Photograph");
			default:
				break;
			}
		}
	}

	return QVariant();
}
