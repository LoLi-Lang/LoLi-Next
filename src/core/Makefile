CFLAG=-g -Wall -Wextra -O0 -std=c++11

CC=g++

HEADERS= \
		 include/types.h

TESTS= \
	   tests/test.cpp

CORE= \
	  types.cpp

TEST: $(HEADERS)
	$(CC) $(CFLAG) $(CORE) $(TESTS) -o test
