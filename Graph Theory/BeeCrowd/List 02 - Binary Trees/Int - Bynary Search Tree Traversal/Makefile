# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g
LINKING = 
TARGET = *

all:
	$(CXX) $(CFLAGS) -o main $(TARGET).c $(LINKING)
	./main < input.txt > output.txt

clean:
	$(RM) $(TARGET)