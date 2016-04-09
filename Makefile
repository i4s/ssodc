#compiler
  CC = g++

#flags
  CFLAGS = -g -Wall -pedantic

default: Main

Main: Daemon.o Main.o
	$(CC) $(CFLAGS) Daemon.o main.o -o Main

Daemon.o: utils/Daemon.hpp utils/Daemon.cpp
	$(CC) $(CFLAGS) -c utils/Daemon.cpp

Main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm Main *.o