/* Digit.c
 * by Yiheng Quan 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInteger.h"

typedef struct digit {
	// 0 - 9
	int number;
	// Number carries over to next calculation
	int carry;
	struct digit *next;
	struct digit *prev;
} *Digit;

struct bigInteger {
	// First digit
	Digit first;
	// Last digit
	Digit last;
	// Number of digit
	int digit;
	// The sign of number
	int sign;
};

// Create a new node
static Digit newDigit(int number) {
	
	Digit new = malloc(sizeof(struct digit));
	if (new == NULL) {
		printf("Out of memory.\n");
		exit(1);
	}
	
	// Setup new
	new -> number = number;
	new -> carry = 0;
	new -> next = NULL;
	new -> prev = NULL;
	
	return new;
	
}

static int max(int a, int b) {
	return a >= b ? a : b;
}

static int min(int a, int b) {
	return a <= b ? a : b;
}

// Add a digit
static void addDigitRight(BigInteger number, int digit) {
	
	if (number == NULL || (digit < 0 && digit > 9)) {
		printf("addDigitRight: number is not valid.\n");
		return;
	}
	
	if (number -> digit == 0) {
		// There is not digit yet
		number -> first = number -> last = newDigit(digit);
	} else {
		// Append to last
		Digit new = newDigit(digit);
		// last -> new, last <- new
		number -> last -> next = new;
		new -> prev = number -> last;
		number -> last = new;
	}
	
	number -> digit++;
	
}

static void addDigitLeft(BigInteger number, int digit) {
	
	if (number == NULL || (digit < 0 && digit > 9)) {
		printf("addDigitLeft: number is not valid.\n");
		return;
	}
	
	if (number -> digit == 0) {
		// There is not digit yet
		number -> first = number -> last = newDigit(digit);
	} else {
		// Append to last
		Digit new = newDigit(digit);
		// new -> first, new <- first
		number -> first -> prev = new;
		new -> next = number -> first;
		number -> first = new;
	}
	
	number -> digit++;
	
}

// Free
static void freeAll(BigInteger number) {
	if (number == NULL || number -> digit == 0) {
		return;
	}
	
	Digit curr = NULL;
	Digit next;
	for (curr = number -> first; curr -> next != NULL; curr = next) {
		next = curr -> next;
		free(curr);
	}
}

// Create an empty Integer
BigInteger emptyInteger(int sign) {
	
	BigInteger new = malloc(sizeof(struct bigInteger));
	if (new == NULL) {
		printf("Out of memory.\n");
		exit(1);
	} 
	
	// Setup new
	new -> digit = 0;
	new -> first = new -> last = NULL;
	new -> sign = sign;
	
	return new;
	
}

// Create a new Integer
BigInteger newInteger(char *number, int sign) {
	
	BigInteger new = malloc(sizeof(struct bigInteger));
	if (new == NULL) {
		printf("Out of memory.\n");
		exit(1);
	} else if (sign != POSITIVE && sign != NEGATIVE) {
		printf("Sign is not valid.\n");
		return NULL;
	}
	
	// Setup new
	new -> digit = 0;
	new -> first = new -> last = NULL;
	new -> sign = sign;
	
	// Add digit
	int i;
	for (i = 0; i < strlen(number); i++) {
		// If you are reading from a file
		if (number[i] == '\n') break;
		addDigitRight(new, number[i] - '0');
	}
	
	return new;
	
}

// Print a Digit
void printInteger(BigInteger number) {
	
	if (number == NULL) {
		printf("printInteger: number is not valid.\n");
		return;
	}
	
	if (number -> sign == NEGATIVE) printf("-");
	
	Digit curr;
	for (curr = number -> first; curr != NULL; curr = curr -> next) {
		printf("%d", curr -> number);
		if (curr == number -> last) printf("\n");
	}
	
}

// Add two integers
BigInteger add(BigInteger one, BigInteger two) {
	
	if (one == NULL || two == NULL) {
		printf("add: Number is not valid.\n");
		exit(1);
	}
	
	if (one -> sign == POSITIVE && two -> sign == NEGATIVE) {
		// One - Two
		return subtract(one, two);
	} else if (one -> sign == NEGATIVE && two -> sign == POSITIVE){
		// Two - One
		return subtract(two, one);
	} else {
		// One + Two | -(One + Two)
		int i;
		int needCarry = 0;
		Digit oneCurr = one -> last;
		Digit twoCurr = two -> last;
		BigInteger new = emptyInteger(one -> sign);
		int calCount = max(one -> digit, two -> digit);
		for (i = 0; i < calCount; i++) {
			int numToAdd = 0;
			// Add the number
			if (oneCurr == NULL)
				numToAdd = twoCurr -> number;
			else if (twoCurr == NULL)
				numToAdd = oneCurr -> number;
			else
				numToAdd = oneCurr -> number + twoCurr -> number;
			
			// Remove carry
			if (i > 0 && new -> first -> carry == 1) {
				numToAdd += 1;
				
				new -> first -> carry = 0;
			}
			
			if (numToAdd >= 10) {
				// Subtract by 10
				numToAdd -= 10;
				needCarry = 1;
			}
			
			addDigitLeft(new, numToAdd);
			if (needCarry == 1) new -> first -> carry = 1;
			
			if (oneCurr == NULL) oneCurr = NULL;
			else oneCurr = oneCurr -> prev;
			
			if (twoCurr == NULL) twoCurr = NULL;
			else twoCurr = twoCurr -> prev;

			// Reset it
			needCarry = 0;
		}
		
		if (new -> first -> carry == 1) {
			new -> first -> carry = 0;
			addDigitLeft(new, 1);
		}
		
		freeAll(one);
		freeAll(two);
		
		return new;
		
	}
	
}

// Subtract two integers
BigInteger subtract(BigInteger one, BigInteger two) {
	
	if (one == NULL || two == NULL) {
		printf("subtract: Number is not valid.\n");
		exit(1);
	}
	
	return emptyInteger(NEGATIVE);
}

// Multiply two integers
BigInteger multiply(BigInteger one, BigInteger two) {
	
	if (one == NULL || two == NULL) {
		printf("multiply: Number is not valid.\n");
		exit(1);
	}
	
	int i;
	
	// -1 * 1 = -1, 1 * -1 = -1, 1 * 1= 1, -1 * -1 = 1 
	BigInteger new = newInteger("0", POSITIVE);
	// Use the smallest value
	int calCount = min(one -> digit, two -> digit);
	
	BigInteger small, big;
	if (one -> digit == calCount) {
		small = one;
		big = two;
	} else {
		small = two;
		big = one;
	}
	
	BigInteger temp;
	Digit smallCurr = small -> last;
	Digit bigCurr;
	for (i = 0; i < calCount; i++) {
		temp = emptyInteger(POSITIVE);
		// Reset to last
		int numToCarry = 0;
		for (bigCurr = big -> last; bigCurr != NULL; bigCurr = bigCurr -> prev) {
			// Calculate
			int numToAdd = bigCurr -> number * smallCurr -> number;
			
			if (numToAdd >= 10) {
				numToCarry = numToAdd / 10;
				numToAdd -= numToCarry * 10;
				bigCurr -> carry = numToCarry;
			}
			// Check if there is carry
			if (bigCurr -> next != NULL && bigCurr -> next -> carry > 0) {
				numToAdd += bigCurr -> next -> carry;
				bigCurr -> next -> carry = 0;
				if (numToAdd >= 10) {
					numToCarry = numToAdd / 10;
					numToAdd -= numToCarry * 10;
					bigCurr -> carry = numToCarry;
					numToCarry = 0;
				}
			}
			addDigitLeft(temp, numToAdd);
		}
		
		if (big -> first -> carry > 0) {
			addDigitLeft(temp, big -> first -> carry);
		}
		
		int k;
		for (k = 0; k < i; k++) {
			// Shift
			addDigitRight(temp, 0);
		}
		
		// Add
		new = add(new, temp);
		smallCurr = smallCurr -> prev;
	}
	
	new -> sign = (one -> sign == two -> sign ? POSITIVE : NEGATIVE);
	return new;
	
}

// Divide two integers
BigInteger divide(BigInteger one, BigInteger two) {
	
	if (one == NULL || two == NULL) {
		printf("divide: Number is not valid.\n");
		exit(1);
	}
	return emptyInteger(NEGATIVE);
}

// One Modulus Two
BigInteger modulus(BigInteger one, BigInteger two) {
	
	if (one == NULL || two == NULL) {
		printf("modulus: Number is not valid.\n");
		exit(1);
	}
	return emptyInteger(NEGATIVE);
}

// Calculate the sum of digits
void calSumOfDigit(BigInteger number) {
	
	if (number == NULL) {
		printf("printInteger: number is not valid.\n");
		return;
	}
	
	Digit curr;
	int sum = 0;
	for (curr = number -> first; curr != NULL; curr = curr -> next) {
		sum += curr -> number;
	}
	printf("Sum of digits are %d (%d)\n", sum, number -> digit);
	
}