/*Alexis Elston
 * CS201 - Spring 2019
 * Portfolio Due March 29 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// initialize functions

int gameIntro();
void setBoardEMPTY(char *board, int Board_Columns, int BOARD_ROWS);
int getMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS);
int makeMove2(int move);
int checkWin(char *board, int Board_Columns, int BOARD_ROWS);
int checkFour(char *board, int a, int b, int c, int d);
int checkThree(char *board, int a, int b, int c, int d);
int horizontalCheck(char *board, int Board_Columns, int BOARD_ROWS);
int AIMove2(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS);
struct Graph* createGraph(int vertices);
void addEdge();
void printGraph();

// Start main function

int main(int argc, char *argv[]){
	char playerone[25];
	char playertwo[25];
	int gameMode = 0;
	int Board_Columns = 6;
	int BOARD_ROWS = 7;
	int breaker = 0;

// Use game intro to determine whether to play one or two player mode

	gameMode = gameIntro();
	int player, turn, done = 0;

/////////////////////////////////////////////////
// From this point, choose a game board size

	printf("Now select a game board size. The recommended minimum size is 6 rows and 7 columns. It is recommended to not exceed 15 x 15.");
	printf("\nBoard Rows: ");
	scanf("%d", &BOARD_ROWS);

// Verify that input is valid, not a letter. If invalid character, use the standard board size of 6 by 7. Use breaker to break out of loop if a character is entered that is not valid. First scan rows, then scan columns. If an invalid row is entered, do not scan in column.

while((breaker = 0)){
	while(BOARD_ROWS >= 40 || BOARD_ROWS < 6){
		if(isdigit(BOARD_ROWS) != 0){
			printf("Invalid board size. The default row will be used.\n");
			breaker = 1;
			break; }		
		printf("That board size is invalid. Please select a row size between 6 and 40: ");
		scanf("%d", &BOARD_ROWS);	}
}

// Scan for column if valid row was entered

if(breaker == 0){
	printf("Board Columns: ");
	scanf("%d", &Board_Columns);
}
	
while((breaker = 0)){	
	while(((Board_Columns > 40) || (Board_Columns < 7)) && (breaker != 1)){
		if(isdigit(Board_Columns) != 0){
			printf("Invalid board size. The default column will be used.\n");
			breaker = 1;
			break; }
		
		printf("That board size is invalid. Please select a column size between 7 and 40: ");
		scanf("%d", &Board_Columns);	}
}

///////////////////////////////////////////////////
// Use this catchall to stop any unwanted input from crashing program. This is used when an invalid board size is entered, causing overflow of command line input

if(breaker == 0){
	char catchall[5];
	printf("Press the '1' key and 'Enter' to continue: ");
	scanf("%s", catchall);
}

// Set player 1 to 'X' and player 2 to 'O'

	const char *PIECES = "XO";
// Set board size, set the memory to remember any changes to the board

	char board[BOARD_ROWS * Board_Columns];
	memset(board, ' ', BOARD_ROWS * Board_Columns);

/////////////////////////////////////////////
// Decide which mode to enter from this point forward. If gameMode returns 1, then play against computer
	
	if (gameMode == 1){
		printf("This is ONE PLAYER GAME MODE");
		printf("\n\nWelcome to one-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
		printf("Player one's name is: ");
		scanf("%s", playerone); //Get player 1's name
		printf("%s will be playing against me, Mykalo. Best of luck, I don't lose!", playerone);
		
// Set board empty to start game
		for(turn = 0; turn < BOARD_ROWS * Board_Columns && !done; turn++){

			setBoardEMPTY(board, Board_Columns, BOARD_ROWS);

// While the board is not full, enter AIMove2 function
			while(!AIMove2(board, turn % 2, PIECES, Board_Columns, BOARD_ROWS)){

				setBoardEMPTY(board, Board_Columns, BOARD_ROWS); //print board
				puts("**Column FULL!**\n"); } // if move is in a column that has no remaining moves, warn user
			done = checkWin(board, Board_Columns, BOARD_ROWS); // check for a winner
		}
		setBoardEMPTY(board, Board_Columns, BOARD_ROWS); //print board

// If the amount of turns = Board Rows * Board Columns, and no winner is found, then return board is full and game ends in tie.		
		if(turn == BOARD_ROWS * Board_Columns && !done){
			puts("It's a tie!"); }

// If a winner is found in above while loop, print the correct statement
		else{
			turn = turn - 1; // use turn that winner was found on
			player = turn % 2 + 1; //adjust for even or odd turn
			if(player == 2){
				
				printf("HA! I told you I would beat you, YOU LOSE!\n"); }
			else{
				
				printf("Rats... you've beat me this time. Congratulations %s!\n", playerone); }
		} 
	
	}

//////////////////////////////////////////
// If game mode returns 2, play against another human player

	else if (gameMode == 2){
// Get player names, if whitespace is entered for player name, then players forfeit rights to select other game options and begin playing. Names will set to before and after whitespace was entered for player one and two respectively.
		
		printf("\n\n\nWelcome to two-player mode. Please enter a nickname below. No whitespaces can be entered. \n");
		
		printf("Player one's name is: ");
		scanf("%s", playerone); // Get Player 1's name
		printf("Player two's name is: ");
		scanf("%s", playertwo); // Get Player 2's name
		printf("\n");
		printf("%s will be X and %s will be O. Good Luck!\n", playerone, playertwo);

//Determine who's turn it is and use getMove function to determine next board state
		
		for(turn = 0; turn < BOARD_ROWS * Board_Columns && !done; turn++){
			setBoardEMPTY(board, Board_Columns, BOARD_ROWS); //print board
			while(!getMove(board, turn % 2, PIECES, Board_Columns, BOARD_ROWS)){
				setBoardEMPTY(board, Board_Columns, BOARD_ROWS); //print board
				puts("**Column FULL!**\n"); } // warn user if column has no more valid moves
			done = checkWin(board, Board_Columns, BOARD_ROWS); //check for winner
		}
		setBoardEMPTY(board, Board_Columns, BOARD_ROWS); //print board

// if turn = Board Rows * Board Columns and no winner is found, then board must be full and game ends in tie
		
		if(turn == BOARD_ROWS * Board_Columns && !done){
			puts("It's a tie!"); }
// if winner is found, print correct statement
		else{
			turn = turn - 1; // set to turn where winner was determined
			player = turn % 2 + 1; //adjust for even or odd turn
			if(player == 1){
				printf("%s Wins!\n", playerone); }
			else{
				printf("%s Wins!\n", playertwo); }
		}	}

////////////////////////////////////////
// In case of error early on, terminate game before entering infinite while loop

	else {
		printf("FATAL ERROR: GAME TERMINATED"); }


	return 0;
}


///////////////////////////////////////////////////////////////////////////////
// This function will be the first thing a user enters in the program. Get and return game mode. Give user two chances to pick correct game mode by using confirmation statement. If invalid character is entered on confirmation screen, automatically default to second option available

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
// Function to print board at current state

void setBoardEMPTY(char *board, int Board_Columns, int BOARD_ROWS){
	int row, column;
	printf("\n\n");
	puts("\n		-Connect Four-	\n");
	for(row = 0; row < BOARD_ROWS; row++){
		for(column = 0; column < Board_Columns; column++){
			printf("| %c   ", board[Board_Columns * row + column]); // character is either ' ', 'X', or 'O'
		}
		puts("|");
		puts("                    ");
	}
	printf("   ");
// Prints column index across bottom of screen

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
// For a human player, this function will scan input and place piece in appropriate place

int getMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
	int row, col = 0;
	printf("Player %d (%c), which column would you like to place your token?\n", player + 1, PIECES[player]);
	while(1){
		scanf("%d", &col);
// move must be in a valid slot, cannot exceed board size or be a non integer
		if(col > Board_Columns || col < 1){
			while(getchar() != '\n');
			puts("Invalid Column. Please enter a new column."); }
		else{
			break; }}
	col--;

// placing move
	for(row = BOARD_ROWS - 1; row >= 0; row--){
		if(board[Board_Columns * row + col] == ' '){
			board[Board_Columns * row + col] = PIECES[player];
			return 1;
		}
	}
	return 0; }

////////////////////////////////////////////////
// set up adjacency list for graph to determine next best move for AI component
// https://www.programiz.com/dsa/graph-adjacency-list
// Modified code from above website

struct node{
	int vertex;
	struct node* next; };

struct node* createNode(int);

struct Graph{
	int numVertices;
	struct node** adjLists; };

//create nodes and allocate space
struct node* createNode(int v){
	struct node* newNode = malloc(sizeof(struct node));
	newNode -> vertex = v;
	newNode -> next = NULL;
	return newNode; }

//create graph and allocate space	
struct Graph* createGraph(int vertices){
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->numVertices = vertices;

	graph->adjLists = malloc(vertices * sizeof(struct node*));

	int i;
	for(i = 0; i < vertices; i++)
		graph->adjLists[i] = NULL;

	return graph; }

//Add edge between two vertices
void addEdge(struct Graph* graph, int src, int dest){
	struct node* newNode = createNode(dest);
	newNode->next = graph->adjLists[src];
	graph->adjLists[src] = newNode;

	newNode = createNode(src);
	newNode->next = graph->adjLists[dest];
	graph->adjLists[dest] = newNode; }

//If needed, print list of adjecencies to see which vertices are connected
void printGraph(struct Graph* graph){
	int v;
	for(v = 0; v< graph->numVertices; v++){
		struct node* temp = graph->adjLists[v];
		printf("\n Adjacency list of vertex %d\n ", v);
		while(temp){
			printf("%d -> ", temp->vertex);
			temp = temp->next; }
		printf("\n");
	}
}
	
	
/////////////////////////////////////////////////
// This function determines next best move by using a graph search to look at each index and determine if it will result in winning state. The graph is developed from
// https://codereview.stackexchange.com/questions/27446/connect-four-game
// More details on why this approach was chosen and implementation choices is found in ReadMe.md

int AIMove2(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
	int count = 0;
	int col = 0;
	int moveCounter = 0;
	const int Height = Board_Columns;
	const int dleft = Board_Columns + 1;
	const int dright = Board_Columns - 1;
// graph for adjacency list
	struct Graph* graph = createGraph(BOARD_ROWS * Board_Columns);

// if player 1's turn (human), use getMove to determine and place move
	if(player+1 == 1){
		getMove(board, player, PIECES, Board_Columns, BOARD_ROWS);
		return 1; }
// player 2's turn (computer). Since board does not have enough moves to determine best placement, always place first two moves in constant spot.
	else {
		if (board[Board_Columns * BOARD_ROWS - 4] == ' '){
			board[Board_Columns * BOARD_ROWS - 4] = PIECES[player];
			return 1; }
		else if(board[Board_Columns * BOARD_ROWS - 1] == ' '){
			board[Board_Columns * BOARD_ROWS - 1] = PIECES[player];
	       		return 1;	}

// Use board state to determine next best move

		else{
			
// Check for 3 in a row X X X ? or O O O ?			
		
			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;					
					if(board[count] == board[count + 1] && board[count + 1] == board[count + 1 * 2] && board[count] != ' '){
						//if 3 in a row, determine if next best move would be to the right of the set. Check if move is possible
						if(board[count + 1 * 3] == ' '){ //is move open?
							count = Board_Columns * i + j;

							addEdge(graph, count, count + 1);	//link vertices in adjacency list
							addEdge(graph, count, count + 1);
							addEdge(graph, count, count + 1 * 2);
								
							col = count + 1 * 3;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; //update moveCounter to bypass random move at end of function
									return 1; } } }
						//if no connections are found or move is not practical, move to next set and try again
						else break; } 	 } }

					
// Check for 3 in a row ? X X X or ? O O O			
			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;			
					if(board[count + 1] == board[count + 1 * 2] && board[count + 1 * 2] == board[count + 1 * 3] && board[count + 1] != ' '){
						if(board[count] == ' '){ //is move open?
						//check if next best move is board[count]

							addEdge(graph, count, count + 1);	//link vertices in adjacency list
							addEdge(graph, count, count + 1 * 2);
							addEdge(graph, count, count + 1 * 3);
							

							col = count;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; // update moveCounter to bypass random move at end of function
									return 1; } } }
							//if no connections are found or move is not practical, move to next set and try again
							} } }

// Check for 3 in a row X ? X X or O ? O O

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count + 1 * 2] && board[count + 1 * 2] == board[count + 1 * 3] && board[count + 1 * 3] != ' '){
						if(board[count + 1] == ' '){ //is move open?
						//check if next best move is board[count + 1]

							addEdge(graph, count, count + 1);	//link vertices in adjacency list
							addEdge(graph, count, count + 1 * 2);
							addEdge(graph, count, count + 1 * 3);

							col = count + 1;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS-1; row >=0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; // update moveCounter to bypass random move at end of function
									return 1; } } }
							//if no connections are found or move is not practical, move to next set and try again
							} } }

// Check for 3 in a row X X ? X or O O ? O

			for(int i = 0; i < BOARD_ROWS; i ++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count + 1] && board[count + 1] == board[count + 1 * 3] && board[count + 1 * 3] != ' '){
						if(board[count + 1 * 2] == ' '){ // is move open?
						//check if next best move is board[count + 1 * 2]

							addEdge(graph, count, count + 1);	//link vertices in adjacency list
							addEdge(graph, count, count + 1 * 2);
							addEdge(graph, count, count + 1 * 3);

							col = count + 1 * 2;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS - 1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; //update moveCounter to bypass random move at end of function
									return 1; } } }
							//if no connections are found or move is not practical, move to next set and try again
							} } }


// Check for 3 in a row vertical

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count + 1] == board[count + 1 + Height] && board[count + 1 + Height] == board[count + 1 + (Height * 2)] && board[count + 1 + (Height * 2)] != ' '){

						if(board[count + 1 - Height] == ' '){ // is move open?
						//check if next best move is board[count + 1 - Height of board]

							addEdge(graph, count + 1, count + 1 + Height);		//link vertices in adjacency list
							addEdge(graph, count + 1, count + 1 + Height * 2);
							addEdge(graph, count + 1, count + 1 - Height);

							//if determined to be next best move, then place move
							board[count + 1 - Height] = PIECES[player];
							moveCounter = 1; //update moveCounter to bypass random move at end of function
							return 1; }
					//if no connections are found or move is not practical, move to next set and try again	
					} } }		

			
// Check for 3 in a row diagonal

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count - dleft] && board[count - dleft] == board[count - dleft * 2] && board[count] != ' '){
						if(board[count - dleft * 3] == ' '){ //is move open?
						//check if next best move is board[count - dleft * 3]

							addEdge(graph, count, count - dleft);		//link vertices in adjacency list
							addEdge(graph, count, count - dleft * 2);
							addEdge(graph, count, count - dleft * 3);


							col = count - dleft * 3;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; //update moveCounter to bypass random move at end of function
									return 1; } } }
					//if no connections are found or move is not practical, move to next set and try again
					} } }

// Check for 3 in a row diagonal 

			for(int i = 0; i < BOARD_ROWS; i++){
				for(int j = 0; j < Board_Columns; j++){
					count = Board_Columns * i + j;
					if(board[count] == board[count - dright] && board[count - dright] == board[count - dright * 2] && board[count - dright * 2] != ' '){
						if(board[count - dright * 3] == ' '){ //is move open?
						//check if next best move is board[count - dright * 3]

							addEdge(graph, count, count - dright);		//link vertices in adjacency list
							addEdge(graph, count, count - dright * 2);
							addEdge(graph, count, count - dright * 3);

							col = count - dright * 3;
							//if determined to be next best move, then place move
							for(int row = BOARD_ROWS-1; row >= 0; row--){
								if(board[Board_Columns * row + col] == ' '){
									board[Board_Columns * row + col] = PIECES[player];
									moveCounter = 1; // update moveCounter to bypass random move at end of function
									return 1; } } }
					//if no connections are found or move is not practical, place move in random available slot. All possible 3 in a row's have been checked and this is the extent of the depth search for this program.
					} } }



/// Make Random Move if No Best Move is Available. Double check that moveCounter still is at zero before entering random move
			
			if(moveCounter == 0){			
				count = rand() % Board_Columns; //place within board size
					for(int r = BOARD_ROWS - 1; r >= 0; r--){
						if(board[Board_Columns * r + count] == ' '){
							board[Board_Columns * r + count] = PIECES[player];
							return 1; } } } }
		
		
		return 1; }
}

/////////////////////////////////////////////////	
// check all possible winning states
int checkWin(char *board, int Board_Columns, int BOARD_ROWS){
	return (horizontalCheck(board, Board_Columns, BOARD_ROWS)); }
/////////////////////////////////////////////////
// check that all four board positions equal each other, and are not empty spaces (must be an 'X' or an 'O' to return true

int checkFour(char *board, int a, int b, int c, int d){
return (board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && board[a] != ' '); }

/////////////////////////////////////////////////
// check all possible winning states


int horizontalCheck(char *board, int Board_Columns, int BOARD_ROWS){
	int count = 0;


////////////	check horizontal /////////////////////////

	const int WIDTH = 1; // width of each column is 1 space

	for(int row=0; row < BOARD_ROWS; row++){
		for(int col=0; col < Board_Columns - 3; col++){ // no need to traverse through last 3 columns since 4 in a row uses at least last 4 columns
			count = Board_Columns * row + col; // * row to get the correct row, then add col to move left the needed amount to land on correct space
			if(checkFour(board, count, count + WIDTH, count + (WIDTH * 2), count + (WIDTH * 3))){
				return 1; }
		}
	}

/////////////	check vertical ///////////////////////////

	const int HEIGHT = Board_Columns; // if board is 10 by 10, then slots 0, 10, 20, 30 will be stacked vertically on top of each other. Therefore, set height to column size

	for(int row = 0; row < BOARD_ROWS - 3; row++){ //no need to traverse through top 3 rows since 4 in a row uses at least top 4 rows
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(checkFour(board, count, count + HEIGHT, count + (HEIGHT * 2), count + (HEIGHT * 3))){
				return 1; }
		}
	}

//////////////	check diagonal going right ///////////////////

	const int D_RIGHT = Board_Columns - 1; // to check diagonal spaces, adjust so that stack is on a diagonal plane. Increase or decrease the column size in order to shift each index over by one either way. 
	int hold = 0; //must be at least 3 slots away from edges to have diagonal connections

	for(int row = 0; row < BOARD_ROWS - 3; row++){ //no need to traverse through top 3 rows since 4 in a row uses at least top 4 rows
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(hold >=3 && checkFour(board, count, count + D_RIGHT, count + D_RIGHT * 2, count + D_RIGHT * 3)){
				return 1; }
			hold ++;
		}
		hold = 0;
	}

/////////////	check diagonal going left /////////////////

	const int D_LEFT = Board_Columns + 1;
	hold = 0; // reset hold from used above

	for(int row = 0; row < BOARD_ROWS - 3; row ++){ // no need to traverse through top 3 rows since 4 in a row uses at least top 4 rows
		for(int col = 0; col < Board_Columns; col++){
			count = Board_Columns * row + col;
			if(hold <=3 && checkFour(board, count, count + D_LEFT, count + D_LEFT * 2, count + D_LEFT * 3)){
				return 1; }
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////
// END OF CODE	
