#compiler
  CPP = g++

#flags
  CFLAGS = -g -Wall -pedantic
  PQXXFLAGS = -lpqxx -lpq

default: main

main: base_sql_connection.o main.o
	$(CPP) $(CFLAGS) base_sql_connection.o main.o -o main $(PQXXFLAGS)

base_dbconnection.o: base_sql_connection.hpp base_sql_connection.cpp
	$(CPP) $(CFLAGS) -c base_sql_connection.cpp $(PQXXFLAGS)

main.o: main.cpp
	$(CPP) $(CFLAGS) -c main.cpp $(PQXXFLAGS)

clean:
	rm -rf *.o 
	rm -rf *.hpp.gch
	rm -rf main