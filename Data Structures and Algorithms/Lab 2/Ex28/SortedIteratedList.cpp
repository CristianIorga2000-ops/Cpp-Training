#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->firstLink = NULL;
	this->relation = r;
	this->listSize = 0;
}

int SortedIteratedList::size() const {
	return this->listSize;
}

bool SortedIteratedList::isEmpty() const {
	return this->listSize == 0;
}

ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (poz.currentPosition == NULL)
		throw exception("SortedIteratedList::remove(...) NULL address as parameter");
	Link* linkToDelete = poz.currentPosition;
	TComp returnValue = linkToDelete->data;
	Link* previousLink = this->firstLink;

	//Search for the link behind the link we want to delete
	while (previousLink != NULL && previousLink->next != linkToDelete)
		previousLink = previousLink->next;

	//If previousLink is NULL, then linkToDelete is the first link.
	if (previousLink != NULL)
		previousLink->next = linkToDelete->next;

	else // linkToDelete is actually first link
		this->firstLink = linkToDelete->next;

	poz.next();

	delete linkToDelete;
	this->listSize--;

	return returnValue;
}

ListIterator SortedIteratedList::search(TComp e) const {
	Link* currentLink = this->firstLink;
	while (currentLink != NULL)
	{
		if (currentLink->data == e)
			return ListIterator(*this, currentLink);
		currentLink = currentLink->next;
	}
	return ListIterator(*this, NULL);
}

void SortedIteratedList::add(TComp e) {
	Link* linkToAdd = new Link{ e, NULL };

	//If there is at least one element in the list

	Link* previousLink = NULL;
	Link* currentLink = this->firstLink;

	//We search for the first element that is greater than the element we wish to add.
	//When such an element is found, we usually have the following relation true:
	//	relation(e, previousLink->data) == false AND
	//	relation(e, currentLink->data) == true.
	//In other words,
	//	previousLink < linkToAdd < currentLink
	while (currentLink != NULL && this->relation(e, currentLink->data) != true)
	{
		previousLink = currentLink;
		currentLink = currentLink->next;
	}

	//If currentLink is NULL then linkToAdd is the last element in the list.
	if (currentLink != NULL)
		linkToAdd->next = currentLink;

	//If previousLink is NULL then linkToAdd is the first element in the list.
	if (previousLink != NULL)
		previousLink->next = linkToAdd;

	else
		this->firstLink = linkToAdd;

	//Note that currentLink and previousLink CANNOT be simultaneously NULL.

	//An element will have been added invariably.
	this->listSize++;
}

SortedIteratedList::~SortedIteratedList() {
	Link* currentLink = this->firstLink;
	Link* linkToDelete;

	while (currentLink != NULL) {
		linkToDelete = currentLink;
		currentLink = currentLink->next;
		delete linkToDelete;
	}

	delete currentLink;
}
