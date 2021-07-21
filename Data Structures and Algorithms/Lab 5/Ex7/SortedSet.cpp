#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
SortedSet::SortedSet(Relation r)
	:mainRoot{ nullptr }
	, nrElem{ 0 }
	, capacity{ 0 }
	, relation{ r }
	, successfulOperation{ true }
{}


Node* SortedSet::getNewNode(TComp data)
{

	Node* newNode = new Node();
	newNode->data = data;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}


Node* SortedSet::insert(Node* root, TComp data)
{
	successfulOperation = true;

	if (root == nullptr) { // empty tree
		root = getNewNode(data);
	}
	// if it is equal, we cannot insert anything. return null
	else if (root->data == data)
		successfulOperation = false;
	// if data to be inserted is lesser, insert in left subtree. 
	else if ((relation)(data, root->data) == true) {
		root->left = insert(root->left, data);
	}
	// else, insert in right subtree. 
	else if ((relation)(data, root->data) == false) {
		root->right = insert(root->right, data);
	}
	return root;
}

bool SortedSet::searchBST(Node* root, TElem data) const
{
	if (root == nullptr) {
		return false;
	}
	else if (root->data == data) {
		return true;
	}
	//If data is lesser, search in left subtree
	else if ((relation)(root->data, data) == false) {
		return searchBST(root->left, data);
	}
	//If data is greater =, search in right subtree
	else if ((relation)(root->data, data) == true) {
		return searchBST(root->right, data);
	}
}

void SortedSet::postOrderDeletion(Node* root)
{
	if (root == nullptr)
		return;

	// first recur on left subtree
	postOrderDeletion(root->left);

	// then recur on right subtree
	postOrderDeletion(root->right);

	// delete the node
	delete root;

}

Node* SortedSet::removeBST(Node* root, TComp data) {
	//Until we find the element with element->data == parameter data
	//	successfulOperation boolean will be false
	successfulOperation = false;
	// Base case
	if (root == NULL)
		return root;
	
	//If we have found the element we want to delete
	if (root->data == data)
	{
		//Then the the delete operation will be invariably successful 
		successfulOperation = true;
		// If one of the children is empty
		if (root->left == NULL) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			delete root;
			return temp;
		}
		// If both children exist
		else {

			Node* succParent = root;
			// Find successor (the next greater value)
			Node* succ = root->right;
			while (succ->left != NULL) {
				succParent = succ;
				succ = succ->left;
			}

			//If we have a succesor
			if (succParent != root)
				//Make succesor`s right child the left child of succesor`s parent
				succParent->left = succ->right;
			//If this is not a succesor
			else 
				//Simply copy succesor`s right value to parent`s right value
				succParent->right = succ->right;
			// Copy Successor Data to root
			root->data = succ->data;

			// Delete the successor and return the root
			delete succ;
			return root;
		}

	}
	//If this is not the element we want to delete, continue searching
	//Go to the right subtree if data is greater
	else if ((relation)(root->data, data) == true) {
		root->right = removeBST(root->right, data);
		return root;
	}
	//Go to the left subtree if data is lesser
	else if ((relation)(root->data, data) == false) {
		root->left = removeBST(root->left, data);
		return root;
	}
}



bool SortedSet::add(TComp elem) {
	mainRoot = insert(mainRoot, elem); 
	if (successfulOperation)
		nrElem++;
	return successfulOperation;
}


bool SortedSet::remove(TComp elem) {
	mainRoot = removeBST(mainRoot, elem);
	if (successfulOperation)
		nrElem--;
	return successfulOperation;
}

bool SortedSet::search(TElem elem) const
{
	return searchBST(mainRoot, elem);
}


int SortedSet::size() const {
	return nrElem;
}


bool SortedSet::isEmpty() const {
	return nrElem == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	postOrderDeletion(mainRoot);
}


