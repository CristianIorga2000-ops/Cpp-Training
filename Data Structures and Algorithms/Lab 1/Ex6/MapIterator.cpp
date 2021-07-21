#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	this->current = 0;
}
///Theta(1)

void MapIterator::first() {
	this->current = 0;
}
///Theta(1)

void MapIterator::next() {
	if (this->current >= this->map.nrElements) throw exception();
	else this->current++;
}
/// Theta(1)

TElem MapIterator::getCurrent(){
	if (this->current >= this->map.nrElements) throw exception();
	return this->map.elements[this->current];
	return NULL_TELEM;
}


bool MapIterator::valid() const {
	if (this->current < this->map.nrElements) return true;
	return false;
}



