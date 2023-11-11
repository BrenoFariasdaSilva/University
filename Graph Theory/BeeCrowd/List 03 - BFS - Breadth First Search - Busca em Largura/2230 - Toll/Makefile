all:
	clear; time python3 ./main.py < largeInput.txt > output.txt

largeInput:
	clear; time python3 ./main.py < largeInput.txt

console:
	clear; time python3 ./main.py < input.txt

memory:
	valgrind --leak-check=full python3 ./main.py < input.txt > output.txt