#!/bin/bash
FAIL=0

# Function to compile a program
build_program() {
  PROGRAM=$1
  echo "Building $PROGRAM"
  make $PROGRAM
  if [ $? -ne 0 ]; then
    echo "**** Compilation failed: $PROGRAM"
    FAIL=1
  fi
}

# Function to run a single test
runtest() {
  PROGRAM=$1
  TESTNO=$2
  ESTATUS=$3
  DIR=$4

  rm -f output.txt
  
  echo "Test $TESTNO: ./$PROGRAM < $DIR/input-$TESTNO.txt > output.txt"
  ./$PROGRAM < $DIR/input-$TESTNO.txt > output.txt
  STATUS=$?

  # Check exit status
  if [ $STATUS -ne $ESTATUS ]; then
      echo "**** FAILED - Expected exit status $ESTATUS, but got: $STATUS"
      FAIL=1
      return 1
  fi

  # Check output
  if ! diff -q $DIR/expected-$TESTNO.txt output.txt >/dev/null 2>&1 ; then
      echo "**** FAILED - Output did not match expected"
      FAIL=1
      return 1
  fi

  echo "PASS"
  return 0
}

# Function to run tests for a specific program
test_program() {
  PROGRAM=$1
  DIR=$2
  TESTS=$3

  build_program $PROGRAM

  if [ -x $PROGRAM ]; then
    for TEST in "${TESTS[@]}"; do
      runtest $PROGRAM $TEST
    done
  else
    echo "**** Program $PROGRAM could not be tested as it didn't compile"
    FAIL=1
  fi
}

# Tests for each program
INFIX_10_TESTS=("01 0" "02 0" "03 0" "04 0" "05 0" "06 0" "07 0" "08 0" "09 0" "10 0" "11 0" "12 100" "13 102" "14 101" "15 0" "16 100")
INFIX_32_TESTS=("01 0" "02 0" "03 0" "04 0" "05 0" "06 0" "07 0" "08 102" "09 100" "10 100" "11 102")
INFIX_N_TESTS=("01 0" "02 0" "03 100" "04 0" "05 101" "06 0" "07 0" "08 102" "09 102" "10 0")

# Clean and compile each program
echo "Running make clean"
make clean

test_program infix_10 "input-10" "${INFIX_10_TESTS[@]}"
test_program infix_32 "input-32" "${INFIX_32_TESTS[@]}"
test_program infix_n "input-n" "${INFIX_N_TESTS[@]}"

if [ $FAIL -ne 0 ]; then
  echo "**** Some tests failed"
  exit 1
else
  echo "All tests passed"
  exit 0
fi
