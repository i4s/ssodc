#compiler
  CC = g++

#flags
  CFLAGS = -g -Wall -pedantic

default: Divider

Divider: Daemon.o Divider.o Main.o
	$(CC) $(CFLAGS) daemon.o divider.o main.o -o Divider

Daemon.o: daemon.h daemon.cpp
	$(CC) $(CFLAGS) -c daemon.cpp

Divider.o: divider.h divider.cpp
	$(CC) $(CFLAGS) -c divider.cpp

Main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm Divider *.o