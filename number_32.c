/**
 @file number_32.c
 @author Tristan Curtis (tmcurti4)
 This file contains the methods used in order to
 parse through and read in values for base 32
 operations
*/

#include "number.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "operation.h"

// Value of the base, so we don't have to use a magic number all over the code. You might need to change this for number_n file.
int BASE = 32;

/** This is the shift amount */
#define SHIFT_VALUE 10

// Function Prototypes
static void printValueRecursive(long val);

/**
  Helper method that helps convert to base 32
  @param val the value we are converting
  @return the number in base 32
*/
static char convertTo32(int val)
{
  // Our char we use to convert
  char ch;

  // Start with 0-9 character
  if (val >= 0 && val <= 9) {
    // Use our bound to convert
    ch = '0' + val;
  } else { // For A-V character
    // Use shift to convert
    ch = 'A' + val - SHIFT_VALUE;
  }

  // Return our converted value
  return ch;
}

/**
  Helper method which converts from base 32 representation
  @param ch the char which we are converting
  @return base 10 value of the base 32 number
*/
static long convertFrom32(char ch)
{
  // Initialize our variable
  long val = 0;

  // 0-9 character
  if (ch >= '0' && ch <= '9') {
    val = ch - '0'; // Shift with start bound
  }

  // A-V character
  if (ch >= 'A' && ch <= 'V') {
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
  // Skip blank space first
  char ch = skipSpace();
  
  // Check for invalid letter case
  if(ch == 'W' || ch == 'X' || ch == 'Y' || ch == 'Z') {
    // Invalid
    exit(FAIL_INPUT);
  }

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

  // Stores the values that we parse
  // This will help us parse the complete value
  long finalValue = 0;
  long currentValue = 0;

  // Loops through the whole number
  // This allows us to convert from char to int
  while ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'V')) {
    // Converting from char
    currentValue = convertFrom32(ch);

    // Shift
    finalValue = times(finalValue, BASE);

    // Add val
    finalValue = plus(finalValue, sign * currentValue);

    // getting the next character
    ch = getchar();

    // Check for invalid letter case
    if(ch == 'W' || ch == 'X' || ch == 'Y' || ch == 'Z') {
      // Invalid
      exit(FAIL_INPUT);
    }
  }

  // Put the character back into the input stream
  ungetc(ch, stdin);

  // Return the final parsed value
  return finalValue;
}

/**
 Private helper funciton in our recursive pair which
 helps print the base 32 number
 @param val this is the value we will print
*/
static void printValueRecursive(long val) {
  // Recursive case: value is still larger then the base
  if (val >= BASE) {
    // This means we must divide by our base again
    printValueRecursive(val / BASE);
  }

  // Base Case: print the char from the base 32 number
  putchar(convertTo32(val % BASE));
}

/**
 Public function that using a recursive pair
 in order to print the base 32 number
 @param val the value we are printing
*/
void printValue(long val) {
  // Special Case: val is 0
  if (val == 0) {
    // Print 0 and return
    putchar('0');
    return;
  }

  // Special Case: val is the long minimum
  if (val == LONG_MIN) {
    // Add negative sign
    putchar('-');

    // Make our recursive call
    // Print negative sign
    // Now treat val as positive
    printValueRecursive(-1 * (val / BASE));
    putchar(convertTo32(-1 * (val % BASE)));
    return;
  }

  // Special Case: val is negative
  if (val < 0) {
    // Print negative sign
    putchar('-');

    // Now we treat val as positive
    val = -1 * val;
  }

  // Recursive case: print rest of val
  printValueRecursive(val);
}