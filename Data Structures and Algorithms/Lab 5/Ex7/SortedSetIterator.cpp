#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m)
	:set{ m }
	, index{ 0 }
	, valuesArray{ nullptr }
{
	valuesArray = new TComp[set.size()];
	initValues(m.mainRoot);
	first();
}

void SortedSetIterator::initValues(Node* node) {
	if (node == NULL)
		return;

	initValues(node->left);

	valuesArray[index]=static_cast<TElem>(node->data);
	index++;

	initValues(node->right);
}

void SortedSetIterator::first() {
	index = 0;
}


void SortedSetIterator::next() {
	if (!valid()) throw exception();
	index++;
}


TElem SortedSetIterator::getCurrent()
{
	if (!valid()) throw exception();
	return valuesArray[index];
}

bool SortedSetIterator::valid() const {
	return index < set.size();
}

