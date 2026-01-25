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
void createGrid(char ***Grid, int gridSize1);
void printGrid(char **grid, int gridSize2);

typedef struct{
	int xaxis, yaxis;
	int lives;
	int intel;
	char symbol;
	int alive;
	int computerAI;
} player_t;

int main(){

	srand(time(NULL));

	int gridSize, playerMode, randomRowLoc, randomColLoc, newRow, newCol;
	int addPlayer = 0, intelCount = 0, lifeCount = 0, wallCount = 0;
	int compPlayer = 0;
	char compPlayerPrompt, movement;
	char **grid = NULL;

	printf("\n*****SpyNet – The Codebreaker Protocol*****\n");
	
	gridSize_select(&gridSize);
	
	playerMode_select(&playerMode, &compPlayer, &compPlayerPrompt);

	createGrid(&grid, gridSize);
	
	randomRowLoc = rand() % gridSize;
    	randomColLoc = rand() % gridSize;

    	grid[randomRowLoc][randomColLoc] = SYM_EXTRACT;

        player_t player_01;
        player_01.symbol = PLYR1;
        player_01.lives = 3;
        player_01.intel = 0;
        player_01.alive = 1;
        player_01.computerAI = 0;

        while (addPlayer == 0){

                player_01.xaxis = rand() % gridSize;
                player_01.yaxis = rand() % gridSize;

                if (grid[player_01.xaxis][player_01.yaxis] == SYM_EMPTY){

                        grid[player_01.xaxis][player_01.yaxis] = player_01.symbol;
                        addPlayer = 1;

                }
        }
	

    	while (intelCount < 3){

        	randomRowLoc = rand() % gridSize;
        	randomColLoc = rand() % gridSize;

        	if (grid[randomRowLoc][randomColLoc] == SYM_EMPTY){

			grid[randomRowLoc][randomColLoc] = SYM_INTEL;
            		intelCount = intelCount + 1;

        	}
    	}

    	while (lifeCount < 2){

        	randomRowLoc = rand() % gridSize;
        	randomColLoc = rand() % gridSize;

        	if (grid[randomRowLoc][randomColLoc] == SYM_EMPTY){

            		grid[randomRowLoc][randomColLoc] = SYM_LIFE;
            		lifeCount = lifeCount + 1;
		}
	}

    	while (wallCount < gridSize){

        	randomRowLoc = rand() % gridSize;
        	randomColLoc = rand() % gridSize;

        	if (grid[randomRowLoc][randomColLoc] == SYM_EMPTY){

            		grid[randomRowLoc][randomColLoc] = SYM_WALL;
            		wallCount = wallCount + 1;
        	}
    	}
	
	while (player_01.alive == 1){

        	printf("Enter move (W/A/S/D): ");
       		scanf(" %c", &movement);

        	newRow = player_01.xaxis;
        	newCol = player_01.yaxis;

        	if (movement == 'w' || movement == 'W'){

            		newRow = player_01.xaxis - 1;

        	}else if (movement == 's' || movement == 'S'){

            		newCol = player_01.xaxis + 1;

        	}else if (movement == 'a' || movement == 'A'){

            		newRow = player_01.yaxis - 1;

       	 	}else if (movement == 'd' || movement == 'D'){

            		newCol = player_01.yaxis + 1;
        }

		if (player_01.lives <= 0){

            		printf("GAME OVER!\n");
            		player_01.alive = 0;
        	}

        	if (player_01.alive == 1){

            		printGrid(grid, gridSize);
        	}
	}

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
	}

	if (*playermode == 1){ // display selected player mode
                printf("\nYou have selected Singleplayer mode\n");
        }else if(*playermode == 2){
                printf("\nYou have selected 2 player mode\n");
        }else{
                printf("\nYou have selected 3 player mode\n");
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

void createGrid(char ***Grid, int gridSize1){

	int row = 0, currentRow = 0, currentCol = 0;

	*Grid = (char **)malloc(gridSize1*sizeof(char *));

	while (row < gridSize1){

        	(*Grid)[row] = (char *)malloc(gridSize1 * sizeof(char));
        	row = row + 1;
	}
	
	while (currentRow < gridSize1){
      
        char *thisRow = (*Grid)[currentRow];
	currentCol = 0;

        while (currentCol < gridSize1){
            
            thisRow[currentCol] = SYM_EMPTY;
            currentCol = currentCol + 1;
	}
        
        currentRow = currentRow + 1;
	
	}
}


void printGrid(char **grid, int gridSize2){
	
	int row1 = 0, i = 0;
	
	printf("\n");
    
	while (row1 < gridSize2){
		i = 0;

		while(i < gridSize2){

			printf("%c ", grid[row1][i]);
			i = i + 1;
		}

		printf("\n");
		row1 = row1 + 1;
	}

	printf("\n");
}	
