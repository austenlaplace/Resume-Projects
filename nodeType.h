/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Files: nodeType.h, linkedListIterator.h, linkedListType.h, 
	unorderedLinkedList.h, Chapter16_Ex5_MainProgram.cpp
	Description: Header file for struct nodeType
******************************************************************************/

#ifndef nodeType_H
#define nodeType_H

using namespace std;

template <class Type>
struct nodeType
{
	int info;
	nodeType<Type> *link;
};

#endif
