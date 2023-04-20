all:
	clear
	python3 ./main.py < largeInput.txt > output.txt

largeInput:
	clear
	python3 ./main.py < largeInput.txt

console:
	clear
	python3 ./main.py < input.txt

time:
	clear
	time python3 ./main.py < input.txt > output.txt

memory:
	clear
	valgrind --leak-check=full python3 ./main.py < input.txt > output.txt