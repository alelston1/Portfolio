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
int checkFour(char *board, int a, int b, int c, int d);
int checkThree(char *board, int a, int b, int c, int d);
int horizontalCheck(char *board, int Board_Columns, int BOARD_ROWS);
int AIMove();
int AIMove2();

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
	
	printf("Now select a game board size. The recommended minimum size is 6 rows and 7 columns. It is recommended to not exceed 15 x 15.");
	printf("\nBoard Rows: ");
	scanf("%d", &BOARD_ROWS);


while(breaker = 0){
	while(BOARD_ROWS >= 40 || BOARD_ROWS < 6){
		if(isdigit(BOARD_ROWS) != 0){
			printf("Invalid board size. The default row will be used.\n");
			breaker = 1;
			break; }		
		printf("That board size is invalid. Please select a row size between 6 and 40: ");
		scanf("%d", &BOARD_ROWS);	}
}

if(breaker == 0){
	printf("Board Columns: ");
	scanf("%d", &Board_Columns);
}
	
while(breaker = 0){	
	while(Board_Columns > 40 || Board_Columns < 7 && breaker != 1){
		if(isdigit(Board_Columns) != 0){
			printf("Invalid board size. The default column will be used.\n");
			breaker = 1;
			break; }
		
		printf("That board size is invalid. Please select a column size between 7 and 40: ");
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

///////////////////////////////////
	
	if (gameMode == 1){
		printf("This is ONE PLAYER GAME MODE");
		printf("\n\nWelcome to one-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
		printf("Player one's name is: ");
		scanf("%s", playerone);
		printf("%s will be playing against me, Mykalo. Best of luck, I don't lose!", playerone);
		
		for(turn = 0; turn < BOARD_ROWS * Board_Columns && !done; turn++){
			setBoardEMPTY(board, Board_Columns, BOARD_ROWS);
			while(!AIMove2(board, turn % 2, PIECES, Board_Columns, BOARD_ROWS)){
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
			if(player == 2){
				printf("HA! I told you I would beat you, YOU LOSE!\n"); }
			else{
				printf("Rats... you've beat me this time. Congratulations %s!\n", playerone); }
		} 
	
	}

///////////////////////////////////////

	else if (gameMode == 2){
		printf("\n\n\nWelcome to two-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
		
		printf("Player one's name is: ");
		scanf("%s", playerone);
		printf("Player two's name is: ");
		scanf("%s", playertwo);
		printf("\n");
		printf("%s will be X and %s will be O. Good Luck!\n", playerone, playertwo);

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

////////////////////////////////////////

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
////////////////////////////////////////////////
int AIMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
	int move = 0;
	printf("%d", player);

if(player+1 == 1){
	move = getMove(board, player, PIECES, Board_Columns, BOARD_ROWS);
	return 1; }
else {
	printf("Mykalo is moving");
	int count = 0;
	const int WIDTH = 1;
	const int HEIGHT = 1;
	int C = 0;


	
	for(int i=0; i < BOARD_ROWS; i++){
		for(int j=0; j< Board_Columns; j++){
			count = Board_Columns * i + j;
			if(checkThree(board, count, count + WIDTH, count + WIDTH * 2, count + WIDTH * 3)){
		
				C = count + WIDTH * 3;
				for(int R = BOARD_ROWS - 1; R >= 0; R--){
					if(board[Board_Columns * R + C] == ' '){
						board[Board_Columns * R + C] = PIECES[player];
				 		return 1; }
					}	
				C = count + WIDTH * 2;
			 	for(int R = BOARD_ROWS - 1; R >= 0; R--){
					if(board[Board_Columns * R + C] == ' '){
						board[Board_Columns * R + C] = PIECES[player];
						return 1; }
				}
				C = count + WIDTH;
				for(int R = BOARD_ROWS - 1; R >= 0; R--){
					if(board[Board_Columns * R + C] == ' '){
						board[Board_Columns * R + C] = PIECES[player];
						return 1; }
				}
				C = count;
				for(int R = BOARD_ROWS - 1; R >= 0; R--){
					if(board[Board_Columns * R + C] == ' '){
						board[Board_Columns * R + C] = PIECES[player];
						return 1; }
				}
		
		
			} 
			else {
				C = rand() % Board_Columns;
				for(int R = BOARD_ROWS - 1; R >= 0; R--){
					if(board[Board_Columns * R + C] == ' '){
						board[Board_Columns * R + C] = PIECES[player];
						return 1; } } }
		
		
		} } }
	return 1; }
		



/*
		for(int i = BOARD_ROWS; i >= 0; i--){
			for(int j = 0; j < Board_Columns; j++){
				count = Board_Columns * i + j;

				if(checkThree(board, count, count + WIDTH, count + WIDTH * 2, count + WIDTH * 3)){	
					if(board[Board_Columns * i + j] == ' '){
						board[Board_Columns * i + j] = PIECES[player];
						return 1; }
			       	} } } }
							
							
return 0; }
*/


/////////////////////////////////////////////////
int AIMove2(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
	int move = 0;
	int lastMove = 0;
	int count = 0;
	int col = 0;
	int moveCounter = 0;
	const int Height = Board_Columns;
	const int dleft = Board_Columns + 1;
	const int dright = Board_Columns - 1;

	if(player+1 == 1){
		move = getMove(board, player, PIECES, Board_Columns, BOARD_ROWS);
		return 1; }

	else {
		if (board[Board_Columns * BOARD_ROWS - 4] == ' '){
			board[Board_Columns * BOARD_ROWS - 4] = PIECES[player];
			return 1; }
		else if(board[Board_Columns * BOARD_ROWS - 1] == ' '){
			board[Board_Columns * BOARD_ROWS - 1] = PIECES[player];
	       		return 1;	}
		else{

// Check for 3 in a row X X X ? or O O O ?			
			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count + 1] && board[count + 1] == board[count + 1 * 2] && board[count] != ' '){
						if(board[count + 1 * 3] == ' '){	
						
//							count = Board_Columns * (i-1) + j;
//							if(board[count + 1 * 3] == ' '){
//								break; break; }
			
							count = Board_Columns * i + j;
			
							col = count + 1 * 3;
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
				       		else break; } 	 } }
// Check for 3 in a row ? X X X or ? O O O			
			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;			
					if(board[count + 1] == board[count + 1 * 2] && board[count + 1 * 2] == board[count + 1 * 3] && board[count + 1] != ' '){
						if(board[count] == ' '){
//
//						count = Board_Columns * (i-1) + j;
//						if(board[count] != ' ' || i == 0){
//							count = Board_Columns * i + j;
							col = count;
							for(int row = BOARD_ROWS; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
							} } }

// Check for 3 in a row X ? X X or O ? O O

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count + 1 * 2] && board[count + 1 * 2] == board[count + 1 * 3] && board[count + 1 * 3] != ' '){
						if(board[count + 1] == ' '){
//						count = Board_Columns * (i-1) + j;
//						if(board[count + 1] != ' '){
//							printf("IN LOOP 2");
//							count = Board_Columns * i + j;
							col = count + 1;
							for(int row = BOARD_ROWS-1; row >=0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
							} } }

// Check for 3 in a row X X ? X or O O ? O

			for(int i = 0; i < BOARD_ROWS; i ++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count + 1] && board[count + 1] == board[count + 1 * 3] && board[count + 1 * 3] != ' '){
						if(board[count + 1 * 2] == ' '){
							col = count + 1 * 2;
							for(int row = BOARD_ROWS - 1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
					} } }


// Check for 3 in a row vertical

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count + 1] == board[count + 1 + Height] && board[count + 1 + Height] == board[count + 1 + (Height * 2)] && board[count + 1 + (Height * 2)] != ' '){

						if(board[count + 1 - Height] == ' '){
							board[count + 1 - Height] = PIECES[player];
							moveCounter = 1;
							return 1; }
					} } }		

			
// Check for 3 in a row diagonal

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count - dleft] && board[count - dleft] == board[count - dleft * 2] && board[count] != ' '){
						if(board[count - dleft * 3] == ' '){
							col = count - dleft * 3;
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
					} } }

// Check for 3 in a row diagonal 

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count - dright] && board[count - dright] == board[count - dright * 2] && board[count - dright * 2] != ' '){
						if(board[count - dright * 3] == ' '){
							col = count - dright * 3;
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1;
									return 1; } } }
					} } }



/// Make Random Move if No Best Move is Available
			
			if(moveCounter == 0){			
				count = rand() % Board_Columns;
					for(int r = BOARD_ROWS - 1; r >= 0; r--){
						if(board[Board_Columns * r + count] == ' '){
							board[Board_Columns * r + count] = PIECES[player];
							return 1; } } } }
		
		
		
		return 1; }
}
/////////////////////////////////////////////////	
int checkWin(char *board, int Board_Columns, int BOARD_ROWS){
	return (horizontalCheck(board, Board_Columns, BOARD_ROWS)); }

int checkFour(char *board, int a, int b, int c, int d){
return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' '); }

int checkThree(char *board, int a, int b, int c, int d){
	int count = 0;

	if(board[a] == 'X'){
		count = count + 1; }
	if(board[b] == 'X'){
		count = count + 1; }
	if(board[c] == 'X'){
		count = count + 1; }
	if(board[d] == 'X'){
		count = count + 1; }

	if(count == 3){
		printf("COUNT 3");
		return 1; }
	else {	
		return 0; }

}
	
//	return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' '); }


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

///////////////////////////////////////////////////////////












