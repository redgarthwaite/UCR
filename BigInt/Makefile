# Makefile for cs 141, project 1

CXX = g++
CXXFLAGS = -g -Wall

FOBJS = BigInt.o fact.o 

BIGOJS = BigInt.o

COMPILE=$(CXX) $(CXXFLAGS)


fact: $(FOBJS)
	$(CXX) $(CXXFLAGS) $(FOBJS) -o $@
#
BigInt.o: BigInt.cc BigInt.h
	$(COMPILE) -o BigInt.o -c BigInt.cc
#
fact.o: BigInt.h 

test: bigtest.cc $(BIGOJS)
	$(COMPILE)  -o test.out bigtest.cc $(OBJS)  
#
# remove unnecessary files
clean:
	rm -rf *~ fact *.o *~ test *.out