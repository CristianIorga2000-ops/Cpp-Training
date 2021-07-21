#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <cmath>

MultiMap::MultiMap()
	: elements{ nullptr }
	, state{ nullptr }
	, maxSize{ 0 }
	, currentSize{ 0 }
{}

MultiMap::~MultiMap() {
	delete[] elements;
	delete[] state;
}

void MultiMap::add(TKey c, TValue v) {
	//Resize table if needed
	if (isOverloaded()) resizeHashTable();
	//Calculate hash values for key
	int h1 = hash1(c, maxSize);
	int h2 = hash2(c, maxSize);

	for (int i = 0; true; i++) {
		//Calculate position in hash table
		int h = (h1 + i * h2) % maxSize;
		//If that position in the array is NOT occupied:
		if (state[h] != State::Occupied) {
			//Build new HashEntry
			TValue* newValueArray = new TValue[1];
			HashEntry newHashEntry{ c, Array{0, 1, newValueArray } };
			//Assign the slot h in the hash table to this hash entry 
			elements[h] = newHashEntry;
			//Add value to hash entry`s dynamic array of values
			addToArray(h, v);
			//Mark that position as occupied
			state[h] = State::Occupied;
			break;
		}
		//If that position IS occupied BUT it has the corresponding key
		//	we add the value to the associated array of values
		else if (elements[h].key == c) {
			addToArray(h, v);
			break;
		}
	}
}

bool MultiMap::remove(TKey c, TValue v) {
	//If we have no elements, we cannot remove anything
	if (currentSize == 0) return false;
	//Calculate hash values for key 
	int h1 = hash1(c, maxSize);
	int h2 = hash2(c, maxSize);

	for (int i = 0; true; i++) {
		//Calculate position in hash table
		int h = (h1 + i * h2) % maxSize;
		//If the position in the hashtable is NOT occupied, there is no such element
		//	return false for unsuccessful delete
		if (state[h] == State::Vacant) return false;
		//If we have an element with key = c at this position
		if (state[h] == State::Occupied && elements[h].key == c) {
			return deleteFromArray(h, v);
		}
	}
}

vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> valuesForKey;

	//If we have no elements, return the empty vector
	if (currentSize == 0) return valuesForKey;
	//Calculate hash values for this key
	int h1 = hash1(c, maxSize);
	int h2 = hash2(c, maxSize);
	for (int i = 0; true; i++) {
		//calculate position in hash table
		int h = (h1 + i * h2) % maxSize;
		//If there is no element at that position, there are no values to be found
		//	return the empty vector
		if (state[h] == State::Vacant) return valuesForKey;
		//If there is an element at that position with key=c, 
		//	put associated his values in the vector
		if (state[h] == State::Occupied && elements[h].key == c)
		{
			for (int j = 0; j < elements[h].array.size; j++)
			{
				TValue v = elements[h].array.values[j];
				valuesForKey.push_back(v); // This is where the execution stops
			}
			//Return the vector with elements
			return valuesForKey;
		}
	}
}

int MultiMap::size() const {
	return currentSize;
}

bool MultiMap::isEmpty() const {
	return currentSize == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

int MultiMap::hash1(TKey key, int capacity) {
	return abs(key) % (capacity);
}

int MultiMap::hash2(TKey key, int capacity) {
	return 1 + abs(key) % (capacity - 1);
}

bool MultiMap::isOverloaded() const {
	if (maxSize == 0) return true;

	return getLoadFactor() >= HASH_LOAD_FACTOR;
}

float MultiMap::getLoadFactor() const {
	return (float)currentSize / (float)maxSize;
}

int MultiMap::getNewSize() const {
	//Get the next prime number bigger or equal than
	//	the current maxSize*2+1
	if (maxSize == 0) return 3;

	for (int i = maxSize * 2 + 1; true; i += 2) {
		bool isPrime = true;

		for (int k = 3; k * k <= i; k += 2)
			if (i % k == 0) {
				isPrime = false; break;
			}
		if (isPrime) return i;
	}
}

void MultiMap::resizeHashTable() {
	//Get the new size and build the new hash table and state
	int newMaxSize = getNewSize();
	HashEntry* newElements = new HashEntry[newMaxSize];
	State* newState = new State[newMaxSize];
	//Set all positions to be vacant
	memset(newState, static_cast<int>(State::Vacant), newMaxSize);

	for (int i = 0; i < maxSize; i++) {
		//If this position is occupied
		if (state[i] == State::Occupied) {
			//Calculate it`s hash values according to the newMaxSize
			int h1 = hash1(elements[i].key, newMaxSize);
			int h2 = hash2(elements[i].key, newMaxSize);

			for (int j = 0; true; j++) {
				//Calculate the position of the element in the new hash table
				int h = abs((h1 + j * h2) % newMaxSize);
				//If this position is vacant in the new hash entry
				if (newState[h] == State::Vacant) {
					//Make this position point to the current hash entry
					newElements[h] = elements[i];
					//Mark this position as occupied
					newState[h] = State::Occupied;
					break;
				}
			}
		}
	}
	//Delete the old hash table and state
	delete[] elements;
	delete[] state;

	//Point to new hash table, state and maxSize
	elements = newElements;
	state = newState;
	maxSize = newMaxSize;
}

void MultiMap::addToArray(int positionInHashTable, TValue val)
{
	elements[positionInHashTable];
	Array* currentArray = &elements[positionInHashTable].array;
	//If array is full, resize it
	if (currentArray->size >= currentArray->capacity) resizeArray(positionInHashTable);
	//Add the value to the array
	currentArray->values[currentArray->size] = val;
	//Increment array size
	currentArray->size++;
	//Increment overall size
	currentSize++;
}

bool MultiMap::deleteFromArray(int positionInHashTable, TValue val)
{
	Array* currentArray = &elements[positionInHashTable].array;
	bool valueFound = false;
	int i;
	for (i = 0; i < currentArray->size; i++) {
		//If we have found the element
		if (currentArray->values[i] == val) {
			valueFound = true;
			break;
		}
	}
	//Move all the elements from the next position to the end
	//	one position to the left
	for (i++; i < currentArray->size; i++)
		currentArray->values[i - 1] = currentArray->values[i];
	//If we have found (and therefore deleted) an element
	if (valueFound) {
		//Decrement array size
		currentArray->size--;
		//Decrement overall size
		currentSize--;
		//If the array is empty, mark this position in the hash table
		//	as deleted
		if (currentArray->size == 0)
			state[positionInHashTable] = State::Deleted;
	}
	return valueFound;
}

void MultiMap::resizeArray(int positionInHashTable)
{
	Array* currentArray = &elements[positionInHashTable].array;
	//Calculate new capacity
	int newArrayCapacity = (currentArray->capacity + 1) * 2;
	//Create new value array
	TValue* newValueArray = new TValue[newArrayCapacity];
	//Copy elements from old value array to new value array
	for (int i = 0; i < currentArray->size; i++)
		newValueArray[i] = currentArray->values[i];
	//Delete old value array
	delete[] currentArray->values;
	//Point to new value array
	currentArray->values = newValueArray;
	//Update capacity;
	currentArray->capacity = newArrayCapacity;
}
