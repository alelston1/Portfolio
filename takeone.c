/* Alexis Elston
 * CS201 - Spring 2019
 * Portfolio */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

////////// Define Variables ///////////
#define BOARD_ROWS 6
#define BOARD_COLUMNS 7

///////////////////////////// This Function will set the game mode to one or two player ////////////////////////////////////////////////
int gameIntro(){
	int setupPlayers = 0;
	int hold = 0;

	printf("Welcome to Connect Four!");
	while(1){	
		printf("\nFor one-player mode, enter a '1'. For two-player mode, enter a '2'.\n");
		scanf("%d", &setupPlayers);	
		
			if (setupPlayers == 1){
				printf("You chose to play against the computer, is this correct? Enter '1' for yes or enter '2' to switch to two-player mode. \n");
				scanf("%d", &hold);
				if (hold == 1){ 
					printf("Good Luck! You're going to need it!\n");
					return 1; }
				else {
					printf("You have switched to two player mode.\n");
					return 2; }
			}

			else if (setupPlayers == 2){
				printf("You chose to play against another player, is this correct? Enter '1' for yes, '2' to switch to one-player mode. \n");
				scanf("%d",&hold);
				if (hold == 1) {
					return 2; }
				else {
					printf("You have switched to one player mode. Good luck, you will need it to beat me!\n");
					return 1; }
			}

			else {
				printf("Please enter a valid number. '1' for one-player mode and '2' for two-player mode.\n");
				scanf("%d", &setupPlayers); }
	}
}
	
//////////////////////////////////// This Function Prints an EMPTY Board //////////////////////////////////////////////////////////

void setBoardEMPTY(char *board){
	int row, column;
	puts("\n	-Connect Four-	\n");
	for(row = 0; row < BOARD_ROWS; row++){
		for(column = 0; column < BOARD_COLUMNS; column++){
			printf("|   ");
		}
		puts("|");
		puts("-----------------------------");
	}
	puts("  1   2   3   4   5   6   7\n");
return;
}


///////////////////////////////////// This Function Makes a Move for a Player ////////////////////////////////////////////////////


int getMove2(){
	char move = '0';	
		printf("Please Choose a column to place move. Input must be an integer 1-7:  ");
		scanf("%c", &move);
		scanf("%c", &move);
	while(1){	
		if(move == '1' || move == '2'|| move == '3' || move == '4' || move == '5' || move == '6' || move == '7'){
			return move;
	       		break; break;	}
		else {
			printf("That is not a valid move. Please enter a column 1 through 7: ");
			scanf("%c", &move);
			scanf("%c", &move);	}
	}
}

/////////////////////////////////////// This Function Places the Move on the Board ///////////////////////////////////////////////
int makeMove2(){
	return 0;
}



/////////////////////////////////////// This Function Checks for a Winner ////////////////////////////////////////////////////////
int checkWinner(){
	return 1;
}



//////////////////////////////////////// This is the Main Function ///////////////////////////////////////////////////////////////


int main(void){
	char playerone[25];
	char playertwo[25];
	int winner = 1;
	int gameMode = 0;
	char board[BOARD_ROWS * BOARD_COLUMNS];


	gameMode = gameIntro();

	if (gameMode == 1){
		printf("This is ONE PLAYER GAME MODE");
	}

	else if (gameMode == 2){
		printf("Welcome to two-player mode. Please enter a nickname below. No Whitespaces can be entered. \n");
		printf("Player one's name is: ");
		scanf("%s", playerone);
		printf("Player two's name is: ");
		scanf("%s", playertwo);
		printf("\n");
		printf("%s will be X and %s will be O. Good Luck!\n", playerone, playertwo);

//CHECK//
		printf("MOVE RETURNED: %c", getMove2());
/////////

		while(winner == 0){
			getMove2();
			makeMove2();
			winner = checkWinner();	
		}
		
		if(winner == 1){
			printf("\n\n%s Wins!", playerone); }
		else {
			printf("\n\n%s Wins!", playertwo); }
	}


	else {
		printf("FATAL ERROR: GAME TERMINATED");
	}


	setBoardEMPTY(board);
	return 0;
}

