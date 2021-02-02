/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Files: nodeType.h, linkedListIterator.h, linkedListType.h, 
	unorderedLinkedList.h
	Description: Header file for class linkedListType
******************************************************************************/

#ifndef linkedListType_H
#define linkedListType_H

#include <cassert>
#include "nodeType.h"
#include "linkedListIterator.h"

using namespace std;

template <class Type>
class linkedListType
{
	public:
		const linkedListType<Type>& operator=(const linkedListType<Type>&);
		//Overload the assignment operator
		
		void initializeList();
		//Initializes the list to an empty state
		//Post-condition: first = NULL, last = NULL, count = 0
		
		bool isEmptyList() const;
		//Determines whether the list is empty or not 
		//Post-condition: Returns true if list is empty, else returns false
		
		void print() const;
		//Function to print the contents of the list
		//Post condition: No change to variables at this time
		
		int length() const;
		//Function to return the number of nodes in the list
		//Post-condition: The value of count is returned
		
		void destroyList();
		//Function to delete all the nodes from the list
		//Post condition: first = NULL, last = NULL, count = 0
		
		Type front() const;
		//Function to return the first element of the list
		//Post-condition: If the list is empty, program terminates;
		//otherwise, returns first element of the list
		
		Type back() const;
		//Function to return the last element of the list
		//Post-condition: If the list is empty, program terminates;
		//otherwise, returns last element of the list
		
		virtual bool search(const Type& searchItem) const = 0;
		//Function to determine whether searchItem is in the list
		//Post-condition: Returns true if searchItem is in the list,
		//otherwise returns false
		
		virtual void insertFirst(const Type& newItem) = 0;
		//Function to insert newItem at the beginning of the list
		//Post-condition: first points to the new list, newItem is inserted
		//at the beginning of the list, last points to the last node of the
		//list, and count is incremented by 1
		
		virtual void insertLast(const Type& newItem) = 0;
		//Function to insert newItem at the end of the list
		//Post-condition: first points to the new list, newItem is inserted
		//at the end of the list, last points to the last node of the
		//updated list, and count is incremented by 1
		
		virtual void deleteNode(const Type& deleteItem) = 0;
		//Function to delete deleteItem from the list
		//Post-condition: If found, node containing deleteItem is deleted
		//from the list. First points to the first node, last points to the
		//last node, and count is decremented by 1.
		
		void divideMid(linkedListType<Type>& sublist);
		//The operation divides the given list into two sublists of almost
		//equal value
		//Post-condition: first points to the first node and last points to the
		//last node of the first sublist
		//sublist.first points to the first node and sublist.last points to the 
		//last node of the second sublist
		
		linkedListIterator<Type> begin();
		//Function to return an iterator at the beginning of the linked list
		//Post-condition: Returns an iterator such that current is set to first
		
		linkedListIterator<Type> end();
		//Function to return an iterator one element past the last element of the linked list
		//Post-condition: Returns an iterator such that current is set to NULL
		
		linkedListType();
		//Default constructor
		//Initializes the list to the default state
		//Post-condition: first = NULL, last = NULL, count = 0
		
		linkedListType(const linkedListType<Type>& otherList);
		//Copy constructor
		
		~linkedListType();
		//Destructor
		//Deletes all the nodes from the list
		//Post-condition: The list object is destroyed
		
		protected:
			
			int count;
			//Variable to store the number of elements in the list
			
			nodeType<Type> *first; 
			//pointer to the first node of the list
			
			nodeType<Type> *last;
			//pointer to the last node of the list
			
		private:
			void copyList(const linkedListType& otherList);
			//Function to make a copy of otherList
			//Post-condition: A copy of otherList is created and assigned to this list 
};

template <class Type>
const linkedListType<Type>& linkedListType<Type>::operator=(const linkedListType<Type>& otherList)
{
	if(this = &otherList)
	{
		copyList(otherList);
	}
	return *this;
}

template <class Type>
void linkedListType<Type>::initializeList()
{
	destroyList();
}

template <class Type>
bool linkedListType<Type>::isEmptyList() const
{
	return (first == NULL);
}

template <class Type>
void linkedListType<Type>::print() const
{
	nodeType<Type> *current;
	//pointer to traverse the list
	
	current = first;
	
	while(current != NULL)
	{
		cout << current->info << " ";
		current = current->link;
	}
}

template <class Type>
int linkedListType<Type>::length() const
{
	return count;
}

template <class Type>
void linkedListType<Type>::destroyList()
{
	nodeType<Type> *temp;
	
	while(first != NULL)
	{
		temp = first;
		first = first->link;
		delete temp;
	}
	
	last = NULL;
	
	count = 0;
}

//Default Constructor
template <class Type>
linkedListType<Type>::linkedListType()
{
	first = NULL;
	last = NULL;
	count = 0;
}

//Copy Constructor
template <class Type>
linkedListType<Type>::linkedListType(const linkedListType& otherList)
{
	first = NULL;
	copyList(otherList);
}

//Destructor
template <class Type>
linkedListType<Type>::~linkedListType()
{
	destroyList();
}

template <class Type>
void linkedListType<Type>::copyList(const linkedListType<Type>& otherList)
{
	nodeType<Type> *newNode;
	nodeType<Type> *current;
	
	if(first != NULL)
	{
		destroyList();
	}
	
	if(otherList.first == NULL)
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	
	else
	{
		current = otherList.first;
		
		count = otherList.count;
		
		first = new nodeType<Type>;
		first->info = current->info;
		first->link = NULL;
		
		last = first;
		
		current = current->link;
		
		while(current != NULL)
		{
			newNode = new nodeType<Type>;
			newNode->info = current->info;
			newNode->link = NULL;
			
			last->link = newNode;
			last = newNode;
			
			current = current->link;
		}
	}
	
}

template <class Type>
Type linkedListType<Type>::front() const
{
	assert(first != NULL);
	return first->info;
}

template <class Type>
Type linkedListType<Type>::back() const
{
	assert(last != NULL);
	return last->info;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::begin()
{
	linkedListIterator<Type> temp(first);
	
	return temp;
}

template <class Type>
linkedListIterator<Type> linkedListType<Type>::end()
{
	linkedListIterator<Type> temp(NULL);
	
	return temp;
}

template <class Type>
void linkedListType<Type>::divideMid(linkedListType<Type>& sublist)
{
	int originalList;
	//Stores the length of the original list
	
	int newList;
	//Stores the length of the new list
	
	if ((count % 2) != 0) 
		originalList = ((count/2) + 1);
	else 
		originalList = (count/2);
	
	newList = (count - originalList);

	nodeType<Type> *current;
	current = first;
	sublist.last = last;
	
	for (int i = 0; i < originalList; i++)
	{
		last = current; 
		//Sets last equal to the current node
		
		current = current->link; 
		//Current travels down the list until it reaches the node at the position
		//defined by originalList
	}
	
	sublist.first = current; 
	//sublist.first is assigned to the first node past the midpoint
	
	last->link = NULL; 
	//Sets the last link of the original list to NULL
	
	count = originalList;
	//Sets count for the given list to the new value calculated by originalList
	
	sublist.count = newList;
	//Sets count for the new sublist to the new value calculated by newList
} 
#endif
