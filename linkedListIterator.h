/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Files: nodeType.h, linkedListIterator.h, linkedListType.h, 
	unorderedLinkedList.h, Chapter16_Ex5_MainProgram.cpp
	Description: Header file for class linkedListIterator
******************************************************************************/

#ifndef linkedListIterator_H
#define linkedListIterator_H

#include "nodeType.h"
#include <iostream>

using namespace std;

template <class Type>
class linkedListIterator
{
	public:
		linkedListIterator();
		//Default Constructor
		//Post-condition: current = NULL
		
		linkedListIterator(nodeType<Type> *ptr);
		//Constructor with parameter
		//Post-condition: current = ptr;
		
		Type operator*();
		//Function to overload the dereferencing operator
		//Post-condition: Returns the info contained in the node
		
		linkedListIterator<Type> operator++();
		//Overload the post increment operator
		//Post-condition: The iterator is advanced to the next node
		
		bool operator==(const linkedListIterator<Type>& right) const;
		//Overload the equality operator
		//Post-condition: returns true if the this iterator is equal to the
		//iterator specified by right, else returns false
		
		bool operator!=(const linkedListIterator<Type>& right) const;
		//Overload the inequality operator
		//Post-condition: returns true if the this iterator is not equal to the
		//iterator specified by right, else returns false
	
	private:
		nodeType<Type> *current;
		//Pointer to the current node
};

template <class Type>
linkedListIterator<Type>::linkedListIterator()
{
	current = NULL;
}

template <class Type>
linkedListIterator<Type>::linkedListIterator(nodeType<Type> *ptr)
{
	current = ptr;
}

template <class Type>
Type linkedListIterator<Type>::operator* ()
{
	return current->info;
}

template <class Type>
linkedListIterator<Type> linkedListIterator<Type>::operator++()
{
	current = current->link;
	
	return *this;
}

template <class Type>
bool linkedListIterator<Type>::operator==(const linkedListIterator<Type>& right) const
{
	return (current == right.current);
}

template <class Type>
bool linkedListIterator<Type>::operator!=(const linkedListIterator<Type>& right) const
{
	return (current != right.current);
}

#endif

