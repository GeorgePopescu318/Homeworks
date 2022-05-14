compile: build run
valgrind: build valgrind
cppcheck: build cppcheck
build: p1.c
	 gcc p1.c -Wall -g -o compiler
run: compiler
	./compiler
valgrind: compiler
	 valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --vgdb=full --error-exitcode=1 ./compiler
cppcheck:
	 cppcheck --enable=all p1.c

