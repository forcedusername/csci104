# Name: Ani Ramchandran
# stacker_implementation makefile

CC = g++
CFLAGS = -g -Wall -Ilib/ -I.
LDFLAGS =

all : stacker_implementation.o
	@echo "Building stacker implementation"
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) stacker_implementation.o -o stacker_implementation

stacker_implementation.o : stacker_implementation.cpp
	$(CC) $(CFLAGS) -c stacker_implementation.cpp -o stacker_implementation.o

clean:
	rm -f stacker_implementation*.o *~
