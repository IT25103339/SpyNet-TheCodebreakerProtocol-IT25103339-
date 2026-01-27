#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLYR1 '@' // define the symbols used in this game
#define PLYR2 '&'
#define PLYR3 '$'
#define SYM_WALL '#'
#define SYM_LIFE 'L'
#define SYM_INTEL 'I'
#define SYM_EXTRACT 'X'
#define SYM_EMPTY '.'

typedef struct { // structure to keep track of player data in the game
	int xaxis, yaxis;
	int lives;
	int intel;
	char symbol;
	int alive;
	int computerAI;
	int escaped;	
} player_t;

void gridSize_select(int *gridsize); // function prototypes declaration
void playerMode_select(int *playermode, int *compplayer, char *compplayerPrompt);
void createGrid(char ***Grid, int gridSize1);
void printGrid(char **grid, int gridSize2);
void freeMem(char **grid, int gridSize3);
void logMessage(char *text);
void statusBar(player_t plyr_list[], int count);
void placeExtraction(char **grid, int gridSize4);
void placeItems(char **grid, int gridSize5);
void playerConfig(player_t plyr_list[], char **grid, int gridSize6, int playerMode, int compPlayer, char symArray[]);
void playTurn(player_t *playerAvatar, char **grid, int gridSize7);

int main() {

	srand(time(NULL)); // get random values based on current computer time

	int gridSize, playerMode, compPlayer; // declare the variables used in the game
	int turn, activeInMission;
	char compPlayerPrompt;
	char **grid;
	char symArray[3];
	player_t plyr_list[3];

	grid = NULL; // assign starting values to the varaibles
	compPlayer = 0;

	symArray[0] = PLYR1; // assign symbols to the player icons
	symArray[1] = PLYR2;
	symArray[2] = PLYR3;

	printf("\n*****SpyNet – The Codebreaker Protocol*****\n");

	gridSize_select(&gridSize); // select the grid size

	playerMode_select(&playerMode, &compPlayer, &compPlayerPrompt); // select player mode and computer participation

	createGrid(&grid, gridSize); // create the grid based on the input values

	placeExtraction(grid, gridSize);// place the extract point in the created grid at a random placement

	playerConfig(plyr_list, grid, gridSize, playerMode, compPlayer, symArray); // set up player positions and data

	placeItems(grid, gridSize); // place lives adn intel randomly

	while (1){ // start of the main game loop

		turn = 0; // player turn
		activeInMission = 0; // loop in work

		while (turn < playerMode){ // check how many players are alive

			if (plyr_list[turn].alive == 1){
				activeInMission = activeInMission +1;
			}
			
			turn = turn + 1;
		}

		if (activeInMission == 1 && playerMode > 1){ // if only one player is left, they will automatically win
			
			turn = 0;
			
			while (turn < playerMode){
				
				if (plyr_list[turn].alive == 1){

					printf("\nMission won by Player %c!.\n", plyr_list[turn].symbol);
					plyr_list[turn].alive = 0;
				}

				turn = turn + 1;
			}

			break;
		}

		if (activeInMission == 0){ // if not, end the game if escaped or everyone is dead
			
			break;
		}

		turn = 0; // to cycle the player turns

		while (turn < playerMode){

			if (plyr_list[turn].alive == 1){

				statusBar(plyr_list, playerMode);
				printGrid(grid, gridSize);
				playTurn(&plyr_list[turn], grid, gridSize);
			}

			turn = turn + 1;
		}
	}

	printf("\nMission Ended!\n");// final end message
	
	freeMem(grid, gridSize);// free the memory allocated
	
	return 0;

}

void playTurn(player_t *playerAvatar, char **grid, int gridSize7){ // handle player movement

	int newRow, newCol, aiMove;
	char movement, logBufferTxt[100];

	newRow = playerAvatar->xaxis;
	newCol = playerAvatar->yaxis;

	if (playerAvatar->computerAI == 1){
		aiMove = rand() % 4; // for random computer player movement

		if (aiMove == 0){ 
			movement = 'W';
		}else if (aiMove == 1){ 
			movement = 'S';
		}else if (aiMove == 2){ 
			movement = 'A';
		}else{ 
			movement = 'D';
		}

		printf("Computer Player %c moved!\n", playerAvatar->symbol);
	}else{

		printf("Player %c: Enter your move (W/A/S/D) or 'Q' to quit: ", playerAvatar->symbol);
		scanf(" %c", &movement);
	}

	if (movement == 'q' || movement == 'Q'){ // if the player wants to quit, they can  

		printf("Player %c quit the game!\n", playerAvatar->symbol);
		
		sprintf(logBufferTxt, "Player %c has quit the game!", playerAvatar->symbol);
		logMessage(logBufferTxt);
		
		playerAvatar->alive = 0;   // mark as out
		playerAvatar->escaped = 0; // did not win
		
		grid[playerAvatar->xaxis][playerAvatar->yaxis] = SYM_EMPTY; // remove the player from the map
		
		return;
	}


	if (movement == 'w' || movement == 'W'){ // player movement direction logic
		newRow = newRow - 1;}
	if (movement == 's' || movement == 'S'){
	       	newRow = newRow + 1;}
	if (movement == 'a' || movement == 'A'){
		newCol = newCol - 1;}
	if (movement == 'd' || movement == 'D'){
		newCol = newCol + 1;
	}

	if (newRow < 0 || newRow >= gridSize7 || newCol < 0 || newCol >= gridSize7){ // check for player collisions boundary

		playerAvatar->lives = playerAvatar->lives- 1;

		sprintf(logBufferTxt, "Player %c hit Boundary!. Lives left: %d", playerAvatar->symbol, playerAvatar->lives);// write to log
		
		logMessage(logBufferTxt);// write to log

	}

	else if (grid[newRow][newCol] == SYM_WALL){ // check for player collisions wall

                playerAvatar->lives = playerAvatar->lives- 1;

                sprintf(logBufferTxt, "Player %c hit a Wall!. Lives left: %d", playerAvatar->symbol, playerAvatar->lives);// write to log

                logMessage(logBufferTxt);// write to log
        }

	
	else{
		sprintf(logBufferTxt, "Player %c moved to (%d, %d)", playerAvatar->symbol, newRow, newCol);
		logMessage(logBufferTxt);

		if (grid[newRow][newCol] == SYM_INTEL){ // item pick up logic
			playerAvatar->intel = playerAvatar->intel + 1;

			sprintf(logBufferTxt, "Player %c collected 1 intel!. Total: %d/3", playerAvatar->symbol, playerAvatar->intel);
			logMessage(logBufferTxt);
			
			grid[newRow][newCol] = SYM_EMPTY; // clear the item location as empty

		}else if (grid[newRow][newCol] == SYM_LIFE){
			playerAvatar->lives = playerAvatar->lives + 1;

			sprintf(logBufferTxt, "Player %c collected 1 life!. Total: %d", playerAvatar->symbol, playerAvatar->lives);
                        logMessage(logBufferTxt);

			grid[newRow][newCol] = SYM_EMPTY;
		
		}else if (grid[newRow][newCol] == SYM_EXTRACT){ // check for extract location
			
			if (playerAvatar->intel >= 3){ // if player has 3 intel , allow extraction
				
				printf("Player %c Extracted!\n", playerAvatar->symbol);

				sprintf(logBufferTxt, "Player %c has extracted! Mission won by Player %c", playerAvatar->symbol, playerAvatar->symbol);
				logMessage(logBufferTxt);
				
				playerAvatar->alive = 0;
				playerAvatar->escaped = 1;

				grid[playerAvatar->xaxis][playerAvatar->yaxis] = SYM_EMPTY;

			}else{
				printf("Player %c : Collect more Intel to extract!\n", playerAvatar->symbol); // if they do not have 3 intel, prompt to collect more
				
				newRow = playerAvatar->xaxis;
				newCol = playerAvatar->yaxis;
			}
		}

		if (playerAvatar->alive == 1){ //  update player position on grid according to movement input

			grid[playerAvatar->xaxis][playerAvatar->yaxis] = SYM_EMPTY;
			
			playerAvatar->xaxis = newRow;
			playerAvatar->yaxis = newCol;
			
			grid[newRow][newCol] = playerAvatar->symbol;
		}
	}

	if (playerAvatar->lives <= 0){ // check for player alive/dead status
	
		printf("Player %c died!\n", playerAvatar->symbol);
		
		sprintf(logBufferTxt, "Player %c died!", playerAvatar->symbol);
		logMessage(logBufferTxt);

		playerAvatar->alive = 0;
		playerAvatar->escaped = 0;
		
		grid[playerAvatar->xaxis][playerAvatar->yaxis] = SYM_EMPTY;// if the player is dead, remove the symbol from the grid
	}
}


void placeExtraction(char **grid, int gridSize4){ // place the extraction point on a random location
	
	int r = rand() % gridSize4; // random row
	int c = rand() % gridSize4; // random column
	
	grid[r][c] = SYM_EXTRACT; // place extract symbol on the grid
}

void playerConfig(player_t plyr_list[], char **grid, int gridSize6, int playerMode, int compPlayer, char symArray[]){ //start player position and data
	
	int p = 0; // player index = playermode - 1
	int placed; // placement validity check
	
	while (p < playerMode){
		
		plyr_list[p].symbol = symArray[p]; // assign index 0 to player 1,index 1 to player 2 etc.
		plyr_list[p].lives = 3; // player starting lives count
		plyr_list[p].intel = 0; // starting intel count
		plyr_list[p].alive = 1; // start as alive
		plyr_list[p].escaped = 0; // start as not extracted

		if (compPlayer == 1 && p == (playerMode - 1)){ // if computer is playing, set computerAI to 1 , else ,0.
			plyr_list[p].computerAI = 1;
		}else{
			plyr_list[p].computerAI = 0;
		}

		placed = 0; // not yet placed on grid

		while (placed == 0){
			
			plyr_list[p].xaxis = rand() % gridSize6; // random x axis location
			plyr_list[p].yaxis = rand() % gridSize6; // random y axis location
			
			if (grid[plyr_list[p].xaxis][plyr_list[p].yaxis] == SYM_EMPTY){ // only place player on a empty cell

				grid[plyr_list[p].xaxis][plyr_list[p].yaxis] = plyr_list[p].symbol; // place relevant player symbol on that position
				placed = 1; // now the player 'x' is placed, proceed to others
			}
		}
		
		p = p + 1; // move on to next player
	}
}

void placeItems(char **grid, int gridSize5){ // placing lives and intel randomly
	
	int intelCount = 0, lifeCount = 0, wallCount = 0; // this is a counting mechanism, not how much lives or intel are there
	int r, c; // row, column
	
	while (intelCount < 3){ // place 3 intel, no more than that.
		
		r = rand() % gridSize5; // getting random placement location 
		c = rand() % gridSize5;
		
		if (grid[r][c] == SYM_EMPTY){ // place only on a empty cell
			grid[r][c] = SYM_INTEL; intelCount = intelCount+ 1; 
		}
	}
	
	while (lifeCount < 2){ // place only 2 lives, not more.
		
		r = rand() % gridSize5;
		c = rand() % gridSize5;
		
		if (grid[r][c] == SYM_EMPTY){ 
			grid[r][c] = SYM_LIFE; lifeCount = lifeCount + 1; 
		}
	}
	
	while (wallCount < gridSize5){ // placing walls on random locations
		
		r = rand() % gridSize5;// get random location on grid
		c = rand() % gridSize5;
		
		if (grid[r][c] == SYM_EMPTY){ 
			grid[r][c] = SYM_WALL; wallCount = wallCount + 1; 
		}
	}
}

void gridSize_select(int *gridsize){ // grid size selection based on input
	
	printf("\nEnter grid size (5-15): ");
	scanf(" %d", gridsize); // get grid size X ( X * X)
	
	while (*gridsize < 5 || *gridsize > 15){ // take value between 5 and 15
		
		printf("Error! Value not acceptable. Enter a value between 5-15: ");
		scanf(" %d", gridsize);
	}

	printf("\n");
}

void playerMode_select(int *playermode, int *compplayer, char *compplayerPrompt){ // selcting player mode
	
	printf("Enter player count (1-3): "); // no of players
	scanf(" %d", playermode);
	
	while (*playermode < 1 || *playermode > 3){ // should be between 1 and 3 players
		printf("Error! Value not acceptable. Enter a value between 1-3: ");
		scanf(" %d", playermode);
	}
	
	if (*playermode > 1){
		
		while (1){// if it is not single player, as whether to enable computer opponent
			
			printf("\nDo you want to enable Computer as an opponent (Y/N): ");
			scanf(" %c", compplayerPrompt);
			
			if (*compplayerPrompt == 'Y' || *compplayerPrompt == 'y'){  // check agreement yes/no
				*compplayer = 1; 
				break; 
			
			}else if (*compplayerPrompt == 'N' || *compplayerPrompt == 'n'){ 
				*compplayer = 0; 
				break; 
			}
		}
	}
}

void createGrid(char ***Grid, int gridSize1){ // creating the grid
	
	int i = 0;
	int r, c; // row, column

	*Grid = (char **)malloc(gridSize1 * sizeof(char *)); //allocate memory for the grid
	
	while (i < gridSize1){
		(*Grid)[i] = (char *)malloc(gridSize1 * sizeof(char)); // memory allocation one by one
		i = i + 1;
	}

	for (r = 0; r < gridSize1; r++){ // craete empty grid

		for (c = 0; c < gridSize1; c++){

			(*Grid)[r][c] = SYM_EMPTY;
		}
	}
}

void printGrid(char **grid, int gridSize2){ // function to print the created grid / updated grid
	
	int r, c; //row ,column
	
	printf("\n");
	
	for (r = 0; r < gridSize2; r++){ // print the grid row by row

		for (c = 0; c < gridSize2; c++){ // print the columns of the grid within the rows

			printf("%c ", grid[r][c]); // print
		}

		printf("\n");
	}

	printf("\n");
}

void freeMem(char **grid, int gridSize3){ // free the allocated memory after the game

	int i = 0; // counter
	
	while (i < gridSize3){ 
		
		free(grid[i]); // free memory one by one
		i = i + 1;
	}

	free(grid);
}

void logMessage(char *text){ // for logging mechanism

	FILE *f = fopen("gamelog.txt", "a"); // create/update to the external file

	if (f != NULL){ // check for availability
		
		fprintf(f, "%s\n", text);  // write to log
		fclose(f);
	}
}

void statusBar(player_t plyr_list[], int count){ // player data status bar
	
	int i = 0;
	
	printf("\n");
	
	while (i < count){ // to print the bar for the available players
		
		printf("Player %c | Lives: %d | Intel: %d/3 | Position: (%d,%d)\n", plyr_list[i].symbol, plyr_list[i].lives, plyr_list[i].intel,plyr_list[i].xaxis, plyr_list[i].yaxis);
		
		i = i + 1; // move from player 1 to 2, 2 to 3 etc.
	}
	
	printf("\n");
}
