/*Alexis Elston
 * CS201 - Spring 2019
 * Portfolio Due March 29 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


int gameIntro();
void setBoardEMPTY(char *board, int Board_Columns, int BOARD_ROWS);
int getMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS);
int makeMove2(int move);
int checkWin(char *board, int Board_Columns, int BOARD_ROWS);
int horizontalCheck(char *board, int Board_Columns, int BOARD_ROWS);

int main(int argc, char *argv[]){
	char playerone[25];
	char playertwo[25];
	int winner = 0;
	int gameMode = 0;
	int Board_Columns = 6;
	int BOARD_ROWS = 7;
	int breaker = 0;
	gameMode = gameIntro();

	int player, turn, done = 0;
	player = turn % 2 + 1;
	
	printf("Now select a game board size. The recommended and minimum size is 6 rows and 7 columns, but can be no larger than 15 rows by 15 columns to fit the screen.");
	printf("\nBoard Rows: ");
	scanf("%d", &BOARD_ROWS);


while(breaker = 0){
	while(BOARD_ROWS > 15 || BOARD_ROWS < 6){
		if(isdigit(BOARD_ROWS) != 0){
			printf("Invalid board size. The default row will be used.\n");
			breaker = 1;
			break; }		
		printf("That board size is invalid. Please select a row size between 6 and 15: ");
		scanf("%d", &BOARD_ROWS); }
}

if(breaker == 0){
	printf("\nBoard Columns: ");
	scanf("%d", &Board_Columns);
}
	
while(breaker = 0){	
	while(Board_Columns > 15 || Board_Columns < 7 && breaker != 1){
		if(isdigit(Board_Columns) != 0){
			printf("Invalid board size. The default column will be used.\n");
			breaker = 1;
			break; }
		
		printf("That board size is invalid. Please select a column size between 7 and 15: ");
		scanf("%d", &Board_Columns);	}
}

if(breaker == 0){
	char catchall[5];
	printf("Press the '1' key and 'Enter' to continue: ");
	scanf("%s", catchall);
}

	const char *PIECES = "XO";
	char board[BOARD_ROWS * Board_Columns];
	memset(board, ' ', BOARD_ROWS * Board_Columns);

	if (gameMode == 1){
		printf("This is ONE PLAYER GAME MODE");
	}

	else if (gameMode == 2){
		printf("\n\n\nWelcome to two-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
		
		printf("Player one's name is: ");
		scanf("%s", playerone);
		printf("Player two's name is: ");
		scanf("%s", playertwo);
		printf("\n");
		printf("%s will be X and %s will be O. Good Luck!\n", playerone, playertwo);


////////////////


		for(turn = 0; turn < BOARD_ROWS * Board_Columns && !done; turn++){
			setBoardEMPTY(board, Board_Columns, BOARD_ROWS);
			while(!getMove(board, turn % 2, PIECES, Board_Columns, BOARD_ROWS)){
				setBoardEMPTY(board, Board_Columns, BOARD_ROWS);
				puts("**Column FULL!**\n"); }
			done = checkWin(board, Board_Columns, BOARD_ROWS);
		}
		setBoardEMPTY(board, Board_Columns, BOARD_ROWS);

		if(turn == BOARD_ROWS * Board_Columns && !done){
			puts("It's a tie!"); }
		else{
			turn = turn - 1;
			player = turn % 2 + 1;
			if(player == 1){
				printf("%s Wins!\n", playerone); }
			else{
				printf("%s Wins!\n", playertwo); }
		}	}


	else {
		printf("FATAL ERROR: GAME TERMINATED"); }


	return 0;
}


///////////////////////////////////////////////////////////////////////////////


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
			       printf("Please enter a valid number. '1' for one-player mode and '2' for two-player mode. \n");
			       scanf("%d", &setupPlayers); }
	       }
}


////////////////////////////////////////////////////////////////////////////////////

void setBoardEMPTY(char *board, int Board_Columns, int BOARD_ROWS){
	int row, column;
	printf("\n\n");
	puts("\n		-Connect Four-	\n");
	for(row = 0; row < BOARD_ROWS; row++){
		for(column = 0; column < Board_Columns; column++){
			printf("| %c   ", board[Board_Columns * row + column]);
		}
		puts("|");
		puts("                    ");
	}
	printf("   ");
	for(column = 1; column < Board_Columns+1; column++){
		if(column < 10){
			printf("%d     ", column);
		}
		else{
			printf("%d    ", column); }}
printf("\n\n");	
return;
}

///////////////////////////////////////////////////////////////////////////////////////

int getMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
	int row, col = 0;
	printf("Player %d (%c), which column would you like to place your token?\n", player + 1, PIECES[player]);
	while(1){
		scanf("%d", &col);
		if(col > Board_Columns || col < 1){
			while(getchar() != '\n');
			puts("Invalid Column. Please enter a new column."); }
		else{
			break; }}
	col--;

	for(row = BOARD_ROWS - 1; row >= 0; row--){
		if(board[Board_Columns * row + col] == ' '){
			board[Board_Columns * row + col] = PIECES[player];
			return 1;
		}
	}
	return 0; }

/////////////////////////////////////////////////
int checkWin(char *board, int Board_Columns, int BOARD_ROWS){
	return (horizontalCheck(board, Board_Columns, BOARD_ROWS)); }

int checkFour(char *board, int a, int b, int c, int d){
return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' '); }

	
int horizontalCheck(char *board, int Board_Columns, int BOARD_ROWS){
	int row, col;
	int count = 0;


////////////	check horizontal /////////////////////////

	const int WIDTH = 1;

	for(int row=0; row < BOARD_ROWS; row++){
		for(int col=0; col < Board_Columns - 3; col++){
			count = Board_Columns * row + col;
			if(checkFour(board, count, count + WIDTH, count + (WIDTH * 2), count + (WIDTH * 3))){
				return 1; }
		}
	}

/////////////	check vertical ///////////////////////////

	const int HEIGHT = Board_Columns;

	for(int row = 0; row < BOARD_ROWS - 3; row++){
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(checkFour(board, count, count + HEIGHT, count + (HEIGHT * 2), count + (HEIGHT * 3))){
				return 1; }
		}
	}

//////////////	check diagonal upwards ///////////////////

	const int D_RIGHT = Board_Columns - 1;
	int hold = 0;

	for(int row = 0; row < BOARD_ROWS - 3; row++){
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(hold >=3 && checkFour(board, count, count + D_RIGHT, count + D_RIGHT * 2, count + D_RIGHT * 3)){
				return 1; }
			hold ++;
		}
		hold = 0;
	}

/////////////	check diagonal downwards /////////////////

	const int D_LEFT = Board_Columns + 1;
	hold = 0;

	for(int row = 0; row < BOARD_ROWS - 3; row ++){
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(checkFour(board, count, count + D_LEFT, count + D_LEFT * 2, count + D_LEFT * 3)){
				return 1; }
		}
	}

	return 0;
}














