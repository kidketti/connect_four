#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define ROW 6	//there are 6 rows on a connect four board
#define COL 7	//there are 7 columns on a connect four board

void start_game();
void how_to_play();
void print_board(char *board, int player, const char *marker);
int player_turn(char *board, int player, const char *marker);
int check_all(char *board);
int check_four(char *board, int, int, int, int);
int check_vertical(char *board);
int check_horizontal(char *board);
int check_diagonal(char *board);
int check_tie(int, int);
void finish_menu();

//print the main menu	
void start_game(){	
	system("clear");

	printf("+------------------+\n");
	printf("|   Connect Four   |\n");
	printf("+------------------+\n");
	printf("| (1) Start Game   |\n");
	printf("| (2) How To Play  |\n");
	printf("| (3) Exit         |\n");
	printf("+------------------+\n");
}

//print a how to play description menu
void how_to_play(){
	system("clear");	

	printf("+----------------------------------------------------------------------------------------------------+\n");
        printf("|                                           How To Play                                              |\n");
        printf("+----------------------------------------------------------------------------------------------------+\n");
	printf("| Description:                                                                                       |\n");
	printf("| Connect Four is a game in which two players are assigned two different colored tokens/markers.     |\n");
	printf("| These token/marker colors vary from black and red, or yellow and red. In this program, the         |\n");
	printf("| *X* symbol and *O* symbol represents the tokens/markers as it would in Tic-Tac-Toe.                |\n");
	printf("|                                                                                                    |\n");
	printf("| Objective:                                                                                         |\n");
	printf("| The objective of the game is to be the first player to connect four of the same symbols            |\n");
	printf("| in a row on the playboard. This can happen vertically, horizontally, and/or diagonally.            |\n");
	printf("|                                                                                                    |\n");
	printf("| How to Play:                                                                                       |\n");
	printf("| -Decide who wants to go first (Player 1). This player is assigned the *X* symbol.                  |\n");
	printf("|  The second player (Player 2) is assigned the *O* symbol.                                          |\n");
	printf("|                                                                                                    |\n");
	printf("| -The player's turns are alternated. After a column number is selected, that player will            |\n");
	printf("|  *drop* their piece to the next available slot of that column.                                     |\n");
	printf("|                                                                                                    |\n");
	printf("| -Continue until one player wins, or the board is completely filled and there is a tie.             |\n");
	printf("|                                                                                                    |\n");
	printf("|                                           (1) Back                                                 |\n");
	printf("+----------------------------------------------------------------------------------------------------+\n");
}

//prints the playboard
void print_board(char *board, int player, const char *marker){
	system("clear");
	
	printf("     ******************\n");
        printf("     *  Connect Four  *\n");
        printf("     ******************\n\n");
	printf(" Player %d (%c) - Player %d (%c)\n\n", player + 1, marker[player], player + 2, marker[player + 1]);	//prints player and marker key

	for(int row = 0; row < ROW; row++){
      		for(int col = 0; col < COL; col++){
         		printf("|");
			printf(" %c ", board[(COL * row) + col]);	//print spaces in the board
      		}
      		
		printf("|\n");
      
		printf("+---+---+---+---+---+---+---+\n");

   	}
   	
	printf(" |1| |2| |3| |4| |5| |6| |7|\n");

}

//function for the player's turn
int player_turn(char *board, int player, const char *marker){
	int row, col = 0;
   	
	printf("\n+---------------+\n");
	printf("| Player %d Turn |\n", player + 1);
	printf("+---------------+\n");
	printf("\nEnter a slot number: ");

   	for(;;){ 	//loop forever
      		if(scanf("%d", &col) != 1 || col < 1 || col > 7 ){	//if input does not equal 1 or is out of bounds
        		while(getchar() != '\n');	//while does not equal new line
       			
			printf("\nINVALID Input! Try again: ");	
      		} 

		else { 
         		break;	//else break
     		}
   	}
   
	col--;	//decrement col

   	for(row = ROW; row >= 0; row--){	//start from last row in board
      		if(board[COL * row + col] == ' '){
         		board[COL * row + col] = marker[player];	//place marker in board in relation to the player input
         		
			return 1;
      		}
   	}
	
	return 0;
}

//check for a win in all directions 
int check_all(char *board){
	return (check_vertical(board) || check_horizontal(board) || check_diagonal(board));	//return if one of the conditions are met
}

//check for four in a row
int check_four(char *board, int s1, int s2, int s3, int s4){
	return (board[s1] == board[s2] && board[s2] == board[s3] && board[s3] == board[s4] && board[s1] != ' ');	//return all slots next to one another on the board
}

//check for a vertical win condition
int check_vertical(char *board){
	int row, col, index;
    	const int height = 7;

	for(row = 0; row < ROW - 3; row++){
       		for(col = 0; col < COL; col++){
          		index = COL * row + col;	//set the index
          		
			if(check_four(board, index, index + height, index + height * 2, index + height * 3)){	//call check_four function to check for a vertical win
              			return 1;
          		}
       		}
    	}
	
	return 0;
}

//check for a horizontal win condition 
int check_horizontal(char *board){
	int row, col, index;
    	const int width = 1;

	for(row = 0; row < ROW; row++){
       		for(col = 0; col < COL - 3; col++){
          		index = COL * row + col;	//set the index
          		
			if(check_four(board, index, index + width, index + width * 2, index + width * 3)){	//call check_four function for horizontal win
             			return 1;
          		}
       		}
    	}

	return 0;
}

//check for a diagonal win condition
int check_diagonal(char *board){
	int row, col, index, count = 0;
   	const int right_diagonal = 6, left_diagonal = 8;

	for(row = 0; row < ROW - 3; row++){
      		for(col = 0; col < COL; col++){
         		index = COL * row + col;	//set the index in the board
         
			//if function uses a count variable and calls the check_four function to check for diagonal wins
			if(count <= 3 && check_four(board, index, index + left_diagonal, index + right_diagonal * 2, index + left_diagonal * 3) || count >= 3 && check_four(board, index, index + right_diagonal, index + right_diagonal * 2, index + right_diagonal * 3)){
            			return 1;
         		}
		
			count++;	//increment count
		}
	
		count = 0;	//reset count
	}
	
	return 0;
}

//function to check for a tie game
int check_tie(int turn, int finish){
	if(turn == ROW * COL && !finish){       //if turn is the same as board and is not finish, it's a tie
		printf("\n+---------------------+\n");
		printf("| +-----------------+ |\n");
		printf("| |  **Tie Game!**  | |\n");
		printf("| +-----------------+ |\n");
		printf("+---------------------+\n\n");

	}

        else{
        	turn--;
                printf("\n+--------------------+\n");
                printf("| +----------------+ |\n");
                printf("| | Player %d WINS! | |\n", turn % 2 + 1);
                printf("| +----------------+ |\n");
                printf("+--------------------+\n\n");
	}

}

//print an endgame menu
void finish_menu(){
	printf("+----------------+\n");
        printf("| (1) Retry      |\n");
	printf("| (2) Main Menu  |\n");
        printf("| (3) Exit       |\n");
        printf("+----------------+\n");

}


int main(){
	int select = 0, back_select = 0, finish_select = 0;
	char board[ROW * COL];
	const char *marker = "XO";	//assign the marker to a character
	int player;

	reselect:
	
	int turn = 0, finish = 0;

	start_game();
	
	printf("\nEnter a Selection: ");
	
	scanf("%d", &select);
 
	reset:
	
	turn = 0, finish = 0;	//reset turn and finish

	memset(board, ' ', ROW * COL);        //set board memory to space

	while(select == 1){
		system("clear");

		for(turn = 0; turn < ROW * COL && !finish; turn++){
                	print_board(board, player, marker);

			//while the column is full print the board and column full message
               		while(!player_turn(board, turn % 2, marker)){
                       		print_board(board, player, marker);
                       		printf("\n**That Column is FULL!**\n");
               		}

               		finish = check_all(board);	//set finish to check_all function
       		}

       		print_board(board, player, marker);

		check_tie(turn, finish);

		break;
	}
	
	if(select == 2){
		how_to_play();

		printf("\nEnter a Selection: ");

        	scanf("%d", &back_select);


		if(back_select == 1){
			goto reselect;
		}
	}

	if(select == 3){
			system("clear");

                        printf("+------------------------+\n");
                        printf("| Thank You For Playing! |\n");
                        printf("+------------------------+\n");

                        exit(0);
	}

	if(select < 1 || select > 3){
		system("clear");
		printf("***INVALID Selection! Make Another Selection***\n\n");
		goto reselect;
	}

	finish_reselect:

	finish_menu();

 	printf("\nEnter a Selection: ");

        scanf("%d", &finish_select);

	if(finish_select == 1){
		goto reset;
	}
 	
	if(finish_select == 2){
		goto reselect;
	}

	if(finish_select == 3){
        	system("clear");

                printf("+------------------------+\n");
                printf("| Thank You For Playing! |\n");
                printf("+------------------------+\n");

                exit(0);
        }

        if(finish_select < 1 || finish_select > 3){
                system("clear");
                printf("***INVALID Selection! Make Another Selection***\n\n");
                goto finish_reselect;
        }


	return 0;	
}
