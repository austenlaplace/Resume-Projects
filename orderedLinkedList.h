/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Due Date:
	Files:
	Description:
******************************************************************************/

#ifndef orderedLinkedList_H
#define orderedLinkedList_H

#include <iostream>
#include "nodeType.h"
#include "linkedListIterator.h"
#include "linkedListType.h"

using namespace std;

template <class Type>
class orderedLinkedList: public linkedListType<Type>
{
	public:
		bool search(const Type& searchItem) const;
		//Function to determine whether searchItem is in the list
		//Postcondition: Returns true if searchItem is in the list,
		//otherwise returns false
		
		void insertL(const Type& newItem);
		//Function to insert newItem in the list
		//Postcondition: first points to the new list, newItem
		//is inserted at the proper place in the list, and count
		//is incremented by one
		
		void insertFirst(const Type& newItem);
		//Function to insert newItem at the beginning of the list
		//Postcondition: first points to the new list, newItem is inserted
		//at the beginning of the list, last points to the last node of the
		//list, and count is incremented by 1
		
		void insertLast(const Type& newItem);
		//Function to insert newItem at the end of the list
		//Postcondition: first points to the new list, newItem is inserted
		//at the end of the list, last points to the last node of the
		//updated list, and count is incremented by 1
		
		void deleteNode(const Type& deleteItem);
		//Function to delete deleteItem from the list
		//Postcondition: If found, node containing deleteItem is deleted
		//from the list. First points to the first node and count is decremented by 1.
		//If deleteItem is not found, prints an appropriate message
};

template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const
{
	bool found = false;
	nodeType<Type> *current;
	//Pointer to traverse the list
	
	current = this->first;
	
	while(current != NULL && !found)
		if(current->info >= searchItem)
			found = true;
		else
			current = current->link;
			
	if(found)
		found = (current->info == searchItem); //test for equality
		
	return found;
}

template <class Type>
void orderedLinkedList<Type>::insertL(const Type& newItem)
{
	nodeType<Type> *current;
	//pointer to traverse the list
	
	nodeType<Type> *trailCurrent;
	//pointer to node just before current
	
	nodeType<Type> *newNode;
	//pointer to create a node
	
	bool found;
	
	//Create the node
	newNode = new nodeType<Type>;
	
	//Store newItem in the node
	newNode->info = newItem;
	
	//set the link field of the node to NULL
	newNode->link = NULL;
	
	if(this->first == NULL) //Case 1
	{
		this->first = newNode;
		this->last = newNode;
		this->count++;
	}
	
	else
	{
		current = this->first;
		found = false;
		
		while(current != NULL && !found) //search the list
			if(current->info >= newItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		
		if(current == this->first)	//Case 2
		{
			newNode->link = this->first;
			this->first = newNode;
			this->count++;
		}
		
		else
		{
			trailCurrent->link = newNode;
			newNode->link = current;
			
			if(current == NULL)
				this->last = newNode;
		
			this->count++;
		}
	}	// End Else
}	//End insert

template <class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
	insertL(newItem);
}

template <class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
	insertL(newItem);
}

template <class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type> *current;
	//pointer to traverse the list
	
	nodeType<Type> *trailCurrent;
	//pointer to node just before current
	
	bool found;
	
	if(this->first == NULL)	//Case 1
		cout << "Cannot delete from an empty list." << endl;
	
	else
	{
		current = this->first;
		found = false;
		
		while(current != NULL && !found) //search the list
			if(current->info >= deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		
		if(current == NULL)	//Case 4
			cout << "The item to be deleted is not in the list." << endl;
			
		else
			if(current->info == deleteItem) //The item to be deleted is in the list
			{
				if(this->first == current)	//Case 2
				{
					this->first = this->first->link;
					
					if(this->first == NULL)
						this->last = NULL;
						
					delete current;
				}
				else	//Case 3
					{
						trailCurrent->link = current->link;
						
						if(current == this->last)
							this->last = trailCurrent;
							
						delete current;
					}
				this->count--;
			}
		else
			cout << "The item to be deleted is not in the list." << endl;
	}		
}	//End deleteNode
#endif
