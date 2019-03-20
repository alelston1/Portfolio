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
int checkWinner();


int main(int argc, char *argv[]){
	char playerone[25];
	char playertwo[25];
	int winner = 0;
	int gameMode = 0;
	int Board_Columns = 6;
	int BOARD_ROWS = 7;
	
	gameMode = gameIntro();

	int player, turn, done = 0;
	player = turn % 2 + 1;
	
	printf("Now select a game board size. The recommended and minimum size is 6 rows and 7 columns, but can be no larger than 15 rows by 15 columns to fit the screen.");
	printf("\nBoard Rows: ");
	scanf("%d", &BOARD_ROWS);
	while(BOARD_ROWS > 15 || BOARD_ROWS < 6){
		printf("That board size is invalid. Please select a row size between 6 and 15: ");
		scanf("%d", &BOARD_ROWS); }
	printf("\nBoard Columns: ");
	scanf("%d", &Board_Columns);
	while(Board_Columns > 15 || Board_Columns < 7){
		printf("That board size is invalid. Please select a row size between 7 and 15: ");
		scanf("%d", &Board_Columns); }


	const char *PIECES = "XO";
	char board[BOARD_ROWS * Board_Columns];
	memset(board, ' ', BOARD_ROWS * Board_Columns);

	if (gameMode == 1){
		printf("This is ONE PLAYER GAME MODE");
	}

	else if (gameMode == 2){
		printf("Welcome to two-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
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
			done = checkWinner(board);
		}
		setBoardEMPTY(board, Board_Columns, BOARD_ROWS);

		if(turn == BOARD_ROWS * Board_Columns && !done){
			puts("It's a tie!"); }
		else{
			turn--;
			printf("Player %d wins!\n", turn % 2 + 1); }







//		while(winner == 0){
//			getMove(board, player, PIECES, Board_Columns, BOARD_ROWS);
//			makeMove2(move);
//			winner = checkWinner();
//		}

		if (winner == 1){
			printf("\n\n%s WINS!", playerone); }
		else {
			printf("\n\n%s WINS!", playertwo); }
	}
	else {
		printf("FATAL ERROR: GAME TERMINATED"); }
		
		setBoardEMPTY(board, Board_Columns, BOARD_ROWS);
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
int checkWinner(){
	printf("Checking");
	return 0; }














