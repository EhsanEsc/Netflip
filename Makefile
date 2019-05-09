
CC = g++
CFLAGS = -std=c++11

a.out: main.o
	$(CC) $(CFLAGS) main.o -o a.out
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o
clean:
	rm *.o *.out
