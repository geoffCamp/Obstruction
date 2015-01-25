#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Draws game board and prints intial control messages. */
void drawBoard(int bHeight, int bWidth);

/* Decides to end the game or initiate the next turn. */
void statusHandler(char player1[11], char player2[11], int bHeight, int bWidth, char nameAI[11], int player1Score, int player2Score);
 
 /* Handles user game play input and intiates spot placing function and win check function. */
 void playGame(int bHeight, int bWidth, int *gameStatus, int turnStatus);
  
 /* If player 2 is AI, playGameAI is called instead of playGame to choose a spot. */
 void playGameAI(int bHeight, int bWidth, int *gameStatus, int turnStatus);
  
 /* Generates random number to be used in playGameAI function. */
 int generateRandom (int arrayMarker);
 
 /*Checks if spot is not obstructed and prints obstruction symbol. */
 int placeCheck(int curY, int curX, int turnStatus);
  
 /* Checks if winning conditions have been met. */
 int winCheck(int bHeight, int bWidth);
  
 /* Refreshes score board. */
 void printScore(int player1Score,int player2Score);
