/*
*	proj5Main.cpp
*	A program that transforms an infix expression to postfix expression and evaluates it 
*
****************************************/
#include "proj5.h"

//prints the commands
void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

// checks if a char is an opening symbol
bool isOpeningSymbol(char c) {
     if(c == '{' ||
        c == '(' || 
        c == '[' || 
        c == '<' ) {
          return true;      
     }
     else {
          return false;
     }       
}

// checks if a char is an closing symbol
bool isClosingSymbol(char c) {
     if(c == '}' || 
        c == ')' ||
        c == ']' ||
        c == '>') {
          return true;      
     }
     else {
          return false;
     }       
}

// checks if a char is an math operator
bool isMathOperator(char ch) {
	if ( ('+' == ch) || ('-' == ch) || ('*' == ch) || ('/' == ch) ) {
      	return true;
	}
	else {
		return false;
	}
}

// pops and evaluates elemnts in the stacks
void popAndEval(stackVal* sVal, stackOp* sOp) {

	char oper = top(*sOp);
	pop(sOp);
	int val2 = top(*sVal);
	pop(sVal);
	int val1 = top(*sVal);
	pop(sVal);
	int val3;
	
	if('+' == oper) {
		val3 = val1 + val2;
		push(sVal, val3);
	}
	else if('-' == oper) {
		val3 = val1 - val2;
		push(sVal, val3);
	}
	else if('*' == oper) {
		val3 = val1 * val2;
		push(sVal, val3);
	}
	else if('/' == oper) {
		val3 = val1 / val2;
		push(sVal, val3);
	}

}

// processes the translation and evaluation of infix expressions
void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
	stackVal sVal;
	stackOp sOp;
	sVal.init();
	sOp.init();
	
 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
    	if(debugMode) {
	    	printf ("Val: %d, ", inputToken.getValue() );                                        
	    } 

       // add code to perform this operation here
       push(&sVal, inputToken.getValue());

      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
      	char oper = inputToken.getOperator();
       /* make this a debugMode statement */
       if(debugMode) {
	    	printf ("OP: %c, ", oper );                                        
	    }
       

       // add code to perform this operation here
	   //If opening paranthysis
	   if(isOpeningSymbol(oper)) {
			//push
	   		push(&sOp, oper);
	   }
	   //If + or -
	   if(oper == '+' || oper == '-') {
	   		//while not empty && top is + - * /
	   		while(!isEmpty(sOp) && isMathOperator(top(sOp))) {
	   			//popAndEval
	   			popAndEval(&sVal, &sOp);
			}
	   			
	   		//push the current operator to the stack
	   		push(&sOp, oper);
	   }
	   //if * or /
		if(oper == '*' || oper == '/') {
	   		//while not empty && top is * /
	   		while(!isEmpty(sOp) && (top(sOp) == '*' || top(sOp) == '/')) {
	   			//popAndEval
				popAndEval(&sVal, &sOp);   	
			}
	   		//push the current operator to the stack
	   		push(&sOp, oper);
	   }
	   //if closing paranythsis
		if(isClosingSymbol(oper)) {
	   		//while not empty && top isn't an opening
	   		while(!isEmpty(sOp) && !isOpeningSymbol(top(sOp))) {
	   			//popAndEval
	   			popAndEval(&sVal, &sOp);
			}	
	   		//if empty
	   		if(isEmpty(sOp)) {
	   			//print error
	   			printf("error: stack is empty, but a closing symbol was found");
			}
	   		//else
	   		else {
	   			//push the current operator to the stack
	   			if(isOpeningSymbol(top(sOp))) {
	   				pop(&sOp);	
				}
				//push(&sOp, oper);  	
			}
	   }
      }

    /* get next token from input */
    inputToken = tr->getNextToken ();
   }

 /* The expression has reached its end */
 // add code to perform this operation here 
 //while stack isn't empty
 while(!isEmpty(sOp)) {
 	//popAndEval
 	popAndEval(&sVal, &sOp);
 }
 //print the end value
 printf("End value is %d", top(sVal));
 //if the stack is empty, print an error 
 if(!isEmpty(sVal)) {
 	pop(&sVal);
 }
 else {
 	printf("error: the valeu stack is empty and can't be popped");
 }
 	
 reset(&sVal);
 reset(&sOp);
 printf ("\n");
}


int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */

	//Setup debugMode
	debugMode = false;
	int i;
    for(i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-d") == 0) {
            debugMode = true;
			printf ("Debug Mode is ON\n");
        }
    }

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}
