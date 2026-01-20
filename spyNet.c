#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define player1 '@'
#define player2 '&'
#define player3 '$'
#define symbol_wall '#'
#define symbol_life 'L'
#define symbol_intel 'I'
#define symbol_extract 'X'
#define symbol_empty '.'

int main(){
	int gridSize; // grid size 5 - 15
	
	printf("\nEnter grid size: ");
	scanf("%d", &gridSize);

	if (gridSize < 5 || gridSize > 15){
		printf("\nError! Defaulting value to 5!\n\n");
		gridSize = 5;
	}
}
