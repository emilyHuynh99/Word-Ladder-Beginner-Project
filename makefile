# CS 202
# Make file for spirograph program

CC	= g++ -Wall -pedantic -Wextra -std=c++11 -g
OBJS1	= ladder.o wordLadderImp.o
OBJS2   = testLLists.o
DEPS1	= linkedQueue.h
DEPS2   = linkedStack.h
DEPS3	= wordLadder.h

all: ladder testLLists

ladder: $(OBJS1)
	$(CC) -o ladder $(OBJS1) 

ladder.o: 	ladder.cpp $(DEPS1) 
	$(CC) -c ladder.cpp

testLLists: $(OBJS2)
	$(CC) -o testLLists $(OBJS2) 

testLLists.o: testLLists.cpp $(DEPS2) $(DEPS1)
	$(CC) -c testLLists.cpp


wordLadderImp: $(OBJS1)
	$(CC) -c wordLadderImp $(DEPS3)

wordLadderImp.o: wordLadderImp.cpp $(DEPS3)
	$(CC) -c wordLadderImp.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS1) $(OBJS2)

