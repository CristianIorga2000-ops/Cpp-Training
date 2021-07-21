#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
private:
	friend class MultiMap;

	const MultiMap& iteratedMultiMap;
	int indexHashMap;
	int indexArray;

	//Verify if indexArray is valid
	bool validIndexArray();

	//Constructor
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();
};

