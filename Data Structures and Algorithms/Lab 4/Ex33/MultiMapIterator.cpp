#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

bool MultiMapIterator::validIndexArray()
{
	MultiMap::Array currentArray = iteratedMultiMap.elements[indexHashMap].array;
	return indexArray < currentArray.size-1;
}

MultiMapIterator::MultiMapIterator(const MultiMap& c)
	: iteratedMultiMap(c)
	, indexHashMap{ 0 }
	, indexArray{ 0 } {
	//Set indexHashMap to index of first occupied position in hashtable 
	for (; indexHashMap < iteratedMultiMap.maxSize; indexHashMap++) {
		if (iteratedMultiMap.state[indexHashMap] == MultiMap::State::Occupied)
			break;
	}
}

TElem MultiMapIterator::getCurrent() const {
	//If indexHashEntry is invalid, throw an error
	if (!valid()) throw exception("MultiMapIterator::getCurrent(): Invalid index");
	//If current position in hashtable does not have a hash entry, throw an error
	MultiMap::HashEntry currentHashEntry = iteratedMultiMap.elements[indexHashMap];
	TKey currentKey = currentHashEntry.key;
	TValue currentValue = currentHashEntry.array.values[indexArray];
	return TElem{ currentKey, currentValue };
}

bool MultiMapIterator::valid() const {
	return iteratedMultiMap.currentSize != 0 
		&& indexHashMap < iteratedMultiMap.maxSize;
}

void MultiMapIterator::next() {
	if (!valid()) throw exception("Failed iterator next() call");
	//If indexArray is invalid it means we have iterated trough the whole valueArray
	if (!validIndexArray()) {
		indexArray = 0;
		//We move to the next hashtable entry
		indexHashMap++;
		while (iteratedMultiMap.state[indexHashMap] != MultiMap::State::Occupied)
			indexHashMap++;
	}
	//If indexArray is valid we simply move to the next element in the valueArray
	else indexArray++;
}

void MultiMapIterator::first() {
	for (indexHashMap = 0; indexHashMap < iteratedMultiMap.maxSize; indexHashMap++)
		if (iteratedMultiMap.state[indexHashMap] == MultiMap::State::Occupied)
			break;
}

