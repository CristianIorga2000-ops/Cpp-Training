#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <assert.h>


using namespace std;
bool asc(TComp a, TComp b) {
	return a < b;
}

int main() {
	testAll();
	testAllExtended();
	cout << "\nTest end" << endl;
	system("pause");
}