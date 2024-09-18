# Set the standard rules
CC = gcc
CFLAGS = -Wall -std=c99

# Builds all threee executables
all: infix_10 infix_32 infix_n

# This rule links infix.o and number_10.o into infix_10
infix_10: number_10.o infix.o
	gcc infix.o number_10.o operation.o -o infix_10

# This rule links infix.o and number_32.o into infix_32
infix_32: number_32.o infix.o
	gcc infix.o number_32.o operation.o -o infix_32

# This rule links infix.o and number_n.o into infix_n
infix_n: number_n.o infix.o
	gcc infix.o number_n.o operation.o -o infix_n

# This makes the infix.o object
infix.o: infix.c

# This rule makes the number_10.o file
number_10.o: operation.o number.h number_10.c

# This rule makes the number_32.o file
number_32.o: operation.o number.h number_32.c

# This rule makes the number_n.o file
number_n.o: operation.o number.h number_n.c

# This rule makes the operation.o file
operation.o: operation.c operation.h

# Cleans/deletes output files and executables
clean:
	rm -f *.o
	rm -f *output*
	rm -f infix_10 infix_25 infix_n
