#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLYR1 '@'
#define PLYR2 '&'
#define PLYR3 '$'
#define SYM_WALL '#'
#define SYM_LIFE 'L'
#define SYM_INTEL 'I'
#define SYM_EXTRACT 'X'
#define SYM_EMPTY '.'

typedef struct{
	int x, y;
	int lives;
	int intel;
	char symbol;
	int alive;
	int computerAI;
} Player;

int main(){

	srand(time(NULL));

	int gridSize, playerMode;// grid size 5 - 15
	int compPlayer = 0;
	char compPlayerPrompt;

	printf("\n*****SpyNet – The Codebreaker Protocol*****\n");
	
	printf("\nEnter grid size (5-15): "); // get grid size
	scanf(" %d", &gridSize);

	if (gridSize < 5 || gridSize > 15){ // default to 5 if value is out of parameters
		printf("\nError! Defaulting value to 5!\n");
		gridSize = 5;
	}
	
	printf("Enter player mode(1-3): "); // get player mode single/multiple
	scanf(" %d", &playerMode);

	if (playerMode < 1 || playerMode > 3){ //default to singleplayer if value is out of parameters
		printf("\nError! Defaulting value to 1!\n");
		playerMode = 1;
	}

	if (playerMode == 1){ // display selected player mode
		printf("\nYou have selected Singleplayer mode\n");
	}else if(playerMode == 2){
		printf("\nYou have selected 2 player mode\n");
	}else {
		printf("\nYou have selected 3 player mode\n");
	}
	
	if (playerMode > 1){ // check for computer opponent permission
		printf("\nDo you want to enable Computer as an opponent (Y/N): ");
		scanf(" %c", &compPlayerPrompt);

		if (compPlayerPrompt == 'Y' || compPlayerPrompt == 'y'){ //check for input and select computer/human opponent
			compPlayer = 1;
			printf("\nComputer opponent enabled!\n");
		}else if (compPlayerPrompt == 'N' || compPlayerPrompt == 'n'){
			compPlayer = 0;
			printf("\nHuman opponent mode selected!\n");
		}else{
			printf("\nError! Invalid input! Defaulting to Human Opponent mode\n");
			compPlayer = 0;
		}
	
	}
}
