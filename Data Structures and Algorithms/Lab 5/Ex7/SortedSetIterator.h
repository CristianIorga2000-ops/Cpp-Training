#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& set;
	SortedSetIterator(const SortedSet& m);
	void initValues(Node* node);
	int index;
	TComp* valuesArray;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};

