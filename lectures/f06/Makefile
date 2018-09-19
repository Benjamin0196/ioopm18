main: tree.c 
	gcc -Wall -pedantic tree.c -o main

memtest: main
	valgrind --leak-check=full ./main

clean:
	rm -f main
