/******************************************************************************
	Name: Austen Laplace
	Class: CSC 161
	Due Date:
	Files:
	Description:
******************************************************************************/

#ifndef binaryTree_H
#define binaryTree_H

#include <iostream>
#include "orderedLinkedList.h"

using namespace std;

template <class elemType>

struct binaryNodeType
{
	elemType info;
	binaryNodeType<elemType> *lLink;
	binaryNodeType<elemType> *rLink;
};

template <class elemType>
class binaryTreeType
{
	public:
		const binaryTreeType<elemType>& operator=(const binaryTreeType<elemType>&);
		//Function to overload assignment operator
		
		bool isEmpty() const;
		//Function to determine whether the binary tree is empty
		//Postcondition: Returns true if the binary tree is empty,
		//otherwise returns false
		
		void inorderTraversal() const;
		//Function to do an inorder traversal of the binary tree
		//Postcondition: Nodes are printed in an inorder sequence
		
		void preorderTraversal() const;
		//Function to do a preorder traversal of the binary tree
		//Postcondition: Nodes are printed in a preorder sequence
		
		void postorderTraversal() const;
		//Function to do a postorder traversal of the binary tree
		//Postcondition: Nodes are printed in an postorder sequence
		
		int treeHeight() const;
		//Function to determine the height of the binary tree
		//Postcondition: Returns the height of the binary tree
		
		int treeNodeCount() const;
		//Function to determine the number of nodes in the tree
		//Postcondition: Returns the number of nodes in the tree
		
		int treeLeavesCount() const;
		//Function to determine the number of leaves in the tree
		//Postcondition: Returns the number of leaves in the tree
		
		void destroyTree();
		//Function to destroy the binary tree
		//Postcondition: Memory space allocated by each node is deallocated.
		//root = NULL;
		
		void createList(orderedLinkedList<elemType> &list);
		//Function to insert the nodes of a binary tree into a linked list
		//Postcondition: The linked list contains the information held by the 
		//nodes of the binary tree
		
		void convertToList(binaryNodeType<elemType> *p, orderedLinkedList<elemType> &list) const;
		
		virtual bool search(const elemType& searchItem) const = 0;
		//Function to determine if searchItem is in the binary tree
		//Postcondition: Returns true if searchItem is found within the binary
		//tree, otherwise returns false
		
		virtual void insert(const elemType& insertItem) = 0;
		//Function to insert insertItem into the binary tree
		//Postcondition: If there is no node in the binary tree that has the 
		//same info as insertItem, a node with the info of insertItem is created
		//and inserted into the binary tree
		
		virtual void deleteNode(const elemType& deleteItem) = 0;
		//Function to delete deleteItem from the binary tree
		//Postcondition: If a node with the same info as deleteItem is found, 
		//it is deleted from the binary tree. If the binary tree is empty, or if 
		//deleteItem is not found within it, an appropriate message is printed.
		
		binaryTreeType(const binaryTreeType<elemType>& otherTree);
		//Copy constructor
		
		binaryTreeType();
		//Default constructor
		
		~binaryTreeType();
		//Destructor
		
	protected:
		binaryNodeType<elemType> *root;
		//Pointer to the head of the binary tree
		
	private:
		void copyTree(binaryNodeType<elemType>* &copiedTreeRoot, binaryNodeType<elemType>* otherTreeRoot);
		//Makes a copy of the binary tree to which otherTreeRoot points
		//Postcondition: The pointer copiedTreeRoot points to the root of the copied binary tree
		
		void destroy(binaryNodeType<elemType>* &p);
		//Function to destroy the binary tree to which p points
		//Postcondition: Memory space occupied by each node, in the binary tree to which p points,
		//is deallocated, p = NULL;
		
		void inorder(binaryNodeType<elemType>* p) const;
		//Function to do an inorder traversal of the binary tree to which p points
		//Postcondition: Nodes of the binary tree, to which p points, are printed in inorder sequence
		
		void preorder(binaryNodeType<elemType>* p) const;
		//Function to do an preorder traversal of the binary tree to which p points
		//Postcondition: Nodes of the binary tree, to which p points, are printed in preorder sequence
		
		void postorder(binaryNodeType<elemType>* p) const;
		//Function to do an postorder traversal of the binary tree to which p points
		//Postcondition: Nodes of the binary tree, to which p points, are printed in postorder sequence
		
		int height(binaryNodeType<elemType> *p) const;
		//Function to determine the height of the binary tree, to which p points
		//Postcondition: Height of the binary tree to which p points is returned
		
		int max(int x, int y) const;
		//Function to determine the larger of x and y
		//Postcondition: Returns the larger of x and y
		
		int nodeCount(binaryNodeType<elemType> *p) const;
		//Function to determine the number of nodes in the binary tree to which p points
		//Postcondition: The number of nodes in the binary tree to which p points is returned
		
		int leavesCount(binaryNodeType<elemType> *p) const;
		//Function to determine the number of leaves in the binary tree to which p points
		//Postcondition: The number of leaves in the binary tree to which p points is returned
};

template <class elemType>
bool binaryTreeType<elemType>::isEmpty() const
{
	return (root == NULL);
}

template <class elemType>
binaryTreeType<elemType>::binaryTreeType()
{
	root = NULL;
}

template <class elemType>
void binaryTreeType<elemType>::inorderTraversal() const
{
	inorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::preorderTraversal() const
{
	preorder(root);
}

template <class elemType>
void binaryTreeType<elemType>::postorderTraversal() const
{
	postorder(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeHeight() const
{
	return height(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeNodeCount() const
{
	return nodeCount(root);
}

template <class elemType>
int binaryTreeType<elemType>::treeLeavesCount() const
{
	return leavesCount(root);
}

template <class elemType>
void binaryTreeType<elemType>::inorder(binaryNodeType<elemType> *p) const
{
	if(p != NULL)
		{
			inorder(p->lLink);
			cout << p->info << " ";
			inorder(p->rLink);
		}
}

template <class elemType>
void binaryTreeType<elemType>::preorder(binaryNodeType<elemType> *p) const
{
	if(p != NULL)
		{
			cout << p->info << " ";
			preorder(p->lLink);
			preorder(p->rLink);
		}
}

template <class elemType>
void binaryTreeType<elemType>::postorder(binaryNodeType<elemType> *p) const
{
	if(p != NULL)
	{
		postorder(p->lLink);
		postorder(p->rLink);
		cout << p->info << " ";
	}
}

template <class elemType>
int binaryTreeType<elemType>::height(binaryNodeType<elemType> *p) const
{
	if(p == NULL)
		return 0;
	else
		return 1 + max(height(p->lLink), height(p->rLink));
}

template <class elemType>
int binaryTreeType<elemType>::max(int x, int y) const
{
	if(x >= y)
		return x;
	else
		return y;
}

template <class elemType>
void binaryTreeType<elemType>::copyTree(binaryNodeType<elemType>* &copiedTreeRoot, binaryNodeType<elemType>* otherTreeRoot)
{
	if(otherTreeRoot == NULL)
		copiedTreeRoot = NULL;
	else
	{
		copiedTreeRoot = new binaryNodeType<elemType>;
		copiedTreeRoot->info = otherTreeRoot->info;
		copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
		copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
	}
}

template <class elemType>
void binaryTreeType<elemType>::destroy(binaryNodeType<elemType>* &p)
{
	if(p != NULL)
	{
		destroy(p->lLink);
		destroy(p->rLink);
		delete p;
		p = NULL;
	}
}

template <class elemType>
void binaryTreeType<elemType>::destroyTree()
{
	destroy(root);
}

//Copy constructor
template <class elemType>
binaryTreeType<elemType>::binaryTreeType(const binaryTreeType<elemType>& otherTree)
{
	if(otherTree.root == NULL) //otherTree is empty
		root = NULL;
	else
		copyTree(root, otherTree.root);
}

//Destructor
template <class elemType>
binaryTreeType<elemType>::~binaryTreeType()
{
	destroy(root);
}

//Overload assignment operator
template <class elemType>
const binaryTreeType<elemType>& binaryTreeType<elemType>::operator=(const binaryTreeType<elemType>& otherTree)
{
	if(this != otherTree)	//avoid self-copy
		{
			if(root != NULL)	//If binary tree is not empty, destroy the binary tree
				destory(root);
			
			if(otherTree.root == NULL)	//otherTree is empty
				root = NULL;
			else
				copyTree(root, otherTree.root);
		}
	return *this;
}

template <class elemType>
void binaryTreeType<elemType>::createList(orderedLinkedList<elemType> &list)
{
	convertToList(root, list);
}

template <class elemType>
void binaryTreeType<elemType>::convertToList(binaryNodeType<elemType> *p, orderedLinkedList<elemType> &list) const
{
	if(p != NULL)
		{
			inorder(p->lLink);
			list.insertL(p->info);
			inorder(p->rLink);
		}
}
#endif
