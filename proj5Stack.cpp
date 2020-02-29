/*
*	proj5Stack.cpp
*	Functions that perfrom operations on stackVal and stackOp classes
*
****************************************/
#include "proj5.h"

//checks if the stack is empty
bool isEmpty(stackVal s) {
	if(s.getInUse() == 0) {
		return true;
	}
	else {
		return false;
	}
}

//checks if the stack is empty
bool isEmpty(stackOp s) {
	if(s.getInUse() == 0) {
		return true;
	}
	else {
		return false;
	}
}

//pushs an elemnt to the stack
void push(stackVal* s, int c) {
	/* check if enough space currently on stack and grow if needed */
    if(s->getInUse() == s->getAllocated()) {
	    int *temp = s->getDarr();
	    s->setAllocated(s->getAllocated() + 2);	
	    int* darr = (int*) malloc ( sizeof (int) * s->getAllocated());
		s->setDarr(darr);
	    s->copyDarr(temp); 	
	    free (temp);
 	}
 
  /* add val onto stack */
  s->setElem(s->getInUse(), c);
  s->setInUse(s->getInUse() + 1);
}

//pushs an elemnt to the stack
void push(stackOp* s, char c) {
	/* check if enough space currently on stack and grow if needed */
    if(s->getInUse() == s->getAllocated()) {
	    char *temp = s->getDarr();
	    s->setAllocated(s->getAllocated() + 2);	
	    char* darr = (char*) malloc ( sizeof (char) * s->getAllocated());
		s->setDarr(darr);
	    s->copyDarr(temp); 	
	    free (temp);
 	}
 
  /* add val onto stack */
  s->setElem(s->getInUse(), c);
  s->setInUse(s->getInUse() + 1);
}

//returns the element at the top of the stack
int top(stackVal s) {
	if(s.getInUse() == 0) {
		printf("error: stack is empty");
		return -999;
	} else {
		return s.getElem(s.getInUse() - 1);	
	}
}

//returns the element at the top of the stack
char top(stackOp s) {
	return s.getElem(s.getInUse() - 1);
}

//pops the item at the top of the stack
void pop(stackVal* s) {
	s->setInUse(s->getInUse() - 1);
}

//pops the item at the top of the stack
void pop(stackOp* s) {
	s->setInUse(s->getInUse() - 1);
}

// resets the stack
void reset(stackVal* s) {
	free(s->getDarr());
	s->setAllocated(2);
	s->setInUse(0);
}

// resets the stack
void reset(stackOp* s) {
	free(s->getDarr());
	s->setAllocated(2);
	s->setInUse(0);
}

//prints the elements of the stack
void printStack(stackVal s) {
	printf("There are %d vals\n", s.getInUse());
	for(int i = 0; i < s.getInUse(); i++) {
		printf("Val at index %d is %d\n", i, s.getElem(i));
	}
}

//prints the elements of the stack
void printStack(stackOp s) {
	printf("There are %d operators\n", s.getInUse());
	for(int i = 0; i < s.getInUse(); i++) {
		printf("Operator at index %d is %c\n", i, s.getElem(i));
	}
}

