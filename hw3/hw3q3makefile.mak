# Name: Ani
# email: anirudhr@usc.edu

CC = g++
CFLAGS = -g -Wall
LDFLAGS =

all : hw3q3v2.o
	@echo "hw3 problem 3"
	@echo "Compiling and linking"
	$(CC) $(CFLAGS) hw3q3v2.o -o hw3q3v2

hw3q3v2.o : hw3q3v2.cpp
	$(CC) $(CFLAGS) -c hw3q3v2.cpp

clean:
	rm -f hw3q3v2 *.o *~