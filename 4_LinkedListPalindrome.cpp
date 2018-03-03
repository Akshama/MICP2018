/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++
/**********WEEK FOUR***********/
/*
isPalindrome(Linked List)
Implement a function to check if a linked list is a palindrome.
//TEBOW IT
/*
1. T - TALK
Input: A linked list. Elements may be alphanumeric or even special characters. 
Output: TRUE if the linked list is palindromic, FALSE if it is not.
Clarified:
Type of data: ASCII
Special Characters: May be present
Case sensitivity: Yes
2. E - EXAMPLES
	 	a. { 'a','%', 'c', 'c', '%','a'} -> TRUE
	 	b. {} -> FALSE
	 	c. {'a'} -> TRUE
	 	d. {'A', 'b', 'a'} -> FALSE

3. B - BRUTE-FORCE
Make a copy of the input Linked List. 
Reverse the sequence of nodes in the cloned list.
Now, compare both the lists node by node from head to tail node.
If they match, then input Linked List is palindromic otherwise not.

Complexity
Time: O(n)
Space: O(n)

4. O - OPTIMISE
An optimised approach would follow these steps:

4.1 Divide the list into two equal parts by calling findMid that finds the middle node of the list. Use two pointers: slow_pointer and fast_pointer. 
Advance slow_pointer one node at a time while fast_pointer two nodes at a time. The slow pointer points to the mid node when the fast_pointer reaches the end of the list.
4.2 Reverse the second half of the list.
4.3 Compare the two halves.
4.4 Return TRUE if they match, FALSE if not.

Complexity
Time: O(n)
Space: O(1)

W - WALK THROUGH
Explained as comments in the code

6. I - IMPLEMENT
*/
#include <bits/stdc++.h>
using namespace std;

struct Node 
{
    char data;
    struct Node* next;
};

// Helper function to insert a new node in the beginning of the linked list
void insert(struct Node** headRef, int data)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = *headRef;
    *headRef = node;
}

// Iterative function to reverse the nodes of linked list
void reverse(struct Node** headRef)
{
    struct Node* reversed = NULL;
    struct Node* current = *headRef;

	// Iterate through the list and move/insert each node to the front of the result list.
    while (current != NULL)
	{
        struct Node* next = current->next;
        // move the current node to the reversed list
        current->next = reversed;
        reversed = current;
        // process next node
        current = next;
    }

    // fix head pointer
    *headRef = reversed;
}

// Recursive function to check if two linked lists are equal or not
bool compare(struct Node* a, struct Node* b)
{
    // check if both list is empty
    if (a == NULL && b == NULL)
        return true;

    return a && b && (a->data == b->data) && compare(a->next, b->next);
}

// Function to split the linked list into two equal parts and return pointer to the second half
struct Node* findMid(struct Node* head, bool &odd)
{
    struct Node* prev = NULL;
    struct Node *slow = head, *fast = head;

    // find middle pointer
    while (fast && fast->next)
	{
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // for odd nodes, fast still points to last node
    if (fast)
	    odd = true;

    // make next of prev node null
    prev->next = NULL;

    // return mid node: the slow pointer points to the middle node when the fast pointer reaches the end of the list
    return slow;
}

// Function to check if linked list is a palindrome or not
bool isPalindrome(struct Node* head)
{
    // base cases
    if (head == NULL) //No element, empty list
        return false;
    if (head->next == NULL) //Single element list
        return true;
        
    // flag to indicate if number of nodes in the linked list is odd or not. It will be passed by reference to findMid()
    bool odd = false;

    // find second half of linked list
    struct Node* mid = findMid(head, odd);

    // if number of nodes is odd, advance mid as we'll start reversing from the node succeeding mid.
    if (odd)
        mid = mid->next;

    // reverse the second half
    reverse(&mid);

    // compare first and second half
    return compare(head, mid);
}

//T - TEST
bool test1() //empty list
{
	char elements[] = {};
    int n = sizeof(elements) / sizeof(elements[0]);
    struct Node* head = NULL;
    for (int i = 0; i < n; i++)
        insert(&head, elements[i]);

    if (isPalindrome(head)) return false;
    else return true;
}

bool test2() //Checking case sensitivity and special characters
{
	char elements[] = {'a','%','^','b','B','^','%','a'};
    int n = sizeof(elements) / sizeof(elements[0]);
    struct Node* head = NULL;
    for (int i = 0; i < n; i++)
        insert(&head, elements[i]);

    if (isPalindrome(head)) return false;
    else return true;
}

bool test3() //Checking list with single node
{
	char elements[] = {'A'};
    int n = sizeof(elements) / sizeof(elements[0]);
    struct Node* head = NULL;
    for (int i = 0; i < n; i++)
        insert(&head, elements[i]);

    if (isPalindrome(head)) return true;
    else return false;
}

bool test4() //Checking list with two same nodes
{
	char elements[] = {'b','b'};
    int n = sizeof(elements) / sizeof(elements[0]);
    struct Node* head = NULL;
    for (int i = 0; i < n; i++)
        insert(&head, elements[i]);

    if (isPalindrome(head)) return true;
    else return false;
}

int main()
{
    // input elements
    char elements[] = { 'a','%', 'c', 'c', '%','a'};
    int n = sizeof(elements) / sizeof(elements[0]);
    struct Node* head = NULL;
    for (int i = 0; i < n; i++)
        insert(&head, elements[i]);

    if (isPalindrome(head))
        cout << "TRUE";
    else
        cout << "FALSE";
    if( test1() && test2() && test3() && test4())
    	cout<<"\nAll test cases passed!";
    else cout<<"\nOne or more test cases failed!";
    return 0;
}
