/*  ***LOOK TO LINKEQUEUE FOR MORE SPECIFIC COMMENTS
Emily Huynh, 2001393103, CS 202 Assignment 11 ** FINAL ASSIGNMENT** section 1001
input: N/a
output: implementing a stack using linked nodes
*/
#ifndef LINKEDSTACK
#define LINKEDSTACK
#include <iostream>
using namespace std;

template <class myType>
struct nodeType
{
    myType info;
    nodeType<myType> *link;
};

template <class myType>
class linkedStack
{
    private:
        nodeType<myType> *stackTop;
        int count;
        myType rSum(nodeType<myType> *) const;
        void copyStack(const linkedStack<myType>&);

    public:
        bool operator == (const linkedStack<myType>&);
        bool operator != (const linkedStack<myType>&);
        linkedStack();
        linkedStack(const linkedStack<myType>&);
        ~linkedStack();
        void deleteSlack();
        bool isStackEmpty() const;
        void push(const myType&);
        myType peek() const;
        myType pop();
        int stackCount() const;
        myType stackSum() const;
};

/*
Function identifier: default constructor will pointer to null and count to 0
parameters: NONE
return value: NONE
*/
template <class myType>
linkedStack<myType>::linkedStack()
{
    stackTop = 0;   //0 is equivalent to nullptr i think /7/16/2020 comment
    count = 0;
}

/*
Function identifier: copy constructor will deep copy values, 
    ensures the pointer is empty first from 
    object passed in to the current object that called it using function
    copyStack();
parameters: object of the same type
return value: indirectly returns the current object with newly set values
*/
template <class myType>
linkedStack<myType>::linkedStack(const linkedStack<myType>& other)
{
    stackTop = nullptr;
    copyStack(other);
}

/*
Function identifier: performs a deep copy from the object passed in
parameters: object of the same type
return value: indirectly returns the current object with newly set values
*/
template <class myType>
void linkedStack<myType>::copyStack(const linkedStack<myType>& otherStack)
{
    nodeType<myType> *newNode, *current, *last;

    //no checking to ensure that curernt stackTop is empty?
    if(stackTop != nullptr) //if the stack is not empty, then empty the stack here
    {
        nodeType<myType> *temp; //used to delete

        while(stackTop != nullptr)  //walking thru the stack
        {
            temp = stackTop;
            stackTop = stackTop -> link;
            delete temp;
        }
    }

    //no checking to ensure that their stackTop is not empty?
    if(otherStack.stackTop == nullptr)  //if the stack to be copied is null/empty
        stackTop = nullptr;             //the curent stack will be as well

    current = otherStack.stackTop;  //starting point of the stack

    //creating the node
    stackTop = new nodeType<myType>;    //must allocate in copy construtor

    //stacks are last in first out, so current points to the passed stack
        //and stackTop  will point to a newNode and copy the information from
        //the passed stack, especially the first one for the line below
    stackTop -> info = current -> info; //copy the information of obj passed in
    stackTop -> link = nullptr;

    last = stackTop;    //last represents a pointer to the last node

    //current is set the value that current was pointing at's link
        //intention here is to move to the next link
    current = current -> link;  //set the current to point to the next node how???

    while(current != nullptr)   //loop craete newNodes as current is not null, meaning
    {                               //the stack that was passed in is not empty yet
                                    //b/c current points to the passedIn obj's stack
        newNode = new nodeType<myType>; //creation of a new node
        newNode -> info = current -> info;  //setting the information

        //null b/c is it doesn't get set right in his loop, it gets set the
            //the next time around
        newNode -> link = nullptr;  //why is it null??  

        last -> link = newNode; //newly added to the stack hence last added

        current = current -> link;     //set current to point to the next node in the
                                            //passed obj's stack
    }

}

/*
Function identifier: destructor, traverse thru the queue and delete the node
    then nullify the pointers, pointing to the node
parameters: N/A
return value: no memory leaks
*/
template <class myType>
linkedStack<myType>::~linkedStack()
{
    if(stackTop != nullptr) //traverse though the stack since it exists as stackTop is not empty/not null
    {                          // and delete all memory allocated
                                //even though the memory wasn't allocated here but was 
                                //allocated in the obj
        nodeType<myType> *temp;

        while(stackTop != nullptr)  //stackTop becomes null eventually bc all of its links will be 'deleted'
        {
            temp = stackTop;
            stackTop = stackTop -> link;
            delete temp;
        }
    }
    else
        return;
}

/*
Function identifier: checks to see if stack is empty, if the pointer that should
    be pointing to the first node is empty, the queue will be considered empty
    and return true, else it'll be return false
parameters: n/a
return value: true or false
*/
template <class myType>
bool linkedStack<myType>::isStackEmpty() const
{
    if(stackTop == nullptr)
        return true;    //stack is empty
    else
    {
        return false;   //stack is not empty
    }
}

/*
Function identifier: creation of new nodes to add into the stack
parameters: value to be set to the info part of the newNode, and add that node into the 
    queue
return value: n/a
*/
template <class myType>
void linkedStack<myType>::push(const myType& obj)
{
    //cout << "push" << endl;
    nodeType<myType> *newNode;      //creating a new node

    newNode = new nodeType<myType>; //allocation memory for it

    newNode -> info = obj;  //assigning info to value passed in
    //xcout << "newNode -> info: " << newNode -> info << endl;
    newNode -> link = stackTop; //link was whatever stackTop pointed at

    stackTop = newNode; //stackTop now points at newNode, newly added to stack

    count++;
    return;
}

/*
Function identifier: return the value that is at the top of the stack if the stack exists
parameters: n/a
return value: value at the top of the stack of type myType
*/
template <class myType>
myType linkedStack<myType>::peek() const
{
    if(stackTop == nullptr)
    {
        cout << "Error: Stack is empty." << endl;
        return 0;
    }
    else
        return stackTop -> info;
}

/*
Function identifier: remove a "node" or value in the stack that has been in the stack the shortest
    (stacks are first in first out) and 'popping' deletes the most recent thing in the stack
parameters: n/a
return value: returns the value that was popped off if there is something in the stack to begin with
*/
template <class myType>
myType linkedStack<myType>::pop()
{
    nodeType<myType> *temp;
    myType valueReturn = {};

    if(stackTop != nullptr)
    {
        temp = stackTop;
        valueReturn = stackTop -> info;
        stackTop = stackTop -> link;
        delete temp;
    }
    else
        cout << "Stack is empty." << endl;

    count--;

    //return the top item from the stack
    return valueReturn;
}

/*
Function identifier: used to return the counter variable which holds the amt of items
    in the stack
parameters: n/a
return value: integer type, counter value
*/
template <class myType>
int linkedStack<myType>::stackCount() const
{
    return count;
}

/*
Function identifier: calls the recursive sum function to add up all the values in the stack
parameters: n/a
return value: the sum of all the values in the stack
*/
template <class myType>
myType linkedStack<myType>::stackSum() const
{
    rSum(stackTop);
}

/*
Function identifier: gets called by stackSum(), recursively adds up all the values in the stack
    only gets stop if the if hits a null top ptr or if it's the end of the list, else recursively
    call the function and return it
parameters: n/a
return value: integer type, counter value
*/
template <class myType>     //***FYI FOR FUTURE REF, THIS FUNCTION WAS NOT TESTED NOR USED
myType linkedStack<myType>::rSum(nodeType<myType> *top) const
{
    myType sum = {};
    //assuming pointer passed is by default passby value
    if(top == nullptr)
        return 0;
    if(top-> link == nullptr)
        return top -> info;
    else
    {
        sum = top -> info;
        return sum += rsum(top->link);
    }
    
}

/*
Function identifier: will traverse through the current stack and the passed stack and compare
    them, if any are different the bool var will be set to false and then false will be returned
parameters: obj of the same myType
return value: returns true if the two objs are equal else returns false
*/
template <class myType>
bool linkedStack<myType>::operator == (const linkedStack<myType> & passed)
{
    bool equal = true;
    //walk through the nodes and compare
    while(stackTop != nullptr && passed.stackTop != nullptr)    //if one of these conditions fail loop will end
    {
        if(stackTop -> info != passed.stackTop -> info) //if they are different, equal will be false, 
        {               
            equal = false;      //then immediately returned, b/c if one is false, then the whole thing is false
            return equal;
        }
        else
        {
            stackTop = stackTop -> link;    //else cont traversing thru the list
        }
    }
    return equal;
}

/*
Function identifier: will traverse through the current stack and the passed stack and compare
    them, if any are different the bool var will be set to true and then true will be returned
parameters: obj of the same myType
return value: returns true if the two objs are false else returns true
*/
template <class myType>
bool linkedStack<myType>::operator != (const linkedStack<myType> & passed)
{
    bool equal = false;
    //walk through the nodes and compare
    while(stackTop != nullptr && passed.stackTop != nullptr)
    {
        if(stackTop -> info != passed.stackTop -> info)
        {
            equal = true;
            return equal;
        }
        else
        {
            stackTop = stackTop -> link;
        }
        
    }
    return equal;
}
#endif
