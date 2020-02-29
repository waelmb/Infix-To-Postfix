/*
*	proj5.h
*	A header file for a program that transforms an infix expression to postfix expression and evaluates it 
*
****************************************/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <cstdlib>

// Global variables
static bool debugMode;

// Classes and structs
class stackVal
{
 private:
	 int*    darr;  /* pointer to dynamic array  */
	 int     allocated;  /* amount of space allocated */
	 int     inUse; /* top of stack indicator 
			   - counts how many values are on the stack   */
 public:
 	//Default constructor
 	stackVal() {
 		darr = NULL;
 		allocated = 0;
 		inUse = 0;
	 }
 	//constructor
 	void init ()
	{
		 allocated = 2;
		 darr = (int*) malloc ( sizeof (int) * allocated);
		 inUse  = 0;
	}
 	//Accessors
 	int* getDarr(){
 		return darr;
	}
	
	int getAllocated() {
		return allocated;
	}
	
	int getInUse() {
		return inUse;
	}
	
	int getElem(int i) {
		return darr[i];
	}
	
	//Modifiers
	void setDarr(int* newDarr) {
		darr = newDarr;
	}
	
	void setAllocated(int alloc) {
		allocated = alloc;
	}
	
	void setInUse(int use) {
		inUse = use;
	}
	
		void copyDarr(int* temp) {
		int i;
	    for (i = 0 ; i < inUse; i++) {
	    	darr[i] = temp[i];
		}
	}
	
	void setElem(int i, int val) {
		darr[i] = val;
	}
};

class stackOp
{
 private:
	 char*    darr;  /* pointer to dynamic array  */
	 int     allocated;  /* amount of space allocated */
	 int     inUse; /* top of stack indicator 
			   - counts how many values are on the stack   */
 public:
 	//Default constructor
 	stackOp() {
 		darr = NULL;
 		allocated = 0;
 		inUse = 0;
	 }
 	//constructor
 	void init ()
	{
		 allocated = 2;
		 darr = (char*) malloc ( sizeof (char) * allocated);
		 inUse  = 0;
	}
 	//Accessors
 	char* getDarr(){
 		return darr;
	}
	
	int getAllocated() {
		return allocated;
	}
	
	int getInUse() {
		return inUse;
	}
	
	char getElem(int i) {
		return darr[i];
	}
	
	//Modifiers
	void setDarr(char* newDarr) {
		darr = newDarr;
	}
	
	void setAllocated(int alloc) {
		allocated = alloc;
	}
	
	void setInUse(int use) {
		inUse = use;
	}
	
	void copyDarr(char* temp) {
		int i;
	    for (i = 0 ; i < inUse; i++) {
	    	darr[i] = temp[i];
		}
	}
	
	void setElem(int i, char c) {
		darr[i] = c;
	}
};

enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
};

class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }

};


// Functions
void printCommands();

void processExpression (Token inputToken, TokenReader *tr);

bool isEmpty(stackVal s);

bool isEmpty(stackOp s);

void push(stackVal* s, int c);

void push(stackOp* s, char c);

int top(stackVal s);

char top(stackOp s);

void pop(stackVal* s);

void pop(stackOp* s);

void reset(stackVal* s);

void reset(stackOp* s);

void printStack(stackVal s);

void printStack(stackOp s);

bool isOpeningSymbol(char c);

bool isClosingSymbol(char c);

bool isMathOperator(char ch);

void popAndEval(stackVal* sVal, stackOp* sOp);

