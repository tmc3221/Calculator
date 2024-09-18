/**
 @file number_10.c
 @author Tristan Curtis (tmcurti4)
 This file contains the methods used in order to
 parse through and read in values for base 10
 operations
*/
#include "number.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "operation.h"
// Value of the base, so we don't have to use a magic number all over the code. You might need to change this for number_n file.
int BASE = 10;

/**
 Skips space from the input and returns the first
 non-whitespace character it sees
 @return the first non whitespace character
*/
int skipSpace()
{
    // Variable that parses through
    char ch = getchar();

    // Base case: Not a space
    if(ch != ' ') {
        return ch; // Returns first non white space char
    } 

    // Recursive Case: is a space
    return skipSpace();
}

/**
 Parses a value from the input stream
 @return parsed value
*/
long parseValue()
{
    // Skip blank space first
    char ch = skipSpace();

    // Sets the initial sign to positive
    int sign = 1;

    // Checks that there was not a negative number
    if (ch == '-')
    {
        // Switch to negative
        sign = -1;
    }
    else
    {
        // Put the char back into input
        ungetc(ch, stdin);
    }

    // ch will now be a numeric value
    ch = getchar();

    // Checks for valid input
    if (ch < BEG_BOUND || ch > END_BOUND)
    {
        exit(FAIL_INPUT); // Invalid
    }

    // Stores the values that we parse
    // This will help us parse the complete value
    long finalValue = 0;
    long currentValue = 0;

    // Loops through the whole number
    // This allows us to convert from char to int
    while (ch <= END_BOUND && ch >= BEG_BOUND)
    {
        // char to int
        currentValue = ch - BEG_BOUND;

        // Base 10 so we multiply by 10
        finalValue *= BASE;

        // Add the next digit
        finalValue += sign * currentValue;

        // Gets the next character to add
        ch = getchar();
    }

    // Put the character back into the input stream
    ungetc(ch, stdin);

    // Return the final parsed value
    return finalValue;
}

/**
 Prints the specified value
 @param val this is the value we will print
*/
void printValue(long val)
{
    // Print the parameter val
    printf("%ld\n", val);
}
