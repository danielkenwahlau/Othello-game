#include<stdio.h>
#define ROWS 8
#define COLS 8

/************Notes******************

-Player 1 is X and Player 2 is O
-If the wrong row is entered by mistake then a player can enter a 
character to make the move invalid and the program will automatically re-prompt
the user. However when input it read, it only scans the first character which means
that if a user accidentally enters a valid move that he or she did not intend there is
no undo.
-If a move is valid and you accidentally enter it, there is
no going back like in a real game

***********************************/
int board_array[ROWS][COLS] = {0}; //The board is a global variable that will change as the game goes on

//declaring starting player as one and opposite player as 2
//players are globals that will change every time a switch player statement is encountered
//Also the move is global since it is associated with the current player
int player = 1, opposite_player = 2;
int player_move[2];

//##########################################
//FUNCTION DECLARATIONS

void printplayers();
void printarray();
void printboard();
void printline(void);
void startingconfig();
int player_can_move();
int check_rows_diags(int peice_row,int peice_col);
int collect_player_move(int player);
void skip_remaining_chars();
void update_array(int peice_row,int peice_col);
void switch_player();
int spaces_left();
void determine_winner();
int quit();
//##########################################

//This is more for debugging but will print the current players and you can 
//determine whose turn it is
void printplayers(){
	
	printf("player: %d opposite_player: %d",player, opposite_player);

}

// this will be the function to print the board_array which consists of 1's, 2's and 0's.
void printarray(){
	printf("\n");
	int i,j;
	for (i = 0;i<ROWS;i++){
		for (j = 0; j<COLS; j++){
			printf("%d",board_array[i][j]);
		}
		printf("\n");
	}
}

//Starting configuration for the game to start
void startingconfig(){

board_array[3][3] = 1;
board_array[3][4] = 2;
board_array[4][3] = 2;
board_array[4][4] = 1;

//added for testing
// board_array[2][2] = 1;
// board_array[2][3] = 1;
// board_array[2][4] = 1;
// board_array[2][5] = 1;
// board_array[3][2] = 1;
// board_array[3][5] = 1;
// board_array[4][2] = 1;
// board_array[4][5] = 1;
// board_array[5][2] = 1;
// board_array[5][3] = 1;
// board_array[5][4] = 1;
// board_array[5][5] = 1;


}

//Takes the global variable board_array and translates the 1's, 0's, 2's and translates them to 
//X's, O's and spaces. 
void printboard(){
int counter, i, j;
char char_array[ROWS][COLS];


for(i = 0; i<ROWS; i++){
	for(j = 0; j<COLS; j++){
		if (board_array[i][j] == 1)
			char_array[i][j] = 'X';
		else if( board_array[i][j] == 2)
			char_array[i][j] = 'O';
		else
			char_array[i][j] = ' ';
	}
}

printf(" |");
for (counter = 0; counter < 8; counter++)
	printf(" %d |", counter);
printf("\n");
printline();

for(i = 0; i<ROWS; i++){
//just make a function that will take abc... as a parameter
	switch (i){
		case 0: 	printf("0|");

					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 1: 	printf("1|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 2: 	printf("2|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 3: 	printf("3|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 4: 	printf("4|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 5: 	printf("5|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 6: 	printf("6|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		case 7: 	printf("7|");
					for(j = 0; j <COLS; j++){
						printf(" %c |", char_array[i][j]);
					}
					printf("\n");
					printline();
					break;
		default: 	break;

	}

}

}

//prints the lines that separate the rows of the board
void printline(void){
int counter;
printf("-");
for (counter = 0; counter < 7; counter++)
	printf("-----");
printf("\n");
}

//This function will just use the check_rows_diags function to sweep all the empty spaces on the board
//and determine whether or not the player can move
int player_can_move(){

	int peice_row,peice_col; //possible move is a boolean that will become true once a valid move is found

	//This loop will check each cell on the board to see if there is a valid move for that player
	//will return a one if there is atleast one valid move.
	
	for (peice_row = 0; peice_row < ROWS; peice_row++){
		for (peice_col = 0; peice_col < COLS; peice_col++){

			if((check_rows_diags(peice_row,peice_col) && board_array[peice_row][peice_col] == 0))//will return a 1 if a valid move and the space is empty
				return 1;
			else
				continue;
			printf("\n");
		}
		
	}
}

//This will be more specific in check for a single move space
int check_rows_diags(int peice_row,int peice_col){

	//if the move is not a 0, which means empty, then the move is automatically 
	//not valid
	if (board_array[peice_row][peice_col] != 0)
		return 0;

	int i,j;
	int found_opposite;
	//This will check all the rows, columns and diagonals for a valid move.
	//The algorithm scans clockwise and directions are like that of a compass
	//*************************************
	//Checks the rows above the piece NORTH

	for(j = peice_col, i = peice_row-1,found_opposite = 0;i>=0; i--){
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1; 
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1; 
		}
		
	}
	
	//*************************************		

	//*************************************
	//Checks the upper right NORTHEAST.
	for(j = peice_col+1, i = peice_row-1,found_opposite = 0; j<COLS && i>=0; i--,j++){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the columns to the right of the piece EAST
	for(j = peice_col+1, i = peice_row,found_opposite = 0;j<COLS; j++){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the bottom right SOUTHEAST	.
	for(j = peice_col+1, i = peice_row+1,found_opposite = 0; j<COLS && i<ROWS; i++,j++){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the rows under the piece SOUTH
	for(j = peice_col, i = peice_row+1,found_opposite = 0;i<ROWS; i++){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the bottom left. SOUTHWEST
	for(j = peice_col-1, i = peice_row+1,found_opposite = 0; j>=0 && i<ROWS; i++,j--){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the columns to the left of the piece WEST
	for(j = peice_col-1, i = peice_row,found_opposite = 0;j>=0;j--){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************		
	//*************************************
	//Checks the top left diagonal NORTHWEST
	for(j = peice_col-1, i = peice_row-1,found_opposite = 0; j>=0 && i>=0; i--,j--){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				return 1;
			} else {
				break;
			}
		} else if( board_array[i][j] == 0) {
			break;
		} else {
			found_opposite = 1;
		}
		
	}
	//*************************************	
	//if nothing catches, then it returns a 0, which means there are no similar pieces in the diagonals
	return 0;
		
}

//This take the player move and changes the array according to the player and the move
void update_array(int peice_row,int peice_col){

	int i,j;
	int found_opposite;
	int valid_flip;

	//*************************************
	//NORTH
	
	for(j = peice_col, i = peice_row-1,found_opposite = 0,valid_flip = 0;i>=0; i--){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
				
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col, i = peice_row-1;board_array[i][j] == 3; i--)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col, i = peice_row-1;board_array[i][j] == 3; i--)
				board_array[i][j] = opposite_player;
	}
	//*************************************
	//*************************************
	//NORTHEAST
	
	for(j = peice_col+1, i = peice_row-1,found_opposite = 0,valid_flip = 0; j<COLS && i>=0; i--,j++){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col+1, i = peice_row-1; board_array[i][j] == 3; i--,j++)//******
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col+1, i = peice_row-1; board_array[i][j] == 3; i--,j++)//******
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//EAST 
	
	for(j = peice_col+1, i = peice_row,found_opposite = 0, valid_flip = 0;j<COLS; j++){

		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col+1, i = peice_row;board_array[i][j] == 3; j++)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col+1, i = peice_row;board_array[i][j] == 3; j++)
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//SOUTHEAST
	
	for(j = peice_col+1, i = peice_row+1,found_opposite = 0,valid_flip = 0; j<COLS && i<ROWS; i++,j++){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
			for(j = peice_col+1, i = peice_row+1;board_array[i][j] == 3; i++,j++)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col+1, i = peice_row+1;board_array[i][j] == 3; i++,j++)
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//SOUTH 
	
	for(j = peice_col, i = peice_row+1,found_opposite = 0,valid_flip = 0; i<ROWS; i++){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col, i = peice_row+1; board_array[i][j] == 3; i++)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col, i = peice_row+1; board_array[i][j] == 3; i++)
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//SOUTHWEST
	
	for(j = peice_col-1, i = peice_row+1,found_opposite = 0,valid_flip = 0; j>=0 && i<ROWS; i++,j--){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col-1, i = peice_row+1;board_array[i][j] == 3; i++,j--)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col-1, i = peice_row+1;board_array[i][j] == 3; i++,j--)
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//WEST
	
	for(j = peice_col-1, i = peice_row,found_opposite = 0, valid_flip = 0;j>=0;j--){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col-1, i = peice_row;board_array[i][j] == 3;j--)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col-1, i = peice_row;board_array[i][j] == 3;j--)
				board_array[i][j] = opposite_player;
	}
	//*************************************	
	//*************************************
	//NORTHWEST
	
	for(j = peice_col-1, i = peice_row-1,found_opposite = 0, valid_flip = 0; j>=0 && i>=0; i--,j--){
		
		if(board_array[i][j] == player) { 
			if (found_opposite) {
				valid_flip = 1; 
				break;
			} else {
				break; 
			}
		} else if( board_array[i][j] == 0) {
			break; 
		} else {
			found_opposite = 1;
			board_array[i][j] = 3;	
		}
		
	}

	if (valid_flip){
		board_array[peice_row][peice_col] = player;
		for(j = peice_col-1, i = peice_row-1;board_array[i][j] == 3; i--,j--)
				board_array[i][j] = player;
	}
	else{ 
		for(j = peice_col-1, i = peice_row-1;board_array[i][j] == 3; i--,j--)
				board_array[i][j] = opposite_player;
	}
	//*************************************	

	
}

//This is the revised collect player move that I am trying to fix
int collect_player_move(int player){
	
	if(player == 1)
		printf("\n********PLAYER 1********\n");
	else
		printf("\n********PLAYER 2********\n");
	
	//create new variables to store input first
	char row, col;
	printf("Enter the row, q to quit: ");
	scanf("%c", &row);
	skip_remaining_chars();
	printf("Enter the column number q to quit: ");
	scanf("%c", &col);
	skip_remaining_chars();
	
	//Here I check the quit condition, and if it is not quit, the I assign the integer value to the global variable array player_move
	
	if ((row == 'q') || (row == 'Q') || (col == 'q') || (col == 'Q'))//quits and returns -1 when a q for quit is found
		return -1;
	else if( (row>= '0') && (row <= '9') && (col >= '0') && (col <= '9')){//basically  says if the input is a character
		
		player_move[0] = row - '0';
		player_move[1] = col - '0';
		
		return 1;
	}
	else 
		return 0;
		
	
	

}

//For skipping the new-line character at the end of the user input
void skip_remaining_chars(){
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

}



//accesses the players and switches them each time the function is called.
void switch_player(){
	if (player == 1){
		player = 2;
		opposite_player = 1;
	}
	else if (player == 2){
		player = 1;
		opposite_player = 2;
	}
	else
		1;
}

//This function will check to see if any spaces are left
int spaces_left(){

	int row,col;
	for (row = 0; row<ROWS; row++){
		for (col = 0; col<COLS; col++){
			if (board_array[row][col] == 0)
				return 1;
			else
				continue;
		}
	}
	//if there are no 0's then it will return a 0 which means no spaces
	return 0;
}

//counts the number of 1's and 2's which correspond to X's and O's and determines the winner
void determine_winner(){

int X_count = 0, O_count = 0,row,col;

	for (row = 0; row<ROWS; row++){
		for (col = 0; col<COLS; col++){
			if (board_array[row][col] == 1)
				X_count++;
			else if (board_array[row][col] == 2)
				O_count++;
			else
				continue;
		}
	}

	if (X_count > O_count){
		printf("\n X: %d O: %d", X_count, O_count);
		printf("\nPlayer 1 (X) is winner!\n");
	}
	else if (X_count < O_count){
		printf("\n X: %d O: %d", X_count, O_count);
		printf("\nPlayer 2 (O) is winner!\n");
	}
	else{
		printf("\n X: %d O: %d", X_count, O_count);
		printf("\nIt's a Tie!\n");
	
	}
		

}


//main loop that starts the game and includes the loop where the players play
int main(void){


	startingconfig(board_array);
	printboard();
	
	printf("player: %d is X player: %d is O\n", player, opposite_player);

	int turns_skipped = 0;
	int quit;
	
	
	//Main loop that continues when there are spaces left, and when the number of turns skipped is less
	//than two. When turns_skipped = 2, it means that both players' turns were skipped and the loop should end
	 while (spaces_left() && turns_skipped <2 ){
		
		
		
		//if the player can move then take the move and update the board
		if (player_can_move()){
		
			if(collect_player_move(player) == -1)//breaks if q is entered as input
				break;
				
			//mainly checking if the move the move the player picked was not ok. If it is not ok
			//then it will keep looping until you pick a valid move
			while(check_rows_diags(player_move[0],player_move[1]) == 0){
				printboard(board_array);
				printf("\nThat was not a valid move\n");
				quit = collect_player_move(player);//breaks if q is entered, which returns -1
				if(quit == -1)
					break;

			}
			if(quit == -1)
				break;
			
			//At this point the move is valid so update the array and reset the turns skipped
			update_array(player_move[0],player_move[1]);
			printboard(board_array);
			turns_skipped = 0;
		}
		//If there are no moves, increment the number of turns skipped and switch the player
		else{
			printf("\nNo moves for player: %d\n", player);
			turns_skipped++;
		}
		switch_player();
	}
	
	printboard();
	determine_winner();

	return 0;
}



