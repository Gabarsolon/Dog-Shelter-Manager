#include "undo.h"

UndoRedoAdd::UndoRedoAdd(Repository& _repository, const Dog& _dog)
	:repository(_repository), addedDog(_dog)
{
}

void UndoRedoAdd::undo()
{
	repository.deleteDog(addedDog.getName());
}

void UndoRedoAdd::redo()
{
	repository.addDog(addedDog);
}

UndoRedoRemove::UndoRedoRemove(Repository& _repository, const Dog& _dog)
	:repository(_repository), removedDog(_dog)
{
}

void UndoRedoRemove::undo()
{
	repository.addDog(removedDog);
}

void UndoRedoRemove::redo()
{
	repository.deleteDog(removedDog.getName());
}

UndoRedoUpdate::UndoRedoUpdate(Repository& _repository, const Dog& _oldDog, const Dog& _newDog)
	:repository(_repository), oldDog(_oldDog), newDog(_newDog)
{
}

void UndoRedoUpdate::undo()
{
	repository.updateDogBreed(newDog.getName(), oldDog.getBreed());
	repository.updateDogAge(newDog.getName(), oldDog.getAge());
	repository.updateDogPhotograph(newDog.getName(), oldDog.getPhotograph());
	if(newDog.getName() != oldDog.getName())
		repository.updateDogName(newDog.getName(), oldDog.getName());
}

void UndoRedoUpdate::redo()
{
	repository.updateDogBreed(oldDog.getName(), newDog.getBreed());
	repository.updateDogAge(oldDog.getName(), newDog.getAge());
	repository.updateDogPhotograph(oldDog.getName(), newDog.getPhotograph());
	if (newDog.getName() != oldDog.getName())
		repository.updateDogName(oldDog.getName(), newDog.getName());
}
