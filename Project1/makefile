CC = g++
CFLAGS = -Wall
TARGET = scanner
OBJ = main.o
OBJS = main.o testScanner.o scanner.o
SRC = main.cpp 
SRCS = main.cpp testScanner.cpp scanner.cpp

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(SRCS)

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp
testScanner.o: testScanner.cpp
	$(CC) -c $(CFLAGS) testScanner.cpp
scanner.o: scanner.cpp
	$(CC) -c $(CFLAGS) scanner.cpp

clean:
	/bin/rm -f *.o $(TARGET)
