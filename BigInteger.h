/* BigInteger.h
 * by Yiheng Quan 
 */
 
#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#define POSITIVE 1
#define NEGATIVE 0

// Pointer points to bigIntegerRep
typedef struct bigInteger *BigInteger;

// Create a new Integer
BigInteger newInteger(char *number, int sign);

// Print a BigInteger
void printInteger(BigInteger number);

// Calculate the sum of digits
void calSumOfDigit(BigInteger number);

// One + Two
BigInteger add(BigInteger one, BigInteger two);

// One - Two
BigInteger subtract(BigInteger one, BigInteger two);

// One * Two
BigInteger multiply(BigInteger one, BigInteger two);

// One / Two
BigInteger divide(BigInteger one, BigInteger two);

// One % Two
BigInteger modulus(BigInteger one, BigInteger two);

#endif