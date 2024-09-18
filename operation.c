/**
 @file operation.c
 @author Tristan Curtis (tmcurti4)
 This file allows us to override typical 
 mathematical operations in order to check for
 invalid and overflow detections that may arise
*/

#include "operation.h"

#include <stdlib.h>
#include <limits.h>

/** Exit status for when an overflow occurs. */
#define FAIL_OVERFLOW 100

/** Exit status for when we try to divide by zero. */
#define FAIL_DIVZERO 101

/** Exit status for when negative exponent. */
#define FAIL_NEGEXP 103


/**
 Adds to values together while checking for potential
 overflow errors
 @param a our first value
 @param b our second value
 @return the sum of the two parameters
*/
long plus(long a, long b)
{
    // Check for overflow
    long result = a + b;

    if((a > 0 && b > 0 && result < 0) || (a < 0 && b < 0 && result > 0)) {
        exit(FAIL_OVERFLOW);
    }

    // Valid
    return a + b;
}

/**
 Subtracts our two values while also checking
 for potnetial overflow errors
 @param a our first value
 @param b our second value
 @return the difference between a and b
*/
long minus(long a, long b)
{
    // Our result
    long result = a - b;

    // Check for overflow
    if ((a > 0 && b < 0 && result < 0) || (a < 0 && b > 0 && result > 0)) {
        exit(FAIL_OVERFLOW);
    }

    // Valid
    return a - b;
}

/**
 Multiplies two values together while checking for potential
 overflow errors
 @param a our first value
 @param b our second value
 @return the product of the two parameters
*/
long times(long a, long b)
{
    // Check for zero multiplication
    if (a == 0 || b == 0) {
        return 0;
    }

    // Check for overflow based on the signs of a and b
    if (a > 0 && b > 0 && a > LONG_MAX / b) {
        exit(FAIL_OVERFLOW);
    }
    if (a < 0 && b < 0 && a < LONG_MAX / b) {
        exit(FAIL_OVERFLOW);
    }
    if (a > 0 && b < 0 && b < LONG_MIN / a) {
        exit(FAIL_OVERFLOW);
    }
    if (a < 0 && b > 0 && a < LONG_MIN / b) {
        exit(FAIL_OVERFLOW);
    }

    // Valid
    return a * b;
}

/**
 Exponentiates a number while checking for potential
 overflow errors
 @param base the base value
 @param exp the exponent value
 @return base raised to the power of exp
*/
long exponentiate(long a, long b)
{
    // Negative exponet
    if(b < 0) {
        exit(FAIL_NEGEXP);
    }

    // Holds our result
    long result = a;

    // Case: exponet is 0
    if(b == 0) {
        return (long) 1;
    }

    // Multiply b number of times
    for(long i = 0; i < b - 1; i++) {
        result = times(result, a);
    }

    // Valid
    return result;
}

/**
 Divides two values while checking for potential
 overflow errors
 @param a the dividend
 @param b the divisor
 @return the result of a divided by b
*/
long divide(long a, long b)
{
    // Check for divided by 0
    if(b == 0) {
        exit(FAIL_DIVZERO);
    }

    // Check for overflow
    if(a == LONG_MIN && b == -1) {
        exit(FAIL_OVERFLOW);
    }

    // Valid
    return a / b;
}
