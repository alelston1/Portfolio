# Portfolio
> Alexis Elston

> CS 201 - Spring 2019

> Due March 29, 2019

### GitHub ID / Username / Tutorial of Game URL
***48029301 / alelston1***  / https://youtube.com

### Code Style
**All code is written using standard libraries from ANSI C11. All code is written and tested on Ubuntu.**

## Overview of Files
- **portfolio.c**
  - This is the main code. For simplicity of having to download a ZIP file and peer editing, I have decided to only use one C file. This type of coding is not always the best practice, and a header file could have been used, but since this is a project that is contained in less than 1000 lines of code, I felt my decision was reasonable.

- **makefile**
  - The makefile is included for ease of use. When compiling, it runs on the command ./main. All code was compiled using GNU Compiler Collection (gcc). The standard -Wall option flag was used to check for errors and warnings.

- **takeone.c**
  - This is my first attempt at the project. This is where pieces of my project were compiled on a larger scale to test and debug before being implemented in the actual portfolio.c file. This code is only left in the repository to see history, not to be graded or compiled.
  
- **taketwo.c**
  - This is my first attempt at a game. By using Tic Tac Toe, I was able to see what type of implementation I wanted to use on a larger scale game such as Connect Four. This code is only left in the repository to see history, not to be graded or compiled.

### Explanation of Code and Graph Structure
something here





### Example Code
In order to place a move in the correct position, functions often use a piece of code similar to the one shown below. In this case, a  human user is trying to place a marker in the slot held in "col." For this example, say the user entered column 1. The program uses   the information known about the board size to locate which row the chip should be placed in, starting with the bottom row, since when a marker is placed on a real game board, it falls to the bottom. 'row' is initialized to one less than the row size because the row size represents a full row, and we will never need to place a chip in a full row. The player has already entered a column they would like their marker to be placed in. To calculate the first open slot in this column, we do the math of the total board columns available (6 in our case) * the bottom row available (6 in our case). This leads us to the last position in the 5th row due to the adjustment in the initialization of row. We then add the column (1 in our case) to this number and check if that position is empty. If it is, we place the chip and return a success. If not, we move to the next row and try again.

    int getMove(char *board, int player, const char *PIECES, int Board_Columns, int BOARD_ROWS){
        ...
        scanf("%d", &col);
        ...
        for(row = BOARD_ROWS - 1; row >= 0; row--){
            if(board[Board_Columns * row + col == ' '){
                board[Board_Column * row + col] = PIECES[player];
                return 1;
            }
        }
        return 0; }
### Cited Code
1. https://www.programiz.com/dsa/graph-adjacency-list
    - This is the code for the adjacency list and the basic structure of the graphing algorithm my code is based off of.
2. https://codereview.stackexchange.com/questions/27446/connect-four-game
    - This is the code that I modified in order to check for win cases, and how to implement the "PIECES[player]" portion of my code.

## Running Connect Four
> To begin running connect four, download the files and open a command window to compile them. Using the make file, run ./main to begin the game. 

- A series of decisions will need to be made in order to set up the game. Each time the game is to be played, these decisions must be made. These decisions are as followed, and can be made by entering your selection, then pressing 'Enter.' 
    - ONE player or TWO player mode?
        - Is this decision correct?
        - Select a Board Row Size.
        - Select a Board Column Size.
        - Press the '1' key to begin game.
        - Player 1's name is?
            - If two player mode, Player 2's name is?
        - Begin Game

- Once the game is initialized and the board appears, users will be prompted to make selections on where to place a marker. This can be done by entering the desired column, followed by 'Enter.'


### Connect Four Instructions
1. Be the first person to get four markers in a row.
    1. If playing two player, each person should alternate going first. The youngest person should always start game 1 as player 1.
2. '4-in-a-row' can be achieved either **Horizontally, Vertically, Diagonally Up, or Diagonally Down.**

        X                 X       X                                          0      0                 0
          X             X         X         X X X X             0 0 0 0      0        0             0
            X         X           X                                          0          0         0
              X     X             X                                          0            0     0

3. If any of these patterns are achieved, the player who accomplished this daunting task wins!










