#include "Map.h"
#include "MapIterator.h"
#include <exception>
#include <iostream>

Map::Map() {
	this->nrElements = 0;
	this->capacity = 0;
	this->elements = new TElem[capacity];
}
/// Theta(1)

Map::~Map() {
	delete[] this->elements;
}
/// Theta(1)

TValue Map::add(TKey c, TValue v) {
	for (int i = 0; i < this->nrElements; i++) {
		if (this->elements[i].first == c)
		{
			int old_v = this->elements[i].second;
			this->elements[i].second = v;
			return old_v;
		}
	}
	if (this->nrElements == this->capacity) {
		if (capacity == 0)
		{
			capacity = 1;
		}
		else
		{
			capacity *= 2;
		}
		TElem* newElements = new TElem[capacity];
		for (int i = 0; i < this->nrElements; i++)
			newElements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = newElements;
	}
	TElem elem;
	elem.first = c;
	elem.second = v;
	this->elements[this->nrElements] = elem;
	this->nrElements++;
	 
	return NULL_TVALUE;
}
/// Theta(n)

TValue Map::search(TKey c) const{
	for (int i = 0; i < this->nrElements; i++)
		if (this->elements[i].first == c)
		{
			return this->elements[i].second;
		}
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	for (int i = 0; i < nrElements; i++) {
		if (this->elements[i].first == c) {
			int old_v = this->elements[i].second;
			this->elements[i] = this->elements[nrElements - 1];
			this->nrElements--;
			return old_v;
		}
	}
	return NULL_TVALUE;
}

void Map::filter(Condition condition) {
	MapIterator mi = this->iterator();
	while (mi.valid()) {
		TKey currkey = mi.getCurrent().first;
		if (condition(currkey) == false) {
			this->remove(currkey);
		}
		if (mi.valid())
			mi.next();
	}
}


int Map::size() const {
	return this->nrElements;
}

bool Map::isEmpty() const{
	return this->nrElements == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



