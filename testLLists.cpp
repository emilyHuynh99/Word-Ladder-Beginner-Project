//  Main program
//	Test stack and queue implementation

#include <iostream>
#include <fstream>
#include <string>
#include "linkedStack.h"
#include "linkedQueue.h"

using namespace std;

int main()
{
// *****************************************************************
//  Headers...

	string bars = "--------------------------------------------------";

	cout << bars << endl << "CS 202 - Assignment #11" << endl;
	cout << "Basic Testing for Stacks and Queues" << endl;


// *****************************************************************
//  Test basic queue operations.
//	Create some integer queues, add items, delete items,
//	display queues, etc...

	cout << endl << bars << endl << "Queue Operations - Integers:" << endl << endl;

	linkedQueue<int> queue0, queue1;
	linkedQueue<int> queue2, queue3;
	int	j;

	for (int i=1; i<=20; i++)
		queue0.enqueue(i);

	cout << "Queue 0:  ";
	queue0.printQueue(); 
	cout << endl << endl;

	for (int i=1; i<=20; i+=2) {
		queue1.enqueue(queue0.dequeue());
		j = queue0.dequeue();
		queue2.enqueue(j);
	}

	cout << "Queue 1 (odds): ";
	queue1.printQueue(); 
	cout << endl << endl;

	cout << "Queue 2 (evens): ";
	queue2.printQueue(); 
	cout << endl << endl;

	queue3 = queue1;

	cout << "Queue 3 (copy of odds): ";
	queue3.printQueue();
	cout << endl;

	linkedQueue<int> queue4(queue3);

	while (!queue3.isEmptyQueue())
		j = queue3.dequeue();

	cout << "Queue 3 (now empty): ";
	queue3.printQueue();
	cout << endl << endl;

	cout << "Queue 4 (copy of odds): ";
	queue4.printQueue();
	cout << endl;

	cout << "Queue 4 (count): " << queue4.queueCount();
	cout << endl;
	cout << "Queue 4 (first item): " << queue4.front();
	cout << endl;
	cout << "Queue 4 (last item): " << queue4.back();
	cout << endl;


// --------------------------------------
//  Floating point tests
//	Create some queues for floating point items.

	cout << endl << bars << endl << "Queue Operations - Floats:" << endl << endl;

	linkedQueue<double> queue5;

	for (int i=1; i<=7; i++)
		queue5.enqueue(static_cast<double>(i)+0.5);

	linkedQueue<double> queue6(queue5);
	linkedQueue<double> queue7;

	cout << "Queue 5 (floats, original): ";
	queue5.printQueue();
	cout << endl;

	cout << endl << "Queue 6 (floats, original): ";		// => queue5 original
	queue6.printQueue();
	cout << endl;

	queue7 = queue6;
	cout << endl << "Queue 7 (floats, original): ";		// => queue5 original
	queue7.printQueue();
	cout << endl;

	cout << endl << "Queue 5 (floats, modified): ";
	queue5.enqueue(queue5.dequeue());			// move three items
	queue5.enqueue(queue5.dequeue());
	queue5.enqueue(queue5.dequeue());
	queue5.printQueue();
	cout << endl;

	cout << "Queue 5 (count): " << queue5.queueCount();
	cout << endl;
	cout << "Queue 5 (first item): " << queue5.front();
	cout << endl;
	cout << "Queue 5 (last item): " << queue5.back();
	cout << endl;

	cout << endl << "Queue 6 (floats, modified): ";
	queue6.printQueue();
	cout << endl;

	cout << "Queue 6 (count): " << queue6.queueCount();
	cout << endl;
	cout << "Queue 6 (first item): " << queue6.front();
	cout << endl;
	cout << "Queue 6 (last item): " << queue6.back();
	cout << endl;


// *****************************************************************
//  Basic tests for linked stack implementation.
//	Reservse number in a list by pushing each item on stack and then poping.

	cout << endl << bars << endl << "Test Stack Operations "
				"- Reversing:" << endl << endl;

// ---------------------
//  Integers

	linkedStack<int> iStack;
	int	inums[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	int	ilen = ( sizeof(inums) / sizeof(inums[0]) );
	int	iTmp;

	linkedStack<int> iStackA;

	if (!iStack.isStackEmpty())
		cout << "Error, invalid stack." << endl;

	cout << "Original List:     ";
	for (int i=0; i<ilen; i++) {
		iStack.push(inums[i]);
		cout << inums[i] << " ";
	}

	cout << endl << "Reverse List:      ";
	for (int i=0; i<ilen; i++) {
		iTmp = iStack.pop();
		cout << iTmp << " ";
		iStackA.push(iTmp);
	}

	cout << endl << "Copy A (original): ";
	for (int i=0; i<ilen; i++)
		cout << iStackA.pop() << " ";

	cout << endl << endl;

// ---------------------
//  Doubles
//	Create some stacks for doubles.

	linkedStack<double> dstack;
	linkedStack<double> dstackA;
	
	double	dnums[] = {1.1, 3.3, 5.5, 7.7, 9.9, 11.11, 13.13, 15.15};
	int	dlen = ( sizeof(dnums) / sizeof(dnums[0]) );
	double	dTmp;

	dstack.push(1000.0);

	cout << bars << endl << "Test Stack Operations " <<
			"- Doubles:" << endl << endl;

	cout << "Original List:     ";
	for (int i=0; i<dlen; i++) {
		dstack.push(dnums[i]);
		cout << dnums[i] << " ";
	}

	cout << endl << "Reverse List:      ";
	for (int i=0; i<dlen; i++) {
		dTmp = dstack.pop();
		cout << dTmp << " ";
		dstackA.push(dTmp);
	}

	cout << endl << "Copy A (original): ";
	for (int i=0; i<dlen; i++) {
		cout << dstackA.pop() << " ";
	}

	cout << endl << endl;

// --------------------------------------
//  Multiple links testing
//	Insert 303 items, should be 4 links...

	cout << bars << endl << "Test Stack Operations " <<
			"- Multiple Links Test:" << endl << endl;

	linkedStack<short> mStack;
	int	testSize1=303;
	bool	workedStk1 = true;

	for (int i=1; i<=testSize1; i++)
		mStack.push(static_cast<short>(i+100));

	for (int i=testSize1; i>0; i--) {
		if (mStack.pop() != static_cast<short>(i+100))
			workedStk1 = false;
	}

	if (workedStk1)
		cout << "Multiple items, test passed." << endl;
	else
		cout << "Multiple items, test failed." << endl;

	cout << endl;

// --------------------------------------
//  Many entries testing

	cout << bars << endl << "Test Stack Operations " <<
			"- Many Items:" << endl << endl;
	bool	workedStk2 = true;

	linkedStack<int> iStackBig;
	int	testSize2=400000;

	for (int i=1; i<=testSize2; i++)
		iStackBig.push(i);

	for (int i=testSize2; i>0 ; i--) {
		if (iStackBig.pop() != i)
			workedStk2 = false;
	}

	if (workedStk2)
		cout << "Many items, test passed." << endl;
	else
		cout << "Many items, test failed." << endl;

	cout << endl;


// *****************************************************************
//  All done.

	cout << bars << endl << "Game Over, thank you for playing." << endl;

	return 0;
}


