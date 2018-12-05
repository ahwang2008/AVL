#include "AVL.h"
#include <iostream>
#include <algorithm>
#include <iostream>

//Advice:
//1) Try switching the RR & LL algorithms and see what happens(likely bad)
//2) Use the save variable in the add function too and see what works.
//3) Try doing what I did in the remove recursive using updateHeight(), then updateBalance(), then the various cases...

/*
Remember that the LeftChild and RightChild functions keep track of the height. By doing so, you can subtract heights from each other and check if its unbalanced if its not 0 or 1.
To check which rotation is needed (differentiating between right-right and right-left for example), use your child to determine which side is heavier, just like you did with the parent.
Remember it's the top node in the rotation that checks the imbalance.
			o    <-- This one
			 \
			  o
			 /
			o
*/

using namespace std;

Node* root = NULL;
int leftside = 0;
int rightside = 0;
int balance = 0;

AVL::AVL()
{
	root = NULL;
}

AVL::~AVL()
{
	clear();
}

//Please note that the class that implements this interface must be made
//of objects which implement the NodeInterface

/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
NodeInterface* AVL::getRootNode()
{
	return root;
}

int AVL::height(Node *&n)
{
	if (n == NULL)
	{
		return 0;
	}
	return n->height;
}

int AVL::updateBalance(Node *&n)
{
	if (n == NULL)
	{
		return 0;
	}
	return height(n->left) - height(n->right);
}

int AVL::updateHeight(Node *&n)
{
	if (n == NULL)
	{
		return 0;
	}
	if(n->left == NULL && n->right == NULL) //No children root base case
	{
		n->height = 1;
	}
	if (n->left != NULL)
	{
		updateHeight(n->left);
		leftside = n->left->height;
	}
	else
	{
		leftside = 0;
	}
	if (n->right != NULL)
	{
		updateHeight(n->right);
		rightside = n->right->height;
	}
	else
	{
		rightside = 0;
	}
	n->height = max(leftside, rightside) + 1;
	return n->height;
}

/*
 * LL:
 * Right Rotatiom
 *
 * LR:
 * Left Rotation on node->left
 * Node* temp = n;
 * n = n->left->right;
 * n->left->right = n->left->right->left;
 * n->left->right->left = temp;
 * Right Rotation on node
 *
 OR
Node* temp = n;
n

 * RR:
 * Left Rotation
 *
 * RL:
 * Right Rotation on node->right
 * Node* temp = n;
 * n = n->right->left;
 * n->right->left = n->right->left->right;
 * n->right->left->right = temp;
 * Left Rotation on node
 *
 *
   Right Rotation:
 * Node* temp = n;
 * n = n->left;
 * n->left = temp;
 *
 * Left Rotation:
 * Node* temp = n;
 * n = n->right;
 * n->right = temp;
*/

void AVL::RR(Node*&n)
{cout << "what" << endl;
    Node* temp = n->right;
    n->right = temp->left;
    temp->left = n;
    n = temp;
}

void AVL::RL(Node*&n)
{cout << "what" << endl;
	RR(n->left);
	LL(n);
}

void AVL::LL(Node*&n) //WORKS
{cout << "LL" << endl;
    Node* temp = n->left;
    n->left = temp->right;
    temp->right = n;
    n = temp;
}

void AVL::LR(Node*&n)
{cout << "what" << endl;
	LL(n->right);
	RR(n);
}

/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data)
{
	return (addrec(root, data));
}

bool AVL::addrec(Node *&n, int data)
{
	bool save = false;
	if (n == NULL) //If pointer is at NULL
    {cout << "Node Added" << endl;
        n = new Node(data);
		save = true;
		//return true;
	}
	else if (data == n->data) //Check for duplicates
	{
		return false;
	}
    else if (data < n->data) //If data is less than the node
    {
        addrec(n->left, data); //Go again
        if (updateHeight(n->left) - updateHeight(n->right) == 2)
        {
            if (data < n->left->data)
            {cout << 1 << endl;
                    LL(n);
                    //updateHeight(n);
            }
            else
            {cout << 2 << endl;
                    RL(n);
            }
        }
        cout << "kept going" << endl;
    }
	else if (data > n->data) //If data is greater than the node
    {
		addrec(n->right, data); //Go again
        if (updateHeight(n->right) - updateHeight(n->left) == 2)
		{
			if (data > n->right->data)
            {cout << 3 << endl;
				RR(n);
			}
			else
            {cout << 4 << endl;
				LR(n);
			}
		}
    }
	return save;
        //updateHeight(n);
}
/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data)
{
	return (remrec(root, data));
}

bool AVL::remrec(Node *&n, int data)
{
        bool save = false;
	if (n == NULL) //If data not found within the list
        {
		return false;
	}
	else if (data < n->data) //If the data is less than the node
	{
                remrec(n->left, data); //Go again
	}
	else if (data > n->data) //If the data is greater than the node
	{
                remrec(n->right, data); //Go again
	}
	else //If we found the node
	{
		if (n->left == NULL && n->right == NULL) //If 0 children...
		{
			delete n; //Delete node
			n = NULL; //Reset node
			save = true;
		}
		else if (n->right == NULL) //If 1 child
		{
			Node *temp = n; //Initiate the parent value
			n = n->left; //The pointer now points to the left child
			delete temp; //Delete the parent
			save = true;
		}
		else if (n->left == NULL) //If 1 child
		{
			Node *temp = n; //Initiate the parent value
			n = n->right; //The pointer now points to the right child
			delete temp; //Delete the parent
			save = true;
		}
		else //If 2 children
		{
			Node *temp = n->left; //Obtain Left child value
			while (temp->right != NULL) //Keep going down the right side of the tree of the left child
			{
				temp = temp->right;
			}
			n->data = temp->data; //The left child's, furthest right value becomes the new root
			remrec(n->left, temp->data); //The 1st variable passed in is the "new" root, 2nd variable is value to be deleted
			save = true;
		}
	}
    if (n == NULL)
    {
		return save;
	}
	updateHeight(n);
    int balance = updateBalance(n);
	if (balance > 1 && updateBalance(n->left) >= 0)
    {
        LL(n);
	}
	else if (balance > 1 && updateBalance(n->left) < 0)
    {
        LR(n);
	}
	else if (balance < -1 && updateBalance(n->right) <= 0)
    {
        RR(n);
	}
	else if (balance < -1 && updateBalance(n->right) > 0)
	{
        RL(n);
	}
        //return save;
}
/*
* Removes all nodes from the tree, resulting in an empty tree.
*/

void AVL::clear()
{
	while (root != NULL)
	{
		remove(root->data); //Continue removing the roots
	}
}
