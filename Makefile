compile: TreeDr.cpp TreeType.cpp QueType.cpp
	g++ -Wall -pedantic-errors -std=c++14 -g -o0 -o QueType.o -c QueType.cpp
	g++ -Wall -pedantic-errors -std=c++14 -g -o0 -o TreeType.o -c TreeType.cpp
	g++ -Wall -pedantic-errors -std=c++14 -g -o0 -o TreeDr.o -c TreeDr.cpp

main: TreeType.o TreeDr.o QueType.o
	g++ -Wall -pedantic-errors -std=c++14 -g -o0 -o main TreeType.o TreeDr.o QueType.o

run: main	
	./main
clean:
	rm *.o
	rm outFile.txt