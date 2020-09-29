/*
Emily Huynh, 2001393103, CS 202 Assignment 11 ** FINAL ASSIGNMENT** section 1001
input: N/a
output: implementing a queue using linked nodes
*/
#ifndef LINKEDQUEUE
#define LINKEDQUEUE
#include <iostream>
using namespace std;

template <class Type>
struct queueNode
{
    Type info;
    queueNode<Type> *link;
};

template <class Type>
class linkedQueue
{
    private:
        queueNode<Type> *queueFront;
        queueNode<Type> *queueRear;
        int count;

        void copyQueue(const linkedQueue<Type>& otherQueue);

    public:
        linkedQueue<Type>& operator = (const linkedQueue<Type>&);
        linkedQueue();
        linkedQueue(const linkedQueue<Type>& otherQueue);
        ~linkedQueue();
        bool isEmptyQueue() const;
        void initializeQueue();
        void enqueue(const Type& newItem);
        Type front() const;
        Type back() const;
        Type dequeue();
        int queueCount();
        void printQueue();
};

/*
Function identifier: default constructor will pointers to null and count to 0
parameters: NONE
return value: NONE
*/
template <class Type>
linkedQueue<Type>::linkedQueue()
{
    queueFront = nullptr;
    queueRear = nullptr;
    count = 0;
}

/*
Function identifier: copy constructor will deep copy values from 
    object passed in to the current object that called it using function
    copyQueue();
parameters: object of the same type
return value: indirectly returns the current object with newly set values
*/
template <class Type>
linkedQueue<Type>::linkedQueue(const linkedQueue<Type>& other)
{
    //cout << "copy constructor" << endl;
    queueFront = nullptr;
    queueRear = nullptr;
    count = 0;

    initializeQueue();
    copyQueue(other);
    
}

/*
Function identifier: performs a deep copy from the object passed in
parameters: object of the same type
return value: indirectly returns the current object with newly set values
*/
template <class Type>
void linkedQueue<Type>::copyQueue(const linkedQueue<Type>& otherQ)
{
    
    queueNode<Type> *newNode, *current;

    //no checking to ensure that curernt stackTop is empty?
    if(queueFront != nullptr)   //checking to make sure the queue is empty, and if not empty it
    {
        initializeQueue();
    }

    //no checking to ensure that their stackTop is not empty?
    if(otherQ.queueFront == nullptr)    //if the passed in queue is empty, then current queue will be empty too
    {
        queueFront = nullptr;
        return;
    }
        
    current = otherQ.queueFront;    //current will traverse thru the queue

    //creating the node
    queueFront = new queueNode<Type>;    //must allocate in copy construtor
    
    //copy the information of obj passed in
    queueFront -> info = current -> info; //setting the very first node to the value of the first node in the passed in obj
    queueFront -> link = nullptr;
    count++;

    queueRear = queueFront;

    //set current equal to whatever current -> link is 
    //set current equal to current's address's link
    current = current -> link;  //set the current to point to the next node how???

    while(current != nullptr)   //current is pointed towards the beginning of queue to be copied
    {                                   //keeps traversing thru until current hits null (which is the end of the queue)
        newNode = new queueNode<Type>;  //creation of new node so much allocate memory
        newNode -> info = current -> info;   //copying to the info current is pointing to, to the newNode's info
        newNode -> link = nullptr;  //why is it null?? --- b/c it will be changed later *
        
        //newly added to the stack hence last added ****
        queueRear -> link = newNode; //queueRear's prev link will now point to the newly created node****
        queueRear = newNode;    //now queueRear points to the newNode

        current = current -> link;     //set current to point to the next node, traverse to the next one
        count++;    //increment the count of words
    }
}

/*
Function identifier: destructor, traverse thru the queue and delete the node
    then nullify the pointers, pointing to the node
parameters: N/A
return value: no memory leaks
*/
template <class Type>
linkedQueue<Type>::~linkedQueue()
{
    count = 0;
    while(queueFront != nullptr)
    {
        queueNode<Type> *temp;
        temp = queueFront; 
        queueFront = queueFront -> link;
            //if(queueFront == queueRear)
        delete temp;
    }
    //no need to delete that all the memory allocate for the node have been deleted above
        //all that's left to do is to reset the pointer, so it's not pointing to some random
        //memory address
    queueFront = nullptr;
    queueRear = nullptr;
}

/*
Function identifier: function is to delete the queue nodes, so the queue will be empty
    and the nodes will not point at anything
parameters: N/A
return value: n/a
*/
template <class Type>
void linkedQueue<Type>::initializeQueue()
{
    queueNode<Type> *temp;

    while(queueFront != nullptr)
    {
        temp = queueFront;
        queueFront = queueFront -> link;
        delete temp;
    }
    queueRear = nullptr;
}

/*
Function identifier: checks to see if queue is empty, if the pointer that should
    be pointing to the first node is empty, the queue will be considered empty
    and return true, else it'll be return false
parameters: n/a
return value: true or false
*/
template <class Type>
bool linkedQueue<Type>::isEmptyQueue() const
{
    if(queueFront == nullptr)
        return true;
    else 
        return false;
}

/*
Function identifier: creation of new nodes to add into the queue
parameters: value to be set to the info part of the newNode, and add that node into the 
    queue
return value: n/a
*/
template <class Type>
void linkedQueue<Type>::enqueue(const Type& newItem)
{
    //cout << "value inputted: " << newItem << endl;
    queueNode<Type> *newNode;   //creation of newNode to add into the queue
    newNode = new queueNode<Type>;  //memory allocation for that newNode

    newNode -> info = newItem;  //setting the value passed in, to the newNode's info
    newNode -> link = nullptr;

    if(queueFront == nullptr)
    {
        queueFront = newNode;
        queueRear = newNode;
        //cout << "QUEUEFRONT -> " << endl;
    }
    else
    {
        //queueRear will be pointing to the last node enqueued
        //so the queueRear's link(the last node) will be pointed to the newNode
        queueRear -> link = newNode;    //where linking the list happens

        queueRear = queueRear -> link;  //queueRear will now look at the next node's 
        //cout << "enqueueing..." << endl;
    }
    //delete newNode;
    count++;    //increment the amount of nodes in the queue
}

/*
Function identifier: creturns the value the frontQueue pointer is pointing to, if it's pointing
    to something
parameters: n/a
return value: {} or a value of type Type
*/
template <class Type>
Type linkedQueue<Type>::front() const
{
    if(queueFront != nullptr)
        return queueFront->info;
    else
    {
        return {};
    }
    
}

/*
Function identifier: creturns the value the rearQueue pointer is pointing to, if it's pointing
    to something
parameters: n/a
return value: {} or a value of type Type
*/
template <class Type>
Type linkedQueue<Type>::back() const
{
    if(queueFront != nullptr)
        return queueRear->info; 
    else
        return {};
}

/*
Function identifier: remove a "node" or value in the queue that has been in the queue the longest
    (queues are first in first out structured) and enqueueing adds to the end of the queue
    so the whatever is at the front of the queue will get removed
parameters: n/a
return value: returns the value that was dequeued if there is something in the queue to begin with
*/
template <class Type>
Type linkedQueue<Type>::dequeue()
{
    queueNode<Type> *temp;
    Type valueReturn = {};

    if(queueFront != nullptr)
    {
        //cout << "queue is not empty." << endl;
        temp = queueFront;
        valueReturn = temp -> info;
        queueFront = queueFront -> link;
        delete temp;

        if(queueFront == nullptr)
        {
            //cout << "queue is now empty" << endl;
            queueRear = nullptr;
        }
    }
    /*else
    {
        cout << "Queue is empty." << endl;
    }*/
    //cout << "returns : " << queueFront -> info << endl;
    count--;
    return valueReturn;
}

/*
Function identifier: overloading the assignment operator =, if the obj being passed in
    is already equal, then just return the pointer to that obj, else call copy queue and deep copy
    the queue, then return the pointer to the current object calling the operator overloader
parameters: obj of the same type passed in by passby reference(the address of the obj memory itself 
    so when it's changed, the obj passed in can also be changed)
return value: *this pointer
*/
template <class Type>
linkedQueue<Type>& linkedQueue<Type>::operator = (const linkedQueue<Type>& passedIn)
{
    if(this == &passedIn)
        return *this;
    else
    {
        copyQueue(passedIn);
        return *this;
    }
}

/*
Function identifier: traversing through the queue, and printout the 'info' it holds in each node
parameters: n/a
return value: n/a
*/
template <class Type>
void linkedQueue<Type>::printQueue()
{
    queueNode<Type> *tempFront = queueFront;    //temp pointer, initialize the the value the queueFront is pointed at
                                                    //used to traverse through the queue
    //print the elements of the queue
    while(tempFront != nullptr)
    {
        //cout << "tempFront info = " << tempFront -> info << endl;
        cout << tempFront -> info << " ";
        tempFront = tempFront -> link;  //traverse thru to the next pointer
    }
}

/*
Function identifier: used to return the counter variable which holds the amt of items
    in the queue
parameters: n/a
return value: integer type, counter value
*/
template <class Type>
int linkedQueue<Type>::queueCount()
{
    return count;
}

#endif