#pragma once
#include "DogRepository.h"
class UndoRedoAction
{
public:
	virtual void undo() = 0;
	virtual void redo() = 0;
	virtual ~UndoRedoAction(){};
};

class UndoRedoAdd : public UndoRedoAction
{
private:
	Dog addedDog;
	Repository& repository;
public:
	UndoRedoAdd(Repository& _repository, const Dog& _dog);
	void undo();
	void redo();
};

class UndoRedoRemove : public UndoRedoAction
{
private:
	Dog removedDog;
	Repository& repository;
public:
	UndoRedoRemove(Repository& _repository, const Dog& _dog);
	void undo();
	void redo();
};

class UndoRedoUpdate : public UndoRedoAction
{
private:
	Dog oldDog, newDog;
	Repository& repository;
public:
	UndoRedoUpdate(Repository& _repository, const Dog& _oldDog, const Dog& _newDog);
	void undo();
	void redo();
};