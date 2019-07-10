/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
			
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: 	s is not null
	post:	
*/
int isBalanced(char* s)
{
	//If s is empty, return true
	if (s == NULL)
	{
		return 1;
	}
	
	//Create a stack to push braces, parentheses, or brackets onto
	DynArr * stack = newDynArr(2);
	
	//Variable for symbol being checked set by calling nextChar(s)
	char symbol = nextChar(s), top;

	//While loop to go through every symbol until the last placeholder
	while (symbol != '\0')
	{
		//If the stack isn't empty, set the variable top to the top of the stack
		if (!isEmptyDynArr(stack))
		{
			top = topDynArr(stack);
		}

		/* If symbol is an open brace, parentheses, or bracket 
		add the symbol to the stack */
		if (symbol == '{' || symbol == '[' || symbol == '(')
		{
			pushDynArr(stack, symbol);
		}

		/* Following if statements check if symbol is a close brace and if it matches 
		the item on the top of the stack, if so remove the top item on the stack */
		if (symbol == '}' && top == '{')
		{
			//If the stack is empty, return false
			if(isEmptyDynArr(stack))
			{
				return 0;
			}
			popDynArr(stack);
		}
	
		if (symbol == ')' && top == '(')
		{
			if(isEmptyDynArr(stack))
			{
				return 0;
			}
			popDynArr(stack);
		}

		if (symbol == ']' && top == '[')
		{
			if(isEmptyDynArr(stack))
			{
				return 0;
			}
			popDynArr(stack);
		}

		//Set symbol to the next character in the string using a call to nextChar
		symbol = nextChar(s);
	}

	//If the stack is empty, then the symbols matched and the string is balanced
	if (isEmptyDynArr(stack))
	{
		deleteDynArr(stack);
		return 1;					//return true
	}
	//Otherwise, delete the stack and return false
	else
	{
		deleteDynArr(stack);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

