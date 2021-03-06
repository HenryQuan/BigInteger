/* testBigInteger.c
 * by Yiheng Quan 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

void testBigInteger();
void testPrint();
void testAdd();
void Q13();
void Q16();
void testMultiply();

int main(int argc, char *argv[]) {
	
	testBigInteger();
	//Q13();
	Q16();
	return 0;
	
}

void Q13() {
	
	printf("Testing Project Euler Q13.\n");
	char line[100];
	FILE *fp = fopen("Q13.txt", "r");
	
	BigInteger result = newInteger("0", POSITIVE);
	while (fgets(line, sizeof(line), fp)) {
		//printf("%s\n",line);
        result = add(result, newInteger(line, POSITIVE));
    }
	printInteger(result);
	fclose(fp);
}

void Q16() {
	printf("Testing Q16\n");
	BigInteger result = newInteger("1", POSITIVE);
	int i;
	for (i = 0; i < 1000; i++) {
		BigInteger temp = newInteger("2", POSITIVE);
		result = multiply(temp, result);
	}
	printf("2^1000 = ");
	printInteger(result);
	calSumOfDigit(result);
}

void testBigInteger() {
	//testPrint();
	//testAdd();
	testMultiply();
}

void testPrint() {
	printf("Testing print\n");
	BigInteger integer = newInteger("2134691236498134124125436", NEGATIVE);
	printInteger(integer);
}

void testAdd() {
	printf("Testing Addition\n");
	BigInteger one = newInteger("812423534643534244128124235348124235346435342441242353464353424412423534643534244124235346435342464353424412423534643534244124235346435342441242353464353424423534643534244124235346435342441242353464353424", NEGATIVE);
	BigInteger two = newInteger("543657346342342381242353464353424412423534643534244124235346435342441242353464353424441242353464353424412812423534643534244124235346435342441242353464353424412423534643534244235346435342441242353464353424", NEGATIVE);
	BigInteger three = add(one, two);
	printInteger(three);
	BigInteger one1 = newInteger("21433547699123712475632", NEGATIVE);
	BigInteger two1 = newInteger("564378578432", NEGATIVE);
	BigInteger three1 = add(one1, two1);
	printInteger(three1);
	BigInteger one2 = newInteger("432543245325768", NEGATIVE);
	BigInteger two2 = newInteger("4897456148674865146857", NEGATIVE);
	BigInteger three2 = add(one2, two2);
	printInteger(three2);
}

void testMultiply() {
	printf("Testing Multiply\n");
	BigInteger one = newInteger("3254132", NEGATIVE);
	BigInteger two = newInteger("1231241", NEGATIVE);
	BigInteger three = multiply(one, two);
	printInteger(three);
}