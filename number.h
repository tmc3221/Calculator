/** Exit status indicating that the program was given invalid input. */
#define FAIL_INPUT 102

/** Low bound for number input */
#define BEG_BOUND '0'

/** High bound for number input */
#define END_BOUND '9'

/** The low bound for the letter */
#define BEG_ALP 'A'

/** The high bound for the letter */
#define END_ALP 'V'

/**
 Skips space from the input and returns the first
 non-whitespace character it sees
 @return the first non whitespace character
*/
int skipSpace();

/**
 Parses a value from the input stream
 @return parsed value
*/
long parseValue();

/**
 Prints the specified value
 @param val this is the value we will print
*/
void printValue(long val);