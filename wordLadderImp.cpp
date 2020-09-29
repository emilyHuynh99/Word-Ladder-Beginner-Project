/*  ***LOOK TO LINKEQUEUE FOR MORE SPECIFIC COMMENTS
Emily Huynh, 2001393103, CS 202 Assignment 11 ** FINAL ASSIGNMENT** section 1001
input: N/a
output: using a stack and a queue to implement the a word ladder of 5 letters
*/
#include "wordLadder.h"
#include "linkedQueue.h"
#include "linkedStack.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

/*
Function identifier: default constructor will pointer to null and count to 0
parameters: NONE
return value: NONE
*/
wordLadder::wordLadder()
{
    /*
    constructor function will initialize class variables (nullptr or 0 as
    appropriate)
    */

    count = 0;
    first = nullptr;
    ladderEnd = nullptr;
}

/*
Function identifier: destructor, traverse thru the linked lsit and delete the nodes
    then nullify the pointers, pointing to the node
parameters: N/A
return value: no memory leaks
*/
wordLadder::~wordLadder()
{
    /*
    destructor function should free any allocated memory
    for both the ladder and the dictionary.
    */
    if(first != nullptr)
    {
        wordNode *temp;

        while(first != nullptr)
        {
            temp = first;
            first = first -> link;
            delete temp;
        }
    }

    first = nullptr;
    ladderEnd = nullptr;
    count = 0;
}

/*
Function identifier: \read in the words from a .dat file into a linked lsit
    function will use the insertWord() to insert each other and connect them in 
    linked list manner
parameters: N/A
return value: true if the file can be read and opened, false if not
*/
bool wordLadder::readDictionary(const char* filename)
{
    /*
     function should attempt to open and read the passed
    dictionary file name. The file open, read, and close operations should be performed
    within a try block. If there are any file I/O errors should, a false should be returned. 
    */
   ifstream iFile;

   try
   {
       iFile.open(filename);    //attempting to open the file
       
       if(!iFile.is_open()) //if file is unable to be opened, something will the thrown
        {  
            throw 0;
        }
   }
   catch(int zero)  //if something is thrown, the catch block will catch
   {
       cout << "File cannot be accessed." << endl;
       iFile.close();       //because file cannot be open, or some other cases, close just in case
       return false;        //and immediately return false
   }

    string word = "";   //variable that each word will be read into
    
    while(!iFile.eof()) //keep going until the end of file
    {
        iFile >> word;  
            //the last word in the file in a way holds the end bit
                // so u still must check for that after the loop condition to 
                //prevent reading in the same value/word twice
            if(iFile.eof())
                break;
        insertWord(word);   //passing the word to be inserted
    }

    //print ladder for debug purpose
    /*while(wordLadder::first != nullptr) //first starts at the end of alphabet
    {
        //cout << wordLadder::first -> info << endl;
        wordLadder::first = wordLadder::first -> link;
    }*/
    return true;        //when file has sucessfully been read into a linked list
}

/*
Function identifier: this function will find a word ladder, given the beginning word (first)
    and the end word(last), with one letter differences in between them
parameters: N/A
return value: true when a ladder can be found, if a ladder cannot be found, false is returned 
*/
bool wordLadder::findLadder(const string first, const string last)
{
    //wordNode *tempFIRST = wordLadder::first;
    linkedQueue<wordNode*> queue1;  //interesting.. b/c the type is of wordNode pointer
    wordNode *startAddress = searchPtr(first);  //finding the address of where the first word is
                                                //in the linked list

    queue1.enqueue(startAddress);       //per pdf, enqueue that address

    //set the prev pointer of the node to itself to indicate thats the beginning of the word ladder
    startAddress -> prev = startAddress;    //thats how you know thats the begin word

    wordNode *returnAdd1 = nullptr; //used for my own personal function
    wordNode *returnAdd2 = nullptr; //used for my own personal function
    returnAdd2 = searchPtr(last);   //grab the address of the node that holds the string last

    //search dictionary to find all words that are one letter
        //apart from the dequeue'd word
    returnAdd1 = queue1.dequeue();  //dequeue the item from the queue
    //then use it to compare to the rest of the words in the wordLadder dictionary
    while(!letterOffEnqueue(queue1, returnAdd1, returnAdd2))    //5/10/2020, function accepts queue so that the same queue can be used in both functions, returnAdd2 
    {                                                                       //is necessary to see if the one letter off word is the word we are looking for, returnAdd1 
                                                                            //is used to cycle through the queue, and look for one letter difference words from returnAdd1
        returnAdd1 = queue1.dequeue();  //repeating the process of dequeueing and reusing to compare
        if(queue1.isEmptyQueue())   //ensure there is no infinite loop, or seg fault
        {
            //cout << "Queue empty" << endl;
            break;
        }
    }

    //if the last node in the queue holds a address that is equivalent to the address
    //that the string last sits in, then it has found a complete word ladder
    if(queue1.back() == searchPtr(last)) 
    {
        return true;
    }

    return false;
}

/*
Function identifier: point of function is to reset the prev pointers of the nodes
    to nullptr
parameters: N/A
return value: n/a
*/
void wordLadder::resetLadder()
{
    wordNode *temp = first;
    while(temp-> link != nullptr)   //traverse through the wordladder linked list/dictionary
    {
        temp-> prev = nullptr;  //set those nodes to null
        temp = temp -> link;    //move to next node
    }
}

/*
Function identifier: this function ensures that the word passed in can be found
    in the wordLadder dictionary
parameters: the string that needs to be searched for
return value: nreturns true if the word is found, false if else
*/
bool wordLadder::validWord(const string word) const
{
    bool found = false;
    wordNode *tempFirst = first;    //as to not change the value of first

    if(word.length() > 5 || word.length() < 5)  //word must be only 5 letters long
        return false;

    while(tempFirst-> link != nullptr)  //traversing through the linked list/dictionary
    {
        if(tempFirst -> info == word)   //if the info value of the node is equal to the string passed in
        {
            found = true;
            return found;   //*** early out to stop the waste of cycles
        }
        tempFirst = tempFirst-> link;   //look at the values in the next node
    }

    return found;
}

/*
Function identifier: this function will start at ladderEnd, ladderEnd will have pointed
    to the address of where the end of the word ladder value lies, the end word, that node
    that holds that value holds prev pointers that are linked in letterOffEnqueue().
    so we start with that node, and follow the prev pointers back to the begin word of the
    word ladder
parameters: N/A
return value: n/a
*/
void wordLadder::printLadder() const
{
    //cout << "printladder" << endl;
    linkedStack<string> stack1; //creating a stack obj
    //1. find the starting word in the wordLadder
    //2. look for prev pointer value that point to the word above^

    //ladderEnd should hold the address of the end word we are looking for
    //that address, which is a wordNode, has 'prev' pointers that point the one letter diff word before it and so on
    //until it hits the beginning word we were given
    wordNode *tempLend = ladderEnd; //the address where the end word of the ladder is 
                                    //since we dont want to change it

    //we are using the prev pointers in the wordNodes to find our way back to the start word
    
    //the node that holds the begin word of the ladder has it's prev ptr set to itself
    //so thats how we know that weve hit the beginning of the word ladder word
    while(tempLend -> prev != tempLend) 
    {
        //adding the word into the stack
        stack1.push(tempLend -> info);  //starting for the end word
        //cout << tempLend -> info << endl;
        
        //following the prev ptr to the next node
        tempLend = tempLend -> prev;
    }

    //when the condition for the loop above is no longer met, the next prev node will be
    // the beginnning word so you will need to insert that
    //the beginning word of the ladder into the stack so when you print the stack out 
    //it will start from the last word pushed in and go down the stack
    if(tempLend -> prev == tempLend)
        stack1.push(tempLend -> info);

    while(!stack1.isStackEmpty())   //finally we print out the stack until it's empty
    {
        cout << stack1.pop() << endl;   //pop returns the value it removed from the stack
    }
}

/*
Function identifier: compares two strings together, and counts the difference between the words
    by its letter, if the the difference is more than one, false is return, if the difference is only 
    one then true is returned
parameters: two strings that need to be compared
return value: true if the difference between the word is one letter, false is else
*/
bool wordLadder::isOneApart(const string first, const string second) const
{
    int diff = 0;   //counter for the different letters in the words

    for(int i = 0; i < 5; i++)  //only 5 letters words, strings can be similar to arrays
    {
        if(first[i] != second[i])   //if a letter differs, diff counter will be incremented
            diff++;
    }

    if(diff == 1)       //IF AND ONLY IF THE DIFF IS ONE, THEN U CAN RETURN TRUE
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

/*
Function identifier: function will insert the word into a linked list, by building the nodes
    for each word(efvery time it gets called) this function utilizes the first and ladderEnd
    ptr to insertWord a word into a linked list, the ladderEnd ptr later gets changed and will
    not be pointing to the end of the linked list but to the word that marks the end of the wordLadder
parameters: word to be inserted into the linked list
return value: n/a
*/
void wordLadder::insertWord(const string word)
{
    wordNode *firstTemp = first;

    wordNode *temp;
    temp = new wordNode;    //creation of a newNode

    temp -> info = word;    //word assignment
    temp -> prev = nullptr; //null when created
    temp -> link = nullptr; //will be change when the next node gets created if next node
                                //does not get created then link will equal null which indicates
                                //the end of the linked list
    
    if(firstTemp == nullptr)    // if the first ptr is not pointed at anything
    {
        first = temp;
        ladderEnd = temp;
    }
    else            //else if the list has already started
    {
        ladderEnd -> link = temp;
        ladderEnd = ladderEnd -> link;
    }

    //temp -> link = first;
    //first = temp;

    count++;    //word counting/counter
}

/*
Function identifier: traverses through the linked list, and searches for the wordNode's info
    that holds the string being passed in, the returns the address of the node hat holds it
parameters: string to be searched
return value: returns address of the node
*/
wordNode* wordLadder::searchPtr(const string& searchItem) const
{
    wordNode *temp = first; //as to not change the actual first

    while(temp-> link != nullptr)   // traverse through the list to find node address
    {
        if(temp-> info == searchItem)   //early out
            return temp;
        else
            temp = temp -> link;
    }
    cout << "searchPtr address: address not found. Zero returned." << endl;
    return 0;
}

/*
Function identifier: traverses through the dictionary and looks for words that are one letter different
    from the node 'point''s info, where the string/word is saved, if the word is one letter different
    then enqueue the address to that word, and also check to see if that word is the final word you are looking for
    in both cases, enqueue the word into the queue obj passed, and set the node's prev pointer to point, REF findladder()
    for more info on the parameters, enqueue all words that are one word apart from the node point's info which
    is the word, when no more are found and the end word has not been found yet then a false is returned
parameters: obj of linkedqueue passby reference so the queue1 can be changed, the main point to compare with the rest of the 
    the dictionary, and pointer to the end word
return value: true if the final word was found, false if the final word has not been found yet
*/
bool wordLadder::letterOffEnqueue(linkedQueue<wordNode*>& queue1, wordNode* point, wordNode* endPointer)
{
    //linkedQueue<wordNode*> queue2;
    wordNode *temp;
    temp = first; //this will traverse through my wordNodes

    wordNode *prevNodeAdd;  //hold onto the address passed in to save into the node's address
                            //that has been enqueue, so it can find its way back
    prevNodeAdd = point;

    bool found = false;

    //compare word to words in dictionary
    //1. traverse through the linked list
    //2. compare letter by letter, if theres only one difference, enqueue it
    //3. move temp to next node, repeat until count == 0;
    while(temp -> link != nullptr)//1.
    {
        if(isOneApart(point -> info, temp -> info))//ensures the words are one letter apart
        {
            if(endPointer -> info == temp -> info) // if it's one apart you want to check if its the same word
            {
                //cout << "fInfo: " << temp -> info << endl;
                queue1.enqueue(temp);   //this is when the final word has been found
                temp -> prev = prevNodeAdd; //it's prev node is set to point in parametrs
                ladderEnd = temp;   //imperative we set this so that we can use this to push the words
                                    //words into the stack and print them out in the proper order
                return true;
            }
            else if(temp -> prev == nullptr)    //case for when the final word has not been found yet
            {
                //cout << "tInfo: " << temp -> info << endl;
                queue1.enqueue(temp);
                temp -> prev = prevNodeAdd; //key line to link the laddr??
            }
        }

        temp = temp -> link;    //move to next node
    }
    return found;
}

