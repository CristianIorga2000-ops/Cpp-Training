#include "MultiMapIterator.h"
#include "MultiMap.h"

MultiMapIterator::MultiMapIterator(const MultiMap& c)
	: col(c)
	, currentPosition{ col.head } 
{}

TElem MultiMapIterator::getCurrent() const {
	if (currentPosition == -1)
		throw exception("MultiMapIterator::getCurrent(): index out of bounds");
	return col.links[currentPosition].data;
}

bool MultiMapIterator::valid() const {
	return currentPosition != -1;
}

void MultiMapIterator::next() {
	if (currentPosition == -1)
		throw exception("MultiMapIterator::next(): invalid next call");
	currentPosition = col.links[currentPosition].next;
}

void MultiMapIterator::first() {
	currentPosition = col.head;
}

