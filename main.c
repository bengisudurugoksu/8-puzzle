#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Defining PuzzleBoard struct with the numbers 2D array and prev_number integer to use in the auto_finish function.
typedef struct {
    int numbers[3][3];
    int prev_number;
} PuzzleBoard;
//initializeBoard function initilializes a random puzzle board using srand.
void initializeBoard(PuzzleBoard *board) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};  
    int size = sizeof(numbers) / sizeof(numbers[0]);

    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    int index = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board->numbers[i][j] = numbers[index++];
        }
    }
}
//print_bestscore function prints the best_score value in the best_score.txt file.
void print_bestscore(int best_score){
FILE *fp = fopen("best_score.txt", "w");
fprintf(fp, "%d", best_score);
fclose(fp);
}
//read_bestscore function reads the score value from the best_score.txt file and returns it.
int read_bestscore(){
int score;
FILE *fp = fopen("best_score.txt", "r");
fscanf(fp, "%d" , &score);
fclose(fp);
return score;
}
//printBoard function takes the board struct as argument and prints the board.numbers array. 
void printBoard(PuzzleBoard board) {
    printf("\nPuzzle Board:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
        	if(board.numbers[i][j]==0){
        	printf("_ ");
        	}
            else{	
            printf("%d ", board.numbers[i][j]);
            }
        }
        printf("\n");
    }
}
//board_file function takes the board struct and move integer as arguments and prints every move to the board.txt file. 
void board_file(PuzzleBoard board) {
FILE *fp = fopen("board.txt", "a");
if (fp == NULL){
	printf("Error! Could not open file\n");
	exit(-1);
	}
	fprintf(fp, "\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
		if(board.numbers[i][j]==0){
        	fprintf(fp, "_ ");
        	}
            else{	
            fprintf(fp, "%d ", board.numbers[i][j]);
            }
        }
        fprintf(fp,"\n");
    }
fclose(fp);
}
//user_plays function is for the first choice in the menu.
void user_plays(PuzzleBoard board){
int move,finish=0,count=0,score,i,j,best_score=0;
char direction;
printBoard(board);
board_file(board);
print_bestscore(best_score);
//While the finish integer equals zero the game keeps going.
while(finish==0){
best_score=read_bestscore();
//Taking the integer and direction from the user.
printf("\nEnter your move (number-direction, e.g., 2-R): ");
scanf("%d-%c", &move, &direction);
//If the user enters a invalid number the program asks for a number again.
if(move<1 || move>8){
printf("\nChoose a valid number(1-8): ");
scanf("%d", &move);
}
//Finding the values of the 2D array where move==board.numbers to use in the illegal moves.
for(int x=0;x<3;x++){
	for(int y=0;y<3;y++){
	if(board.numbers[x][y]==move){
	i=x;
	j=y;
	}
	}
}

//Using switch-case with directions.	
switch(direction){
case 'R':
if(j+1>2){
//If the user enters R and they are about the hit a wall,the program warns the user that this move is an illegal move and asks for a move again.
printf("\n%d-%c is an illegal move!!! Make a legal move!!!\n", move, direction);
//Everytime the while loop is executed count value increases by one.Since this condition is for the illegal move, we should reduce the count value by 1 because an illegal movement should not be considered a move and it should not be added to the move counter.
count--;
//We print the board even if the move is an illegal move to remind the user the last state of the board.
printBoard(board);
continue;
}
else{
//If the move is not an illegal move we execute the relocation of the two swapping numbers and print the board.Additionaly we print the legal move to the board.txt file using the board_file function.
board.numbers[i][j] = board.numbers[i][j+1];
board.numbers[i][j+1] = move;
printBoard(board);
board_file(board);
}
break;

case 'L':
if(j-1<0){
printf("\n%d-%c is an illegal move!!! Make a legal move!!!\n", move, direction);
count--;
printBoard(board);
continue;
}
else{
board.numbers[i][j] = board.numbers[i][j-1];
board.numbers[i][j-1] = move;
printBoard(board);
board_file(board);
}
break;

case 'U':
if(i-1<0){
printf("\n%d-%c is an illegal move!!! Make a legal move!!!\n", move, direction);
count--;
printBoard(board);
continue;
}
else{
board.numbers[i][j] = board.numbers[i-1][j];
board.numbers[i-1][j] = move;
printBoard(board);
board_file(board);
}
break;

case 'D':
if(i+1>2){
printf("\n%d-%c is an illegal move!!! Make a legal move!!!\n", move, direction);
count--;
printBoard(board);
continue;
}
else{
board.numbers[i][j] = board.numbers[i+1][j];
board.numbers[i+1][j] = move;
printBoard(board);
board_file(board);
}
break;
//If the user did not enter a valid direction the program warns the user and asks the user for a move once again.Like we did in the illegal move state we reduce the count value by 1 because there is no legal movement in this condition.
default:
printf("\nPlease enter a valid direction(U-D-L-R)!\n ");
count--;
break;

}
count++;
//This if statement compares our last board with the wanted result which is {{1,2,3}, {4,5,6}, {7,8,_}} and if results are the same we calculate the score using the count value.
if(board.numbers[0][0]==1 && board.numbers[0][1]==2 && board.numbers[0][2]==3 && board.numbers[1][0]==4 && board.numbers[1][1]==5 && board.numbers[1][2]==6 && board.numbers[2][0]==7 && board.numbers[2][1]==8 && board.numbers[2][2]==0){ 
score = 1000-(10*count);
//To find the best_score we compare the score integer and the best_score integer. If the score integer is greater best_score becomes the score integer.
if(best_score<score){
print_bestscore(score);
best_score=score;
}
//We congratulate the user and set the finish value to 1 to end the while loop.
printf("\nCongratulations! You finished the game.\n\nTotal number of moves: %d\nYour score: %d\n", count, score);
printf("\n");
finish=1;
}
}
}
//Inversioncount function finds the inversion count and returns the value to use in the isSolvable function.
int Inversioncount(PuzzleBoard board)
{
    int inv = 0;
    int i, j;
    int size = 3; // Size of a 3x3 puzzle
    int number;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            number = board.numbers[i][j];
            if (number == 0) // Skip the blank tile
                continue;
            
            for (int k = i; k < size; k++)
            {
                for (int l = (k == i) ? j + 1 : 0; l < size; l++)
                {
                    int compare = board.numbers[k][l];
                    if (compare != 0 && number > compare)
                        inv++;
                }
            }
        }
    }
    return inv;
}
//isSolvable function uses the Inversioncount value recursively and using the returned value and the needed calculations and returns 1 if the number of inversions is even, returns 0 if the number of inversions are odd. If the number of inversions are odd, the puzzle is unsolvable.
int isSolvable(PuzzleBoard board)
{
    int inversions = Inversioncount(board);
    int size = 3; // Size of a 3x3 puzzle
    int blankRow = 0;

    // Find the row containing the blank tile
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.numbers[i][j] == 0)
            {
                blankRow = size - i;
                break;
            }
        }
    }

    // For an odd-sized puzzle, the number of inversions should be even
    if (size % 2 != 0 && inversions % 2 == 0)
        return 1;
    // For an even-sized puzzle, the number of inversions + row of blank tile should be odd
    else if (size % 2 == 0 && ((inversions + blankRow) % 2) != 0)
        return 1;
    else
        return 0;
}
//The auto_finish fuunction is for the second choice in the menu.
void auto_finish(PuzzleBoard board){
int move,finish=0,count=0,score,i,j,drct,prev_number,auto_f;
char direction;
printBoard(board);
board_file(board);   //Printing the initial board to the board.txt file.

while(finish==0){
count++;
move = rand() % (8 + 1);
if(move==board.prev_number){   //The computer chooses a random number between 1-8 for the move value.If the move value equals to the prev_number value the program should choose once again to avoid making the same move again and again.
move = rand() % (8 + 1);
}
drct = rand() % 4;

if(drct==0){   //To use the switch-case statements clearly and understandbly, the computer chooses a random number between 0-3 and the program uses these values to assign the direction characters.
direction='L';
}
else if(drct==1){
direction='U';
}
else if(drct==2){
direction='D';
}
else if(drct==3){
direction='R';
}
for(int x=0;x<3;x++){  //Finding the values of the 2D array where move==board.numbers to use in the illegal moves.
	for(int y=0;y<3;y++){
	if(board.numbers[x][y]==move){
	i=x;
	j=y;
	}
	}
}
	
switch(direction){
case 'R':   //If the computer chooses R and the computer is about the hit a wall,the program indicates that this move is an illegal move and continues.
if(j+1>2){
count--;  //Everytime the while loop is executed count value increases by one.Since this condition is for the illegal move, we should reduce the count value by 1 because an illegal movement should not be considered a move and it should not be added to the move counter.
printf("\nIllegal Move: %d %c\n", move, direction);
printBoard(board);
}
else{
board.numbers[i][j] = board.numbers[i][j+1];
board.numbers[i][j+1] = move;
printf("\nComputer Move: %d-R\n", move);
printBoard(board);
board_file(board);
}
break;

case 'L':
if(j-1<0){
count--;
printf("\nIllegal Move: %d %c\n", move, direction);
printBoard(board);
}
else{
board.numbers[i][j] = board.numbers[i][j-1];
board.numbers[i][j-1] = move;
printf("\nComputer Move: %d-L\n", move);
printBoard(board);
board_file(board);
}
break;

case 'U':
if(i-1<0){
count--;
printf("\nIllegal Move: %d %c\n", move, direction);
printBoard(board);
}
else{
board.numbers[i][j] = board.numbers[i-1][j];
board.numbers[i-1][j] = move;
printf("\nComputer Move: %d-U\n", move);
printBoard(board);
board_file(board);
}
break;

case 'D':
if(i+1>2){
count--;
printf("\nIllegal Move: %d %c\n", move, direction);
printBoard(board);
}
else{
board.numbers[i][j] = board.numbers[i+1][j];
board.numbers[i+1][j] = move;
printf("\nComputer Move: %d-D\n", move);
printBoard(board);
board_file(board);
}
break;
}

if(board.numbers[0][0]==1 && board.numbers[0][1]==2 && board.numbers[0][2]==3 && board.numbers[1][0]==4 && board.numbers[1][1]==5 && board.numbers[1][2]==6 && board.numbers[2][0]==7 && board.numbers[2][1]==8 && board.numbers[2][2]==0){ 
score = 1000-(10*count);
printf("\nComputer finished the game\n\nTotal number of computer moves: %d", count);
printf("\n");
finish=1;
}
//Assigning the move value to the board.prev_number integer to use in the if statement above.
board.prev_number=move;
}
}
int main(){
PuzzleBoard board;
remove("board.txt");

int choice,exit=0,inversionc,best_score;
FILE *fp = fopen("board.txt", "a");
while(exit==0){
printf("\nWelcome to the 8-Puzzle Game!\nPlease select an option:\n1. Play game as a user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n> ");
scanf("%d", &choice);
switch(choice){

case 1:
initializeBoard(&board);
user_plays(board);
fprintf(fp, "\n----------------------------------------------\n");
break;

case 2:
initializeBoard(&board);
inversionc = isSolvable(board);
if(inversionc==0){   //If inversionc==0 the puzzle is unsolvable as I stated in the isSolvable function part. So when this condition happens the program states that the puzzle is unsolvable for the computer and makes the user choose from the menu once again.
printf("\nPuzzle is unsolvable for the computer, please choose from the menu again.\n");
}
else{
auto_finish(board);
fprintf(fp, "\n----------------------------------------------\n");
}
break;

case 3:
best_score=read_bestscore();   //Using the read_bestscore function the program reads the best score and assigns this value to the best_score value, then prints the value.
printf("\nThe best score is %d...\n", best_score);
break;

case 4:   //If the fourth choice is choosen the program equalizes the exit value to 1 and enters the loop, enters the program aswell with a termination message.
printf("\nProgram terminated...\n");
exit=1;
break;

default:
printf("\nPlease make a valid menu choice(1-2-3-4)!\n");
break;
}

}
fclose(fp);
return 0;
}


