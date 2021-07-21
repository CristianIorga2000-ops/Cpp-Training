#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//O(n)
void MultiMap::resize()
{
	//Calculate new capacity
	capacity = (capacity + 1) * 2;
	//Create new arrays with extended capacity
	Link* newLinks = new Link[capacity];
	State* newState = new State[capacity];
	//Set all slots in newState to free
	memset(newState, static_cast<int>(State::Free), capacity);
	//Set first empty slot 
	//Copy form old arrays to new arrays
	for (int i = 0; i < nrElem; i++)
	{
		newState[i] = state[i];
		newLinks[i] = links[i];
	}
	//Delete old arrays
	delete[] links;
	delete[] state;
	//Point to new arrays
	links = newLinks;
	state = newState;
}

//O(n)
void MultiMap::findEmpty()
{
	for (int i = 0; i < capacity; i++)
		if (state[i] != State::Occupied)
		{
			firstEmpty = i;
			break;
		}
}

//Theta(1)
void MultiMap::chain(int indexPreviousLink, int indexNextLink)
{
	//If any of the indexes is out of bounds, throw an exception
	if (indexPreviousLink == -1 or indexNextLink == -1)
		throw exception("MultiMap::chain(...): Attempted chain with out of bounds indexes");

	//If any of the indexes points to a slot without a valid Link, throw an exception
	if (state[indexPreviousLink] != State::Occupied || state[indexNextLink] != State::Occupied)
		throw exception("MultiMap::chain(...): Attempted chain with unexisting links");

	//Chain the two links (head <-> ... <-> previousLink <<=>> nextLink <-> ... <-> tail)
	//	by making them point to eachother
	links[indexPreviousLink].next = indexNextLink;
	links[indexNextLink].prev = indexPreviousLink;
}

//O(1)
MultiMap::MultiMap()
	:links{ NULL }
	, state{ NULL }
	, capacity{ 0 }
	, head{ -1 }
	, firstEmpty{ 0 }
	, tail{ -1 }
	, nrElem{ 0 }
{}

//O(n)
//Theta(1) for most of the times
void MultiMap::add(TKey c, TValue v) {
	//Resize if there is no more space in array for adding a new element
	if (nrElem >= capacity)
		resize();
	//If firstEmpty points to occupied/ invalid slot in array, recalculate it
	if (firstEmpty >= capacity || state[firstEmpty] == State::Occupied)
		findEmpty();
	//Create new link
	Link linkToAdd{ {c, v}, -1, -1 };
	//Bind new link to firstEmpty position
	links[firstEmpty] = linkToAdd;
	//Mark this array slot as occupied
	state[firstEmpty] = State::Occupied;
	//If there is a tail (linkToAdd is NOT the first element in the array)
	if (tail != -1)
		//Chain tail and linkToAdd
		chain(tail, firstEmpty);
	//If there is no tail(linkToAdd is FIRST ELEMENT)
	else
		head = firstEmpty;
	//Make linkToAdd the new tail
	tail = firstEmpty;
	//Number of element is incremented
	nrElem++;
	//There is no point for firstEmpty to point to an occupied array slot and force
	//	a call of the findEmpty() function with O(n) complexity.
	//If incremented, it is guaranteed to point to an empty slot if no deletes have  been done
	firstEmpty++;
}

//O(n)
bool MultiMap::remove(TKey c, TValue v) {
	int i = head;
	while (i != -1)
	{
		TKey currentKey = links[i].data.first;
		TValue currentValue = links[i].data.second;
		//If element was found
		if (currentKey == c && currentValue == v)
		{
			//Mark array slot as free
			state[i] = State::Free;
			//Find neighbours
			int previousLink = links[i].prev;
			int nextLink = links[i].next;
			//If we are deleting the last element
			if (nrElem == 1)
			{
				head = -1;
				tail = -1;
			}
			//If only previousLink is -1, we are deleting the head
			else if (previousLink == -1)
			{
				//We set the second element as the head
				head = nextLink;
				links[nextLink].prev = -1;
			}
			//If nextLink is -1, we are deleting the tail
			else if (nextLink == -1)
			{
				//We set the penultimate element as the tail
				tail = previousLink;
				links[previousLink].next = -1;
			}
			//If we are deleting an element from the middle
			else
				//Chain together previousLink and nextLink
				chain(previousLink, nextLink);
			//Size decrement
			nrElem--;
			//Return true for successsful delete
			return true;
		}
		i = links[i].next;
	}
	return  false;
}

//O(n)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> foundValues;
	int i = head;
	while (i != -1)
	{
		TKey currentKey = links[i].data.first;
		TValue currentValue = links[i].data.second;
		//If we have found the key
		if (currentKey == c)
			//Add value to foundValues vector
			foundValues.push_back(currentValue);
		i = links[i].next;
	}
	return foundValues;
}

//Theta(1)
int MultiMap::size() const {
	return nrElem;
}

//Theta(1)
bool MultiMap::isEmpty() const {
	return nrElem == 0;
}

//Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//Theta(1)
MultiMap::State* MultiMap::getState()
{
	return state;
}

//Theta(1)
MultiMap::~MultiMap() {
	//Delete all pointers, use [] for arrays
	delete[] links;
	delete[] state;
}

