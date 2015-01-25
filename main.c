/*****************************************************
    Student Name:Geofferson Camp    Student Number:  
    Date:January 16th, 2015         Course Name: cis2500
    
    I have exclusive control over this submission via my password.
    By including this statement in this header comment, I certify that:
         1) I have read and understood the University policy on academic integrity;
         2) I have completed the Computing with Integrity Tutorial on Moodle; and
         3) I have achieved at least 80% in the Computing with Integrity Self Test.
   I assert that this work is my own. I have appropriately acknowledged any and all material
   (data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
   Furthermore, I certify that this assignment was prepared by me specifically for this course.
   
   Sources:
   - nCurses functions referenced from www.linux.die.net/man
   - nCurses colour features referenced from www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/color.html
   - drawBoard approach taken from Dr. McCuaig's nCursesExample files.
    
   ****************************************************************************/
   
   #include "a1.h"
   
   /* Initializes nCurses and game set-up. */
   
   int main() {
           
       int bHeight = 8;
       int bWidth = 9;
       int isAiGame;
   
       char player1[11];
       char player2[11];
       /* Name set to player2 when a one player game is selected. This value is referenced during the gamePlayAI function.*/
       char nameAI[11] = {'c','o','m','p','u','t','e','r','A','I'};
   
       initscr();
       wresize(stdscr,98,98);
       start_color();
       
       init_pair(1,COLOR_BLACK,COLOR_BLACK);
       init_pair(2,COLOR_BLACK,COLOR_WHITE);
       init_pair(3,COLOR_BLACK,COLOR_CYAN);
       init_pair(4,COLOR_BLACK,COLOR_MAGENTA);
       init_pair(5,COLOR_RED,COLOR_WHITE);
       init_pair(6,COLOR_BLUE,COLOR_WHITE);
   
       use_default_colors();
   
       printw("Number of players (1 or 2):");
      
       /* Ensure user can only select 1 or 2 players. */ 
       noecho();
       while (isAiGame != '1') {
           if (isAiGame == '2') {
               break;
           }  
           isAiGame = getch();
       }
       echo();
   
       move(0,0);
       clrtoeol();
   
       /* Read in player names. If only one player was selected, set player2 to default AI name */
       printw("Player 1:");
       getnstr(player1,10);
       if (isAiGame == '2') {
           printw("Player 2:");
           do {     
               getnstr(player2,10);
               move(1,9);
               clrtoeol();
           } while (strcmp(player2,nameAI)== 0 );
       } else {
           for (int i = 0; i<11; i++) {
               player2[i] = nameAI[i];
           }
       }
   
       move(0,0);
       clrtoeol();
       move(1,0);
       clrtoeol();
   
       drawBoard(bHeight,bWidth);
   
       refresh();
   
       /* Initiating game play */
       statusHandler(player1,player2,bHeight,bWidth,nameAI,0,0);
       
       return 0;   
   }
   
   /* Draws game board and prints initial control messages.
      IN: Board dimensions.
      OUT: Nothing. */
   
   void drawBoard(int bHeight, int bWidth) {
          
      int i;
      int rows;
      int cols;
      int colourSwitchA;
      int colourSwitchB;
  
      use_default_colors();
  
      attron(COLOR_PAIR(1));    
      for (i=0; i<bWidth; i++) {        
          mvaddch(0, i, '#');    
      } 
      for (i=0; i<bHeight; i++) {
          mvaddch(i,0,'#');
          mvaddch(i,bWidth,'#');
      }
      for (i=0; i<bWidth+1; i++) {
          mvaddch(bHeight,i,'#');
      }
      attroff(COLOR_PAIR(1));   
  
      for (rows=1;rows<bHeight;rows++) {
          
          /* Ensure alternate rows have alternate starting colours. */
          if (rows%2 == 0) {
              colourSwitchA = 1;
              colourSwitchB = 2;
          } else {
              colourSwitchA = 2;
              colourSwitchB = 1;
          }
          
          /* Print board grid. One loop for magenta blocks, one loop for cyan blocks. */
          attron(COLOR_PAIR(3));
          for (cols=colourSwitchA;cols<bWidth;cols=cols+2) {   
              mvaddch(rows,cols,'_');
          }
          attroff(COLOR_PAIR(3));
  
          attron(COLOR_PAIR(4));
          for (cols=colourSwitchB;cols<bWidth;cols=cols+2) {
              mvaddch(rows,cols,'_');  
          }
          attroff(COLOR_PAIR(4));
   
      }
          
      move(bHeight+2,0);
      printw("Press 'x' to choose a spot.");
      move(bHeight+3,0);
      printw("Press 'q' to quit.");
  
  }
  
  /* Decides to end game or initiate next turn.
     IN: player names, board dimensions, player scores.
     OUT: Nothing. */
  
  void statusHandler(char player1[11], char player2[11], int bHeight, int bWidth, char nameAI[11], int player1Score, int player2Score) {
      int gameStatus = 1;
      int turnStatus = 1;
      char againOrQuit;
      
      printScore(player1Score,player2Score);
  
      /* Stay in game play loop until victory conditions are met. Responsible for changing turns and initiating playGame function. */
      while (gameStatus == 1) {
          if (turnStatus == 1) {
              turnStatus = 2;
              move(bHeight+1,0);
              clrtoeol();
              attron(COLOR_PAIR(5));
              printw("It is %s's turn.", player1);
              attroff(COLOR_PAIR(5));
              move(1,1);
              playGame(bHeight,bWidth,&gameStatus,turnStatus);
              
          } else if (turnStatus == 2) {
              turnStatus = 1;
              move(bHeight+1,0);
              clrtoeol();
              attron(COLOR_PAIR(6));
              printw("It is %s's turn.", player2);
              attroff(COLOR_PAIR(6));
              move(1,1);
              if (strcmp(player2,nameAI) == 0) {
                  playGameAI(bHeight,bWidth,&gameStatus,turnStatus);
              } else {  
                  playGame(bHeight,bWidth,&gameStatus,turnStatus);
              }
          }
                  
      }
  
      /* If victory conditions are met, ask user if they want to play again or quit. Resets game board or ends window according to user input. */
      if (gameStatus == 0) {
          move(bHeight+1,0);
          clrtoeol();
          move(bHeight+2,0);
          clrtoeol();
          move(bHeight+3,0);
          clrtoeol();
          move(bHeight+1,0);
          if (turnStatus == 1) {
              player2Score++;
              printw("%s wins! Press 'p' to play again. Press 'q' to quit.", player2);
          } else if (turnStatus == 2) {
              player1Score++;
              printw("%s wins! Press 'p' to play again. Press 'q' to quit.", player1);
          }
  
          printScore(player1Score,player2Score);
          
          while ((againOrQuit=getch()) != 'p') {
              if (againOrQuit == 'q') {
                  break;
              }
          }
          if (againOrQuit == 'p') {
              clear();
              drawBoard(bHeight,bWidth);
              refresh();
              
              statusHandler(player1,player2,bHeight,bWidth,nameAI,player1Score,player2Score);
              
           } else {
              endwin();
          }
      } else if (gameStatus == 2) {
          endwin();
      }
  
  }
  
  /* Reads user control and initiates spot choosing function.
     IN: Board dimensions, game status, and turn status.
     OUT: Nothing. */
  
  void playGame(int bHeight,int bWidth,int *gameStatus, int turnStatus) {
      int posX=1;
      int posY=1;
      char input;
     
     /* Read in user control until spot is chosen or user quits. */ 
     while (1) {
          noecho();
          input = getch();
          
          if (input == 'q') { 
              *gameStatus = 2;
              break;
          }
          else if (input == 'x') {
              if (placeCheck(posY,posX,turnStatus) == 1) {
                  break;
              } else {
                  move (bHeight+1,0);
                  printw("That spot has been obstructed! Try again.");
                  move(posY,posX);
              }
          } else if (input == 'j') {
  
              posX = posX - 1;
              if (posX < 1) {
                  posX=1;
              }
              
              move(posY,posX);   
            
         } else if (input == 'l') {
  
              posX = posX+1;
              if (posX >= bWidth) {
                  posX=bWidth-1;
              }
              
              move(posY,posX);
  
          } else if (input == 'k') {
  
              posY = posY+1;
              if (posY >= bHeight) {
                  posY = bHeight-1;
              }
              
              move(posY,posX);
  
          } else if (input == 'i') {
  
              posY = posY-1;
              if (posY < 1) {
                  posY = 1;
              }
              
               move(posY,posX);
  
          } else {
                          
          }
      }
  
      if (winCheck(bHeight,bWidth) == 1) {
          *gameStatus = 0;
      }
  }
  
  /* If player 2 is AI, chooses spot for player2.
     IN: Board dimensions, turn status, and game status.
     OUT: Nothing. */
  
  void playGameAI(int bHeight, int bWidth, int *gameStatus, int turnStatus) {
      int rows;
      int cols;
      char contentHolder;
      int coords[(bHeight*bWidth)*2+1];
      int arrayMarker = 0;
      int randomNumber;
      int randomY;
      int randomX;
      
      for (rows=1; rows<bHeight; rows++) {
          for (cols=1; cols<bWidth; cols++) {
              move(rows,cols);
              contentHolder = inch();
              if (contentHolder == '_') {
                 coords[arrayMarker] = rows;
                 arrayMarker++;
                  coords[arrayMarker] = cols;
                  arrayMarker++;
              }
          }
      }
     
      /* Return arrayMarker to correct length. */
      arrayMarker = arrayMarker-1;
   
      randomNumber = generateRandom(arrayMarker);
      randomY = coords[randomNumber];
      randomX = coords[randomNumber+1];
      move(randomY,randomX);
    
      placeCheck(randomY,randomX,turnStatus);
     
      if (winCheck(bHeight,bWidth) == 1) {
          *gameStatus = 0;
      } 
  }
  
  /* Generate random number to choose spot for AI.
     IN: Number range.
     OUT: Random number. */
      
  int generateRandom(int arrayMarker) {
      int randomNumber;
      
      /* Use time as seed */
      srand(time(NULL));
  
      /* Ensure randomNumber is between 0 and arrayMarker. */
      randomNumber = rand() % arrayMarker + 1;
      if (randomNumber % 2 == 0 || randomNumber == 0) {
          return randomNumber;
      } else {
          /* Ensure random number points to a row value in the coords array. */
          randomNumber = randomNumber-1;
          return randomNumber;
      }
      return 0;
  }
  
  /* Checks if cursor position is not obstructed and changes game board if not obstructed.
     IN: Cursor position and turn status.
     OUT: Integer indicating if spot is obstructed. */
  
  int placeCheck(int curY, int curX, int turnStatus) {
  
      int rowCounter;
      int colCounter;
      char spotContent;
  
      move(curY,curX);
      spotContent = inch();
      if (spotContent == '*'||spotContent == 'x') {
          return 0;
      } else {
          if (turnStatus == 2) {
              attron(COLOR_PAIR(5));
              printw("*");
              attroff(COLOR_PAIR(5));
          } else {
              attron(COLOR_PAIR(6));
              printw("*");
              attroff(COLOR_PAIR(6));
          } 
          for (rowCounter=curY-1;rowCounter<curY+2;rowCounter++) {
              for (colCounter=curX-1;colCounter<curX+2;colCounter++) {
                  move(rowCounter,colCounter);
                  spotContent = inch();
                  if (spotContent == '_') {
                      attron(COLOR_PAIR(2));              
                      printw("x");
                      attroff(COLOR_PAIR(2));
                  }
              } 
          }
          return 1;
          
      }
  }
  
  /* Check if victory conditions have been met.
     IN: Board dimensions.
     OUT: Integer indicating game status. */
  
  int winCheck(int bHeight, int bWidth) {
      int row, col, winCounter;
      char spotChecker;
      winCounter = 0;
  
      /* Loops through each grid spot. If spot is obstructed or taken, add to win counter. 
      If all spots are added to counter, initiate victory sequence. */ 
      for (row=1; row<bHeight; row++) {
          for (col=1; col<bWidth; col++) {
              move(row,col);
              spotChecker = inch();
              if (spotChecker == 'x' || spotChecker == '*') {
                  winCounter = winCounter + 1;
              }
          }
      }
  
      /* If winCounter is equal to the number grid squares, initiate victory sequence. */
      if (winCounter == (bHeight-1)*(bWidth-1)) {
          return 1;
      } else {
          return 0;
      }
  
  }
  
  /* Refresh the score board.
     IN: Player scores.
     OUT: Nothing. */
  
  void printScore(int player1Score, int player2Score) {
      move(1,15);
      attron(COLOR_PAIR(5));
      printw("%i",player1Score);
      attroff(COLOR_PAIR(5));
      printw("-");
      attron(COLOR_PAIR(6));
      printw("%i",player2Score);
      attroff(COLOR_PAIR(6));
  }
