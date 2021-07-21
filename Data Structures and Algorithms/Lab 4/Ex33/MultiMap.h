/*
GOAL
	Implement a MultiMap ADT using a hashtable with open addresing and 
		double hashing in which unique keys are stored with a dynamic
		array of asociated values.
*/
#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TKey;
typedef int TValue;
typedef std::pair < TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)

const float HASH_LOAD_FACTOR = 0.75;

class MultiMapIterator;

class MultiMap
{
public:
	//constructor
	MultiMap();

	//destructor
	~MultiMap();

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

private:
	friend class MultiMapIterator;
	//Dynamically alocated array for memorizing values associated to a key
	struct Array {
		int size;
		int capacity;
		TValue* values;
	};
	//An entry in the hash table
	struct HashEntry {
		TKey key;
		Array array;
	};
	//A position in the array can be: vacant, occupied, have a deleted HashEntry.
	enum class State : unsigned char {
		Vacant,
		Occupied,
		Deleted,
	};

	HashEntry* elements;
	State* state;
	int maxSize;
	int currentSize;

	//Hashing operations
	static int hash1(TKey key, int tableSize);
	static int hash2(TKey key, int tableSize);

	//Auxiliary private operations for working on the HashTable
	float getLoadFactor() const;
	bool isOverloaded() const;
	int getNewSize() const;
	void resizeHashTable();

	//Auxiliary private operations for working on Array 
	void addToArray(int positionInHashTable, TValue val);
	bool deleteFromArray(int positionInHashTable, TValue val);
	void resizeArray(int positionInHashTable);

};

