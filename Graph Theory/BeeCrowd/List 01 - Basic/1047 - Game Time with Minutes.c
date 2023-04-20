// Read the start time and end time of a game, in hours and minutes (initial hour, initial minute, final hour, final minute). Then print the duration of the game, knowing that the game can begin in a day and finish in another day,

// Obs.: With a maximum game time of 24 hours and the minimum game time of 1 minute.
// Input

// Four integer numbers representing the start and end time of the game.
// Output

// Print the duration of the game in hours and minutes, in this format: “O JOGO DUROU XXX HORA(S) E YYY MINUTO(S)” . Which means: the game lasted XXX hour(s) and YYY minutes.

// Input Sample 	
// 7 8 9 10
// Output Sample
// O JOGO DUROU 2 HORA(S) E 2 MINUTO(S)

// Input Sample 	
// 7 7 7 7
// Output Sample
// O JOGO DUROU 24 HORA(S) E 0 MINUTO(S)

// Input Sample 	
// 7 10 8 9
// Output Sample
// O JOGO DUROU 0 HORA(S) E 59 MINUTO(S)

#include <stdio.h>
 
int main() {
	int startH = 0;
	int startM = 0;
	int endH = 0;
	int endM = 0;
	int hours = 0;
	int minutes = 0;
	
	scanf("%d", &startH);
	scanf("%d", &startM);
	scanf("%d", &endH);
	scanf("%d", &endM);

	int startTime = 60*startH + startM;
	int endTime = 60*endH + endM;

	int elapsedTime = endTime - startTime;

	if (elapsedTime == 0) {
		hours = 24;
		minutes = 0;
	}

	else if (elapsedTime < 0) {
		hours = 23 + (elapsedTime / 60);
		minutes = 60 + (elapsedTime % 60);
	}

	else {
		hours = elapsedTime / 60;
		minutes = elapsedTime % 60;
	}

	printf("O JOGO DUROU %d HORA(S) E %d MINUTO(S)\n", hours, minutes);
	
	return 0;
}