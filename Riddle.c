#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Number Riddle Game, creates a gamboard with an empty spot and allows the player to 
switch the number arounds to place them in order */

int printBoard(int rows, int cols, int gameBoard[rows * cols]);

int main(){

    puts("*************************");
    puts("******* Welcome to ******");
    puts("*** Number Riddle Game***");
    puts("******* Ver. 2.0 ********");
    puts("****** Programmer *******");
    puts("***** Antonio Roye ******\n");

    //Varibales for number of rows, number of columns, and the end condition
    int rows, cols, end;
    do
    {
        //Get number of rows
        do
        {
           puts("Enter number of rows (3-8): ");
           scanf("%d", &rows);
        } while (rows < 3 || rows > 8);

        //Get number of columns
        do
        {
           puts("Enter number of cols (3-8): ");
           scanf("%d", &cols);
        } while (cols < 3 || cols > 8);

        //Variable for the gameboard
        int gameBoard[rows * cols]; 

        // Loop to fill the gameboard with numbers from 0 - (rows*cols)
        for (int i = 0; i < (rows * cols); i++)
        {
            gameBoard[i] = i;
        }

        //Variable to create temporary holding place for a number
        int temp;

        //Loop to randomly shuffle the numbers in the gameboard
        srand(time(NULL));
        for (int i = 0; i < (rows * cols); i++)
        {
            //Variable to generate the random number to be shuffled
            int j = rand() % (rows * cols);
            temp = gameBoard[i];
            gameBoard[i] = gameBoard[j];
            gameBoard[j] = temp;
        }

        // Prints the gameboard
        printBoard(rows, cols, gameBoard);

        //Varible for the index of the 0 (empty spot)
        int zeroIndex;

        //Loop to find the empty spot in the gameboard
        for(int i = 0; i < rows * cols; i++)
        {
            //If number is equal to 0 assign index to zeroIndex
            if (gameBoard[i] == 0)
            {
                zeroIndex = i;
            }
        }

       /* Variable for the number to move, the right edge of the game board, 
       the left edge of the gameboard, and the number of moves */
       int numberToMove, rightEdge, leftEdge, moves = 0;   
       do
       {
           //Finds the index of the right and left borders of the line which the empty spot is on
           rightEdge = (cols * ceil((float)(zeroIndex + 1) / (float)cols)) - 1;
           leftEdge = (cols * ceil((float)(zeroIndex + 1) / (float)cols)) - cols;
           
           //Get the number to move
           printf("\n(#Move %d), Enter a number to move (0 to exit):", moves);
           scanf("%d", &numberToMove);

           //Check exit contion, else run the switching algorithm
           if (numberToMove == 0)
           {
               puts("\nIf you would like to return to the game press 1, otherwise press 0");
               scanf("%d", &numberToMove);
               continue;
           }else
           { 
               //Switches a number to the right of the empty spot in the array with the empty spot
               //If empty spot is on the right border, it will not allow the movement of an adjacent right array number
               //Changes index, increments move, prints board
               if (gameBoard[zeroIndex + 1] == numberToMove && zeroIndex != rightEdge)
               {
                    gameBoard[zeroIndex + 1] = gameBoard[zeroIndex];
                    gameBoard[zeroIndex] = numberToMove;
                    zeroIndex += 1;
                    moves++;
                    printBoard(rows, cols, gameBoard);
                   
                } 
                //Switches a number to the left of the empty spot in the array with the empty spot
                //If empty spot is on the left border, it will not allow the movement of an adjacent left array number
                //Changes index, increments move, prints board
                else if (gameBoard[zeroIndex-1] == numberToMove && zeroIndex != leftEdge)
                {
                    gameBoard[zeroIndex-1] = gameBoard[zeroIndex];
                    gameBoard[zeroIndex] = numberToMove;
                    zeroIndex -= 1;
                    moves++;
                    printBoard(rows, cols, gameBoard);
                    
                } 
                //Switches a number directly below the empty spot with the empty spot within the bounds of the gameboard
                //Changes index, increments move, prints board
                else if (gameBoard[zeroIndex + cols] == numberToMove && zeroIndex + cols <= rows * cols)
                {
                    gameBoard[zeroIndex + cols] = gameBoard[zeroIndex];
                    gameBoard[zeroIndex] = numberToMove;
                    zeroIndex += cols;
                    moves++;
                    printBoard(rows, cols, gameBoard);
                } 

                //Switches a number directly above the empty spot with the empty spot within the bounds of the gamebaord
                //Changes index, increments move, prints board
                else if (gameBoard[zeroIndex - cols] == numberToMove && zeroIndex - cols >= 0)
                {
                    gameBoard[zeroIndex - cols] = gameBoard[zeroIndex];
                    gameBoard[zeroIndex] = numberToMove;
                    zeroIndex -= cols;
                    moves++;
                    printBoard(rows, cols, gameBoard);
                } 
                
                //If number is larger than the gameboard chosen
                else if (numberToMove > (rows * cols - 1))
                {
                    puts("\nThis number is not on the game board!");
                }
                
                //If number is chosen that is not next to the empty spot
                else
                {
                    puts("\nThis cell can't move!");
                }
               
               // Counter variable
               int counter = 0;

               //Counts the numbers in the array and makes sure that they are in increasing order and next to each other
               for ( int i = 0; i < rows * cols - 1; i++)
               {
                   //If the numbers are in order add 1 to counter
                   if (gameBoard[i] == gameBoard[i + 1] - 1)
                   {
                        counter++;
                    }
                }
               
               // If all the numbers are in order the counter will equal rows * cols - 2 which break the loop and end the game
               if (counter == (rows * cols) - 2)
               {
                   puts("\n\nYou won!");
                   break;
               }
           } 
       } while (numberToMove != 0);

       puts("\nIf you want to play a new game enter 1, if not enter 0:");
       scanf("%d", &end);
       
    } while (end != 0);
    
    puts("\nGoodbye!");

    return 0;
}

//Function that prints the gameboard
int printBoard(int rows, int cols, int gameBoard[rows * cols])
{
    //Loop to print the format of the gameboard
    for (int i = 0; i < rows * cols; i++)
        {
            //Prints row on a new line onces the desired number of colums is reached
            if (i % cols == 0 && i > 0)
            {
                printf(" | ");
                printf("\n");
            }
            
            //If the number is 0 print an empty spot, else print the formatted number
            if (gameBoard[i] == 0)
            {
                printf(" |   ");
            }else
            {
                printf(" | ");
                printf("%2d", gameBoard[i]);
            }
        }
        printf(" | ");

    return 0;
}