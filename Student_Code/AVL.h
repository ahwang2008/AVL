#pragma once
#include "AVLInterface.h"
#include "NodeInterface.h"
using namespace std;

struct Node :
	public NodeInterface

{
public:
	int data;
	int height;
        int balance;
        //int leftside;
        //int rightside;
	Node* left; //-> to the left
	Node* right; //-> to the right
	Node(int data)
	{
		left = NULL;
		right = NULL;
		this->data = data;
	}
	~Node()
	{
	}
	int getData()
	{
		return data;
	}
	Node* getLeftChild()
	{
		if (left == NULL)
		{
			return NULL;
		}
		else
		{
			return left;
		}
	}
	Node* getRightChild()
	{
		if (right == NULL)
		{
			return NULL;
		}
		else
		{
			return right;
		}
	}
	/*
	* Returns the height of this node. The height is the number of nodes
	* along the longest path from this node to a leaf.  While a conventional
	* interface only gives information on the functionality of a class and does
	* not comment on how a class should be implemented, this function has been
	* provided to point you in the right direction for your solution.  For an
	* example on height, see page 448 of the text book.
	*
	* @return the height of this tree with this node as the local root.
	*/
	int getHeight()
	{
		return height;
	}
};

class AVL :
	public AVLInterface

{
public:
	AVL();
	~AVL();
	NodeInterface* getRootNode();
	bool add(int data);
	bool addrec(Node *&n, int data);
	bool remove(int data);
	bool remrec(Node*&n, int data);
	void clear();
        int height(Node *&n);
	int updateHeight(Node *&n);
        int updateBalance(Node *&n);
        void RR(Node *&n);
        void LL(Node *&n);
	void RL(Node *&n);
	void LR(Node *&n);
	//int balanceit(Node *n);
        //bool isbalanced(left, right);
};
