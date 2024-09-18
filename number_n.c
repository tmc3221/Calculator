/**
 @file number_n.c
 @author Tristan Curtis (tmcurti4)
 This file contains the methods used in order to
 parse through and read in values for base n
 operations
*/

#include "number.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>
#include "operation.h"

/** This is the shift amount */
#define SHIFT_VALUE 10

/** This is the base value with a placeholder*/
int BASE = -1;

/**
  Helper method that helps convert to a user-defined base
  @param val the value we are converting
  @param base the base we are converting to
  @return the number in the user-defined base
*/
static char convertToBase(int val, int BASE)
{
    // Our char we use to convert
    char ch;

    // Start with 0-9 character
    if (val >= 0 && val <= 9) {
        // Use our bound to convert
        ch = '0' + val;
    } else { // For A-(base-1) character
        // Use shift to convert
        ch = 'A' + val - SHIFT_VALUE;
    }

    // Return our converted value
    return ch;
}

/**
  Helper method which converts from the user-defined base representation
  @param ch the char which we are converting
  @param BASE the base we are converting from
  @return base 10 value of the base n number
*/
static int convertFromBase(char ch, int BASE)
{
    // Initialize our variable
    int val = 0;

    // 0-9 character
    if (ch >= '0' && ch <= '9') {
        val = ch - '0'; // Shift with start bound
    }

    // A-(base-1) character
    if (ch >= 'A' && ch <= ('A' + BASE - 11)) {
        val = ch - 'A' + SHIFT_VALUE; // shift with shift constant
    }

    // Return our converted number
    return val;
}

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
    // Checks to make sure this is the first
    // iteration
    if(BASE == -1) {
        // Correct the base
        getchar();
        scanf("%d", &BASE);
    }

    // Check for invalid base
    if(BASE < 2) {
        exit(FAIL_INPUT);
    }

    // Skip blank space first
    char ch = skipSpace();

    // Sets the initial sign to positive
    int sign = 1;

    // Checks that there was not a negative number
    if (ch == '-')
    {
        // Switch to negative
        sign = -1;
        ch = getchar(); // Read the next character
    }/* else if (ch == '+') {
        ch = getchar(); // Read the next character
    } */

    // Check for invalid characters
    if(ch == '%' || ch == '^' || ch == '*' || ch == '('
      || ch == ')' || ch == '-' || ch == '+' || ch == '\\') {
        // Invalid
        exit(FAIL_INPUT);
    }

    // Check for invalid symbols based on base
    if (BASE == 10 && ch > '9') {
        exit(FAIL_INPUT);
    }

    // Stores the values that we parse
    // This will help us parse the complete value
    long finalValue = 0;
    long currentValue = 0;

    // Loops through the whole number
    // This allows us to convert from char to int
    while ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= ('A' + BASE - 11))) {
        // Converting from char
        currentValue = convertFromBase(ch, BASE);

        // Shift
        finalValue = times(finalValue, BASE);

        // Add val
        finalValue = plus(finalValue, sign * currentValue);

        // getting the next character
        ch = getchar();

        // Check for invalid symbols based on base
        if (BASE == 10 && ch > '9') {
          exit(FAIL_INPUT);
        }
    }

    // Put the character back into the input stream if it is not EOF
    if (ch != EOF) {
        ungetc(ch, stdin);
    }

    // Return the final parsed value
    return finalValue;
}

/**
 Prints the specified value
 @param val this is the value we will print
*/
void printValue(long val)
{
    if (val == 0) {
        // Special Case: 0
        putchar('0');
        return;
    }

    // Check for negative number
    if(val < 0) {
        // Add -
        putchar('-');

        // Set to positive
        val *= -1;
    }   

    // Recursive function to handle printing in the user-defined base
    if (val >= BASE) {
        printValue(val / BASE);
    }

    // Print the last digit/character
    putchar(convertToBase(val % BASE, BASE));
}