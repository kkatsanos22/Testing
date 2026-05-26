CC = gcc
FLAGS = -Wall

testall: test1 test2

test%: test%.data main
	./main < test$*.data

main: main.o phonebook.o
	$(CC) $(FLAGS) main.o phonebook.o -o $@

main.o: main.c phonebook.h
	$(CC) $(FLAGS) -c main.c

phonebook.o: phonebook.c phonebook.h
	$(CC) $(FLAGS) -c phonebook.c

