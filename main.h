#include <ncurses.h>
   2 #include <stdlib.h>
   3 #include <string.h>
   4 #include <time.h>
   5 
   6 /* Draws game board and prints intial control messages. */
   7 void drawBoard(int bHeight, int bWidth);
   8 
   9 /* Decides to end the game or initiate the next turn. */
  10 void statusHandler(char player1[11], char player2[11], int bHeight, int bWidth, char nameAI[11], int player1Score, int player2Score);
  11 
  12 /* Handles user game play input and intiates spot placing function and win check function. */
  13 void playGame(int bHeight, int bWidth, int *gameStatus, int turnStatus);
  14 
  15 /* If player 2 is AI, playGameAI is called instead of playGame to choose a spot. */
  16 void playGameAI(int bHeight, int bWidth, int *gameStatus, int turnStatus);
  17 
  18 /* Generates random number to be used in playGameAI function. */
  19 int generateRandom (int arrayMarker);
  20 
  21 /*Checks if spot is not obstructed and prints obstruction symbol. */
  22 int placeCheck(int curY, int curX, int turnStatus);
  23 
  24 /* Checks if winning conditions have been met. */
  25 int winCheck(int bHeight, int bWidth);
  26 
  27 /* Refreshes score board. */
  28 void printScore(int player1Score,int player2Score);
