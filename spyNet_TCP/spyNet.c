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

void gridSize_select(int *gridsize);
void playerMode_select(int *playermode, int *complayer, char *complayerPrompt);

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
	
	gridSize_select(&gridSize);
	
	playerMode_select(&playerMode, &compPlayer, &compPlayerPrompt);
}

void gridSize_select(int *gridsize){
	
	printf("\nEnter grid size (5-15): "); // get grid size
        scanf(" %d", gridsize);

        while (*gridsize < 5 || *gridsize > 15){ // ask again if the value is not within parameters
                printf("Error! Value not acceptable. Enter a value between 5-15: ");
                scanf(" %d", gridsize);
        }
	printf("\n");
}

void playerMode_select(int *playermode, int *compplayer, char *compplayerPrompt){

	printf("Enter player mode(1-3): "); // get player mode single/multiple
        scanf(" %d", playermode);

	while (*playermode < 1 || *playermode > 3){ // ask again if the value is not within parameters
                printf("Error! Value not acceptable. Enter a value between 1-3: ");
                scanf(" %d", playermode);

		if (*playermode == 1){ // display selected player mode
                	printf("\nYou have selected Singleplayer mode\n");
        	}else if(*playermode == 2){
                	printf("\nYou have selected 2 player mode\n");
        	}else {
                	printf("\nYou have selected 3 player mode\n");
        	}
	}

	if (*playermode > 1){
		while (1){

			printf("\nDo you want to enable Computer as an opponent (Y/N): ");
       	        	scanf(" %c", compplayerPrompt);

			if (*compplayerPrompt == 'Y' || *compplayerPrompt == 'y'){
				*compplayer = 1;
		    		printf("Computer opponent enabled!\n");
		    		break;
            		}else if(*compplayerPrompt == 'N' || *compplayerPrompt == 'n'){
                		*compplayer = 0;
                		printf("Human opponent mode selected!\n");
                		break;
			}else{
                		printf("Invalid input! Please enter Y or N.");
                		while (getchar() != '\n');
			}
		}
	}

}
