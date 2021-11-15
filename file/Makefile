.PHONY:clean 
test:main.o
	gcc -Wall -g -pthread main.o -o test
main.o:main.c
	gcc -Wall -c main.c -o main.o
clean:
	rm -f test main.o
