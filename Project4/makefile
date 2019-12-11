CC = g++
CFLAGS = -Wall
TARGET = compile
OBJ = main.o
OBJS = main.o scanner.o parser.o staticSem.o
SRC = main.cpp
SRCS = main.cpp scanner.cpp parser.cpp staticSem.cpp

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp
parser.o: parser.cpp
	$(CC) -c $(CFLAGS) parser.cpp
scanner.o: scanner.cpp
	$(CC) -c $(CFLAGS) scanner.cpp
staticSem.o: staticSem.cpp
	$(CC) -c $(CFLAGS) staticSem.cpp
clean:
	/bin/rm -f *.o $(TARGET)
