CC=g++
CFLAGS=-std=c++11
LIBS=-lgtest -lpthread
OBJ=obj
BIN=bin

all: utFS

utFS: $(OBJ)/utFS.o
	$(CC) $(CFLAGS) -o $@ $(OBJ)/utFS.o $(LIBS)
$(OBJ)/utFS.o: utFS.cpp utFS.h node.h link.h directory.h iterator.h directory_builder.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o utFS
stat:
	wc *.h *.cpp
