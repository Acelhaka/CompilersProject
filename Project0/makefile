CC = g++
CFLAGS = -Wall
TARGET = p0
OBJ = main.o
OBJS = main.o buildTree.o traversals.o
SRC = main.cpp 
SRCS = main.cpp buildTree.cpp traversals.cpp

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp
buildTree.o: buildTree.cpp
	$(CC) -c $(CFLAGS) buildTree.cpp
traversals.o: traversals.cpp
	$(CC) -c $(CFLAGS) traversals.cpp

clean:
	/bin/rm -f *.o $(TARGET)
