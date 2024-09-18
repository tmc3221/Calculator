/**
 @file infix.c
 @author Tristan Curtis (tmcurti4)
 Top component of our program
 Allows us to manage between our different bases and
 calculate our expressions properly
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "number.h"
#include "operation.h"

// Function prototypes
static long parse_term();
static long parse_parenthesis();
static long parse_exp();
static long parse_mul_div();

/**
  Helper method that parses for parenthesis
 @return the result of the expression
*/
static long parse_parenthesis() 
{
  // Place holder for result
  long result = 0;

  // Check for parenthesis
  char ch = skipSpace();

  if (ch == '(') {
    // Using recursion to parse the expression inside the parenthesis
    result = parse_term();

    // Check for closing parenthesis
    ch = skipSpace();
    if(ch != ')') {
      ungetc(ch, stdin);
    }

    // Consume the closing parenthesis
    ch = getchar();
  } else {
    // It's not a parenthesis, put the character back and parse the value
    ungetc(ch, stdin);

    // Check for invalid characters
    char temp = skipSpace();

    if(temp == '\\' || temp == '+' || temp == '*' || temp == '%'
      || temp == '^' || temp == '/') {
      // Invalid
      exit(FAIL_INPUT);
    } else {
      // Valid
      ungetc(temp, stdin);
    }

    // Now we can parse value
    result = parseValue();
  }

  // Return our result
  return result;
}

/**
   This allows us to parse exponentiation while
   keeping precedence
   @return the result
 */
static long parse_exp()
{
  // Get next number
  long ans = parse_parenthesis();

  // Find next operator
  char oper = skipSpace();

  // Start with higher precedence and loop until end
  while (oper == '^') {
    // Check for invlaid symbols
    if(oper == '%') {
      // Invalid Symbol
      exit(FAIL_INPUT);
    }

    // Do operation
    ans = exponentiate(ans, parse_parenthesis());

    // Check for next operator
    oper = skipSpace();

    if(oper != '^' && oper != '*' && oper != '/'
      && oper != '+' && oper != '-' && oper != '\n'
      && oper != '(' && oper != ')') {
      // Invalid Symbol
      exit(FAIL_INPUT);
    }
  }

  // Put the operator back if its not exponentiation operator
  ungetc(oper, stdin);

  // return our answer
  return ans;
}

/**
   This allows us to parse multiplication and division
   in order to keep correct precedence
   @return the result
 */
static long parse_mul_div()
{
  // Grab the first value
  long ans = parse_exp(); // Handles top precedence

  // Next operator
  char oper = skipSpace();

  // Loop to handle next precedence
  while (oper == '*' || oper == '/') {
    // Multiply current by next
    if (oper == '*') {
      ans = times(ans, parse_exp());
    } else if(oper == '/') { // Divide
      ans = divide(ans, parse_exp());
    } else if (oper != '+' && oper != '-' && oper != '^'
      && oper != '(' && oper != ')') { // Check for invalid symbol
      // Invalid operator/symbol
      exit(FAIL_INPUT);
    }
    
    // Get next operator
    oper = skipSpace();

    // Check for invlaid symbols
    if(oper == '%') {
      // Invalid Symbol
      exit(FAIL_INPUT);
    }
  }

  // Put the operator back if it is not
  // multiplication or division
  ungetc(oper, stdin);

  // return our answer
  return ans;
}

/**
  Helper method that parses a whole line term
 @return the result of the expression
*/
static long parse_term() 
{
  long result = parse_mul_div();

  // Find the next operator
  char oper = skipSpace();

  // Check for invalid symbols
  if(oper == '%') {
    // Invalid Symbol
    exit(FAIL_INPUT);
  }

  // Loop to handle addition and subtraction
  while (oper == '+' || oper == '-')
  {
    // Check for invlaid symbols
    if(oper == '%') {
      // Invalid Symbol
      exit(FAIL_INPUT);
    }

    if(oper != '^' && oper != '*' && oper != '/'
      && oper != '+' && oper != '-' && oper != '\n'
      && oper != '(' && oper != ')') {
      // Invalid Symbol
      exit(FAIL_INPUT);
    }

    if (oper == '+') {
      // Add result
      result = plus(result, parse_mul_div());
    } else {
      // Subtract from result
      result = minus(result, parse_mul_div());
    }

    // Get next operator
    oper = skipSpace();
  }

  // Put the operator back if it's not a plus or minus operator
  ungetc(oper, stdin);

  // Return the result
  return result;
}

/**
 Starts our program
 Takes into two arguments which let us know
 which base we are in
 @param argc this is the argument from command line
 @param argv this is an array of arguments
 @return Exit Status
*/
int main(int argc, char **argv)
{
  if (strcmp(argv[0], "./infix_10") == 0)
  {
    // Evaluate and print the expression
    printValue(parse_term());
  }
  if (strcmp(argv[0], "./infix_32") == 0)
  {
    // Evaluate and print the expression
    printValue(parse_term());
    putchar('\n');
  }
  if (strcmp(argv[0], "./infix_n") == 0)
  {
    // Use this section to change your base for infix_n. The if condition checks if the
    // filename of the executing program is infix_n. This section will be skipped for infix_10 and infix_32.
    printValue(parse_term());
    putchar('\n');
  }

  return EXIT_SUCCESS;
}