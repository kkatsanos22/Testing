CC = gcc
FLAGS = -Wall

testall: test1 test2 

test%: test%.data btree_test
	./btree_test < test$*.data

btree_test: btree_test.o btree.o
	$(CC) $(FLAGS) btree_test.o btree.o -o $@

btree_test.o: btree_test.c btree.h
	$(CC) $(FLAGS) -c btree_test.c

btree.o: btree.c btree.h
	$(CC) $(FLAGS) -c btree.c

