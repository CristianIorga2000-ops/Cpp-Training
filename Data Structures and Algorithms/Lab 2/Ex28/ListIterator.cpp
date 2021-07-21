#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->currentPosition = list.firstLink;
}

ListIterator::ListIterator(const SortedIteratedList& list, Link* newCurrentPosition) : list(list) {
	this->currentPosition = newCurrentPosition;
}

void ListIterator::first(){
	this->currentPosition = list.firstLink;
}

void ListIterator::next(){
	if (this->currentPosition == NULL)
		throw exception("ListIterator::next() -> No next node.");
	this->currentPosition = this->currentPosition->next;
}

bool ListIterator::valid() const{
	return this->currentPosition != NULL;
}

TComp ListIterator::getCurrent() const{
	if (this->currentPosition == NULL)
		throw exception("ListIterator::gerCurrent() -> No current node.");
	return this->currentPosition->data;
}


