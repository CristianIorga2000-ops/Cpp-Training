#pragma once
/*
GOAL:
	Implement a SortedSet ADT using a binary search tree with linked
		representation with dynamic allocation.
*/
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;
struct Node {
	TComp data;
	Node* left;
	Node* right;
};

class SortedSet {
	friend class SortedSetIterator;
public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);


	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;


	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();

//private:
	Node* mainRoot;
	int nrElem;
	int capacity;
	Relation relation;
	bool successfulOperation;


	//Create a new node in a binary search tree
	Node* getNewNode(TComp data);
	//Insert data in ka binary search tree
	Node* insert(Node* root, TComp data);
	//Search for data in a binary search tree
	bool searchBST(Node* root, TElem data) const;
	//Traverse a binary tree post-order and delete all elements
	void postOrderDeletion(Node* root);
	//Delete the node with given parameter data from a tree
	// Return the new root of the tree
	Node* removeBST(Node* root, TComp data);
};
