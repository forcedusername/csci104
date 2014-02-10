# Name: Ani
# email: anirudhr@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =

all : factorial.o
	@echo "hw3 problem 1"
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) factorial.o -o factorial

factorial.o : factorial.cpp
	$(CC) $(CFLAGS) -c factorial.cpp

clean:
	rm -f factorial *.o *~