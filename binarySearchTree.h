/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Due Date:
	Files:
	Description:
******************************************************************************/

#ifndef binarySearchTree_H
#define binarySearchTree_H

#include <iostream>
#include "binaryTree.h"

using namespace std;

template<class elemType>
class bSearchTreeType: public binaryTreeType<elemType>
{
	public:
		bool search(const elemType& searchItem) const;
		//Function to determine if searchItem is in the binary search tree
		//Postcondition: Returns true if searchItem is found within the binary
		//search tree, otherwise returns false
		
		void insert(const elemType& insertItem);
		//Function to insert insertItem into the binary tree
		//Postcondition: If there is no node in the binary search tree that has the 
		//same info as insertItem, a node with the info of insertItem is created
		//and inserted into the binary search tree
		
		void deleteNode(const elemType& deleteItem);
		//Function to delete deleteItem from the binary tree
		//Postcondition: If a node with the same info as deleteItem is found, 
		//it is deleted from the binary search tree. If the binary search tree is empty, or if 
		//deleteItem is not found within it, an appropriate message is printed.
		
	private:
		void deleteFromTree(binaryNodeType<elemType>* &p);
		//Function to delete the node to which p points is deleted from
		//the binary search tree
		//Postcondition: The node to which p points is deleted from the binary search tree
};

template<class elemType>
bool bSearchTreeType<elemType>::search(const elemType& searchItem) const
{
	binaryNodeType<elemType> *current;
	bool found = false;
	
	if(this->root == NULL)
		cout << "Cannot search an empty tree." << endl;
	else
	{
		current = this->root;
		
		while(current != NULL && !found)
		{
			if(current->info == searchItem)
				found = true;
			else if(current->info > searchItem)
				current = current->lLink;
			else
				current = current->rLink;	
		}
	}
	
	return found;
}

template<class elemType>
void bSearchTreeType<elemType>::insert(const elemType& insertItem)
{
	binaryNodeType<elemType> *current;
	//Pointer to traverse the tree
	
	binaryNodeType<elemType> *trailCurrent;
	//Pointer behind current
	
	binaryNodeType<elemType> *newNode;
	//Pointer to create the node
	
	newNode = new binaryNodeType<elemType>;
	newNode->info - insertItem;
	newNode->lLink = NULL;
	newNode->rLink = NULL;
	
	if(this->root == NULL)
		this->root = newNode;
	else
	{
		current = this->root;
		
		while(current != NULL)
		{
			trailCurrent = current;
			
			if(current->info == insertItem)
			{
				cout << "The item to be inserted is already in the tree -- ";
				cout << "duplicates are not allowed." << endl;
				return;
			}
			else if(current->info > insertItem)
				current = current->lLink;
			else
				current = current->rLink;
		}
		if(trailCurrent->info > insertItem)
			trailCurrent->lLink = newNode;
		else
			trailCurrent->rLink = newNode;	
	}
}

template<class elemType>
void bSearchTreeType<elemType>::deleteFromTree(binaryNodeType<elemType>* &p)
{
	binaryNodeType<elemType> *current;
	//Pointer to traverse the tree
	
	binaryNodeType<elemType> *trailCurrent;
	//Pointer behind current
	
	binaryNodeType<elemType> *temp;
	//Pointer to delete the node
	
	if(p == NULL)
		cout << "Error: The node to be deleted is NULL." << endl;
	else if(p->lLink == NULL && p->rLink == NULL)
	{
		temp = p;
		p = NULL;
		delete temp;
	}
	else if(p->lLink == NULL)
	{
		temp = p;
		p = temp->rLink;
		delete temp;
	}
	else if(p->rLink == NULL)
	{
		temp = p;
		p = temp->lLink;
		delete temp;
	}
	else
	{
		current = p->lLink;
		trailCurrent = NULL;
		
		while(current->rLink != NULL)
		{
			trailCurrent = current;
			current = current->rLink;
		}
		
		p->info = current->info;
		
		if(trailCurrent == NULL)	//Current did not move; current == p->lLink, adjust p
			p->lLink = current->lLink;
		else
			trailCurrent->rLink = current->lLink;
			
		delete current;
	}
}	

template<class elemType>
void bSearchTreeType<elemType>::deleteNode(const elemType& deleteItem)
{
	binaryNodeType<elemType> *current;
	//Pointer to traverse the tree
	
	binaryNodeType<elemType> *trailCurrent;
	//Pointer behind current
	
	bool found = false;
	
	if(this->root == NULL)
		cout << "Cannot delete from an empty tree." << endl;
	else
	{
		current = this->root;
		trailCurrent = this->root;
		
		while(current != NULL && !found)
		{
			if(current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				
				if(current->info > deleteItem)
					current = current->lLink;
				else
					current = current->rLink;
			}
		}
	if(current == NULL)
		cout << "The item to be deleted is not in the tree." << endl;
	else if(found)
		{
			if(current == this->root)
				deleteFromTree(this->root);
			else if(trailCurrent->info > deleteItem)
				deleteFromTree(trailCurrent->lLink);
			else
				deleteFromTree(trailCurrent->rLink);
		}
	else
		cout << "The item to be deleted is not in the tree." << endl;
	}
}	
#endif
