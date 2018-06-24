LDFLAGS="-L/opt/local/lib/"
CFLAGS="-I/opt/local/include"

all: main

main: main.o  userinter.o handle.o getinfo.o utils.o read.o
	g++ -o main main.o userinter.o handle.o getinfo.o utils.o read.o $(CFLAGS) $(LDFLAGS)  -lboost_regex

main.o: main.cpp	
	g++ -c main.cpp -o main.o -I/opt/local/include/

userinter.o: userinter.cpp
	g++ -c userinter.cpp -o userinter.o -I/opt/local/include/

handle.o: handle.cpp handle.h operators.h
	g++ -c handle.cpp -o handle.o -I/opt/local/include/

getinfo.o: getinfo.cpp
	g++ -c getinfo.cpp -o getinfo.o -I/opt/local/include/

utils.o: utils.cpp utils.h
	g++ -c utils.cpp -o utils.o

read.o: read.cpp read.h
	g++ -c read.cpp -o read.o

test: test.o read.o utils.o getinfo.o handle.o
	g++ -o test test.o read.o utils.o getinfo.o handle_dependencies.o $(CFLAGS) $(LDFLAGS) -lboost_regex

test.o: test.cpp
	g++ -c test.cpp -o test.o

clean:
	rm -rf test.o main.o userinter.o handle.o getinfo.o utils.o read.o main test
