all: rshell
//	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./rshell
//	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./bin/rshell
rshell:
	mkdir ./bin
	g++ -Wall -Werror -ansi -pedantic src/rshell.cpp -o ./bin/rshell
