/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++

/**********WEEK FIVE***********/
/*
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values
with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants.
The tree s could also be considered as a subtree of itself.

//TEBOW IT

/*
1. T - TALK
Input: Two node pointers, one is the root of tree s and the other is a root of tree t.
Output: True if tree t has exactly the same structure and node values with a subtree of s, false otherwise.

Clarified:
Duplicate values in tree: May be there.
Are the trees BST's (Binary Search Trees): No
Handling NULL input: An empty tree is a subtree of an tree, return true if t is NULL.

2. E - EXAMPLES
Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2

Given tree t:
   4
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.

Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.

Example 3:
Given tree s: NULL
Given tree t: NULL
Return true.

Example 4:
Given tree s: 1
Given tree t: NULL
Return true.

Example 3:
Given tree s: NULL
Given tree t: 1
Return false.

3. B - BRUTE-FORCE

Carry out Pre-order traversal of both the trees, t and s. Create a string representation from the traversal.
(Take X as special character insertion for every NULL node.) If the string representation of t's traversal matches with a
substring of s's traversal string, then t is a subtree of s.
Complexity:
Time:   O(n+m)
Space:  O(n+m)
n,m are the number of nodes in s and t respectively.

4. O - OPTIMISE
Traverse the tree s.
Each time the root of t matches with one of the nodes in s, traverse the two trees simultaneously.
If they are equal in structure and value, return true. Else, return false.

5. W - WALK THROUGH
Explained as comments in the code

6. I - IMPLEMENT
*/
#include <bits/stdc++.h>
using namespace std;
struct node
{
    int data;
    struct node* left;
    struct node* right;
}*root_s,*root_t;

struct node* newNode(int data)
{
    struct node* ptr = (struct node*)malloc(sizeof(node));
    ptr->data = data;
    ptr->left = ptr->right = NULL;
    return ptr;
}

//function for inserting the nodes when given an array of level order traversal as input
struct node* insertNode(int levelOrder[], node* root, int i, int n)
{
    // n is the size of the array
    if (i < n)
    {
        node* ptr = newNode(levelOrder[i]);
        root = ptr;
        root->left = insertNode(levelOrder,root->left, 2*i+1, n);
        root->right = insertNode(levelOrder,root->right, 2*i+2, n);
    }
    return root;
}

bool isSubtree(struct node* s, struct node* t)
{
    if(s==NULL && t==NULL)
        return true;
    if(s!=NULL && t==NULL)
        return true;
    if(s==NULL && t!=NULL)
        return false;
    //check for equality of values and recurse on to the left and right subtrees
    if(s->data==t->data && isSubtree(s->left,t->left) && isSubtree(s->right,t->right))
        return true;
    return isSubtree(s->left,t) || isSubtree(s->right,t);
}

//7. T - TEST

bool isSubtree_NULL_s_and_t() //should return true
{
	root_s = NULL;
	root_t = NULL;
    return isSubtree(root_s,root_t);
}

bool isSubtree_NULL_s_only()  //should return false
{
    root_s=NULL;
    int levelOrder_t[]={3};
    int n=sizeof(levelOrder_t)/sizeof(levelOrder_t[0]);
    root_t = insertNode(levelOrder_t, root_t,0,n);
    return isSubtree(root_s,root_t);
}
bool isSubtree_NULL_t_only()  //should return true
{
    root_t=NULL;
    int levelOrder_s[]={3};
    int n=sizeof(levelOrder_s)/sizeof(levelOrder_s[0]);
    root_s = insertNode(levelOrder_s, root_s,0,n);
    return isSubtree(root_s,root_t);
}
bool isSubtree_True() //should return true
{
	int levelOrder_s[]={3,4,5,1,2};
    int n=sizeof(levelOrder_s)/sizeof(levelOrder_s[0]);
    root_s = insertNode(levelOrder_s,root_s,0,n);
    int levelOrder_t[]={4,1,2};
	n=sizeof(levelOrder_t)/sizeof(levelOrder_t[0]);
    root_t = insertNode(levelOrder_t,root_t,0,n);
    return isSubtree(root_s,root_t);
}

bool isSubtree_False() //should return false
{
	int levelOrder_s[]={3,4,5,1,2};
    int n=sizeof(levelOrder_s)/sizeof(levelOrder_s[0]);
    root_s = insertNode(levelOrder_s,root_s,0,n);
    int levelOrder_t[]={4,1,4};
	n=sizeof(levelOrder_t)/sizeof(levelOrder_t[0]);
    root_t = insertNode(levelOrder_t,root_t,0,n);
    return isSubtree(root_s,root_t);
}

bool isSubtree_EqualTrees() //should return true
{
	int levelOrder_s[]={3,4,5,1,2};
    int n=sizeof(levelOrder_s)/sizeof(levelOrder_s[0]);
    root_s = insertNode(levelOrder_s,root_s,0,n);
    int levelOrder_t[]={3,4,5,1,2};
	n=sizeof(levelOrder_t)/sizeof(levelOrder_t[0]);
    root_t = insertNode(levelOrder_t,root_t,0,n);
    return isSubtree(root_s,root_t);
}

int main()
{
    // TREE s:
    /* 
 			    1
		       / \
              2   3
             / \
           4   5
    */

    int levelOrder_s[]={1,2,3,4,5};
    int n=sizeof(levelOrder_s)/sizeof(levelOrder_s[0]);
    root_s = insertNode(levelOrder_s,root_s,0,n);

    // TREE t:
    /* 
             2
            / \
           4   5 
    */
	int levelOrder_t[]={2,4,5,1};
	n=sizeof(levelOrder_t)/sizeof(levelOrder_t[0]);
    root_t = insertNode(levelOrder_t,root_t,0,n);
    if (isSubtree(root_s,root_t))
       cout<<"Tree T is a subtree of Tree S.\n";
    else
       cout<<"Tree T is not a subtree of Tree S.\n";

 	if(isSubtree_NULL_s_and_t() && !(isSubtree_NULL_s_only()) && isSubtree_NULL_t_only() && isSubtree_True() && !(isSubtree_False()) && isSubtree_EqualTrees())
		cout<<"All test cases passed.";
 	else
		cout<<"One or more test cases failed.";
    return 0;
}

