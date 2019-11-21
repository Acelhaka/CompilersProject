CC = g++
CFLAGS =
TARGET = frontEnd
OBJ = main.o
OBJS = main.o scanner.o parser.o testTree.o
SRC = main.cpp
SRCS = main.cpp scanner.cpp parser.cpp testTree.cpp

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp
parser.o: parser.cpp
	$(CC) -c $(CFLAGS) parser.cpp
scanner.o: scanner.cpp
	$(CC) -c $(CFLAGS) scanner.cpp
testTree.o: testTree.cpp
	$(CC) -c $(CFLAGS) testTree.cpp
clean:
	/bin/rm -f *.o $(TARGET)
