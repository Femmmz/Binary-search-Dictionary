CXX = gcc


all: dict1 dict2

dict1: dict1.c bst.c bst.h
	$(CXX) -o dict1 dict1.c bst.c

dict2: dict2.c bst.c bst.h
	$(CXX) -o dict2 dict2.c bst.c
