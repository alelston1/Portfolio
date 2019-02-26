#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define ROWS 3
#define COLUMNS 3

int gameIntro(){
        int setupPlayers = 0;
        int hold = 0;
        printf("Welcome to Tic-Tac-Toe!");
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
				return 2;}
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
			scanf("%d", &setupPlayers);
		}
	}
}

void setBoardEmpty(char *board){
	int row, column;
	int x = 0;
	char index[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	puts("\n	-Tic-Tac-Toe-	\n");
	puts("-------------");	
	for(row = 0; row < ROWS; row++){
		for(column = 0; column < COLUMNS; column++){
			printf("| %c ", index[x]);
			x++;
		}
		puts("|");
		puts("-------------");
	}
	puts("  1   2   3\n");
return;
}


void makeMove(int player, char *board, char *index){
	int row, column;
	int x = 0;
	int coordinate = 0;
	player = (player % 2) + 1;
	printf("Player %d: Enter number coordinate. DO NOT enter a non-digit: ", player);
	scanf("%d", &coordinate);
	

while(1){
	if(index[coordinate-1] == 'X' || index[coordinate-1] == 'O'){
		printf("That move has already been taken! Try again: ");
		scanf("%d", &coordinate);	}
	else if((coordinate > 9) || (coordinate < 1)){
		printf("That move is outside of the board. Please enter an integer 1-9: ");
		scanf("%d", &coordinate); }
	else break;
}
	
	printf("Putting move in spot %d\n", coordinate);

	if(player == 1){ 
		index[coordinate-1] = 'X'; }
	else {
		index[coordinate-1] = 'O'; }


		puts ("\n		-Tic-Tac-Toe-	\n");
	puts("------------");
	for(row = 0; row < ROWS; row++){
		for(column = 0; column < COLUMNS; column++){
			printf("| %c ", index[x]);
			x++;
		}
		puts("|");
		puts("------------");
	}
	puts("  1  2  3\n");

return;
}


int checkWinner(char *index){
	int winner = 0;
	
//Check Horizontal

	if(index[0] == index[1] && index[1] == index[2] && index[2] == 'X'){
		winner = 1; }
	else if (index[3] == index[4] && index[4] == index[5] && index[5] == 'X'){
		winner = 1; }
	else if (index[6] == index[7] && index[7] == index[8] && index[8] == 'X'){
		winner = 1; }

	else if(index[0] == index[1] && index[1] == index[2] && index[2] == 'O'){
		winner = 2; }
	else if(index[3] == index[4] && index[4] == index[5] && index[5] == 'O'){
		                 winner = 2; }
	else if(index[6] == index[7] && index[7] == index[8] && index[8] == 'O'){
		                winner = 2; }

//Check Vertical

	else if (index[0] == index[3] && index[3] == index[6] && index[6] == 'X'){
		winner = 1; }
	else if (index[1] == index[4] && index[4] == index[7] && index[7] == 'X'){
		winner = 1; }
	else if (index[2] == index[5] && index[5] == index[8] && index[8] == 'X'){
		winner = 1; }
	else if (index[0] == index[3] && index[3] == index[6] && index[6] == 'O'){
		winner = 2; }
	else if (index[1] == index[4] && index[4] == index[7] && index[7] == 'O'){
		winner = 2; }
	else if (index[2] == index[5] && index[5] == index[8] && index[8] == 'O'){
		winner = 2; }

//Check Diagonal
	
	else if (index[0] == index[4] && index[4] == index[8] && index[8] == 'X'){
		winner = 1; }
	else if (index[2] == index[4] && index[4] == index[6] && index[6] == 'X'){
		winner = 1; }
	else if (index[0] == index[4] && index[4] == index[8] && index[8] == 'O'){
		winner = 2; }
	else if (index[2] == index[4] && index[4] == index[6] && index[6] == 'O'){
		winner = 2; }

else {
		winner = 0; }	
return winner;
}

////////////////////////////////////////////////////////////////////////
int main(void){
	char playerone[25];
	char playertwo[25];
	int player = 0;
	char board[ROWS * COLUMNS];
	int winner = 0;
	char index[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};



	if (gameIntro() == 2){
		printf("Welcome to two-player mode. Please enter a nickname WITHOUT SPACES below. \n");
		printf("Player one's name is: ");
		scanf("%s", playerone);
		printf("Player two's name is: ");
		scanf("%s", playertwo);
		printf("%s will be X and %s will be O. Good Luck!\n", playerone, playertwo);
	}

	setBoardEmpty(board);



	while(winner == 0){	
		makeMove(player, board, index);
		checkWinner(index);
		if (checkWinner(index) == 1){
			printf("%s WINS!\n", playerone);
	       		winner = 1;	}
		else if (checkWinner(index) == 2){
			printf("%s WINS!\n", playertwo);
	       		winner = 2;	}
		else if (player == 8){
			printf("DRAW!\n\n");
			break; }
		else {
			printf("\n\n%d\n\n", player);
			winner = 0; }
		player = player + 1;
	}
	return 0;
}















