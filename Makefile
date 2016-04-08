#compiler
  CC = g++

#flags
  CFLAGS = -g -Wall -pedantic

default: Divider

Divider: Daemon.o Divider.o Main.o Serverconnection.o Supermq.o
	$(CC) $(CFLAGS) daemon.o divider.o main.o socketconnection.o supermq.o -o Divide

Daemon.o: utils/daemon.h utils/daemon.cpp
	$(CC) $(CFLAGS) -c utils/daemon.cpp

Divider.o: divider/divider.h divider/divider.cpp
	$(CC) $(CFLAGS) -c divider/divider.cpp

Main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Serverconnection.o: ipc/socketconnection.h ipc/socketconnection.cpp
	$(CC) $(CFLAGS) -c ipc/socketconnection.cpp

Supermq.o: ipc/supermq.h ipc/supermq.cpp
	$(CC) $(CFLAGS) -c ipc/supermq.cpp

clean:
	rm Divide *.o