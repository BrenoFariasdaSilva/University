# the compiler: gcc for C program, define as g++ for C++
CC = gcc
CXX = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
LINKING = -lglut -lGL -lGLU
TARGET = *

all:
	clear
	$(CXX) $(CFLAGS) -o main $(TARGET).cpp $(LINKING)
	./main

clean:
	$(RM) $(TARGET)