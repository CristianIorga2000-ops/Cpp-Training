#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
#define INVALID_INTEGER -111111
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	struct Link {
		TElem data;
		int prev=-1;
		int next=-1;
	};

	enum class State {
		Free,
		Occupied,
	};

	Link* links;
	State* state;
	int capacity;
	int head;
	int tail;
	int firstEmpty;
	int nrElem;

	//resize links and state arrays
	void resize();
	//find an empty place in the array
	void findEmpty();
	//chain two links, received as parameters by their index in the array
	void chain(int indexPreviousLink, int indexNextLink);

public:
	//constructor
	MultiMap();

	//acces to the State* state member 
	State* getState();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();


};

