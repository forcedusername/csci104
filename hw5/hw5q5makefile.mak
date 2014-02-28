# Name: Ani Ramchandran
# stacker_implementation makefile

CC = g++
CFLAGS = -g -Wall -Ilib/ -I.
LDFLAGS =

all : speed_test.o
	@echo "Building speed_test"
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) speed_test.o -o speed_test

stacker_implementation.o : speed_test.cpp
	$(CC) $(CFLAGS) -c speed_test.cpp -o speed_test.o

clean:
	rm -f speed_test*.o *~
