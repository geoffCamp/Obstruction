/*****************************************************
   2 Student Name:Geofferson Camp    Student Number:  
   3 Date:January 16th, 2015         Course Name: cis2500
   4 
   5 I have exclusive control over this submission via my password.
   6 By including this statement in this header comment, I certify that:
   7      1) I have read and understood the University policy on academic integrity;
   8      2) I have completed the Computing with Integrity Tutorial on Moodle; and
   9      3) I have achieved at least 80% in the Computing with Integrity Self Test.
  10 I assert that this work is my own. I have appropriately acknowledged any and all material
  11 (data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
  12 Furthermore, I certify that this assignment was prepared by me specifically for this course.
  13 
  14 Sources:
  15 - nCurses functions referenced from www.linux.die.net/man
  16 - nCurses colour features referenced from www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/color.html
  17 - drawBoard approach taken from Dr. McCuaig's nCursesExample files.
  18  
  19 ****************************************************************************/
  20 
  21 #include "a1.h"
  22 
  23 /* Initializes nCurses and game set-up. */
  24 
  25 int main() {
  26         
  27     int bHeight = 8;
  28     int bWidth = 9;
  29     int isAiGame;
  30 
  31     char player1[11];
  32     char player2[11];
  33     /* Name set to player2 when a one player game is selected. This value is referenced during the gamePlayAI function.*/
  34     char nameAI[11] = {'c','o','m','p','u','t','e','r','A','I'};
  35 
  36     initscr();
  37     wresize(stdscr,98,98);
  38     start_color();
  39     
  40     init_pair(1,COLOR_BLACK,COLOR_BLACK);
  41     init_pair(2,COLOR_BLACK,COLOR_WHITE);
  42     init_pair(3,COLOR_BLACK,COLOR_CYAN);
  43     init_pair(4,COLOR_BLACK,COLOR_MAGENTA);
  44     init_pair(5,COLOR_RED,COLOR_WHITE);
  45     init_pair(6,COLOR_BLUE,COLOR_WHITE);
  46 
  47     use_default_colors();
  48 
  49     printw("Number of players (1 or 2):");
  50    
  51     /* Ensure user can only select 1 or 2 players. */ 
  52     noecho();
  53     while (isAiGame != '1') {
  54         if (isAiGame == '2') {
  55             break;
  56         }  
  57         isAiGame = getch();
  58     }
  59     echo();
  60 
  61     move(0,0);
  62     clrtoeol();
  63 
  64     /* Read in player names. If only one player was selected, set player2 to default AI name */
  65     printw("Player 1:");
  66     getnstr(player1,10);
  67     if (isAiGame == '2') {
  68         printw("Player 2:");
  69         do {     
  70             getnstr(player2,10);
  71             move(1,9);
  72             clrtoeol();
  73         } while (strcmp(player2,nameAI)== 0 );
  74     } else {
  75         for (int i = 0; i<11; i++) {
  76             player2[i] = nameAI[i];
  77         }
  78     }
  79 
  80     move(0,0);
  81     clrtoeol();
  82     move(1,0);
  83     clrtoeol();
  84 
  85     drawBoard(bHeight,bWidth);
  86 
  87     refresh();
  88 
  89     /* Initiating game play */
  90     statusHandler(player1,player2,bHeight,bWidth,nameAI,0,0);
  91     
  92     return 0;   
  93 }
  94 
  95 /* Draws game board and prints initial control messages.
  96    IN: Board dimensions.
  97    OUT: Nothing. */
  98 
  99 void drawBoard(int bHeight, int bWidth) {
 100         
 101     int i;
 102     int rows;
 103     int cols;
 104     int colourSwitchA;
 105     int colourSwitchB;
 106 
 107     use_default_colors();
 108 
 109     attron(COLOR_PAIR(1));    
 110     for (i=0; i<bWidth; i++) {        
 111         mvaddch(0, i, '#');    
 112     } 
 113     for (i=0; i<bHeight; i++) {
 114         mvaddch(i,0,'#');
 115         mvaddch(i,bWidth,'#');
 116     }
 117     for (i=0; i<bWidth+1; i++) {
 118         mvaddch(bHeight,i,'#');
 119     }
 120     attroff(COLOR_PAIR(1));   
 121 
 122     for (rows=1;rows<bHeight;rows++) {
 123         
 124         /* Ensure alternate rows have alternate starting colours. */
 125         if (rows%2 == 0) {
 126             colourSwitchA = 1;
 127             colourSwitchB = 2;
 128         } else {
 129             colourSwitchA = 2;
 130             colourSwitchB = 1;
 131         }
 132         
 133         /* Print board grid. One loop for magenta blocks, one loop for cyan blocks. */
 134         attron(COLOR_PAIR(3));
 135         for (cols=colourSwitchA;cols<bWidth;cols=cols+2) {   
 136             mvaddch(rows,cols,'_');
 137         }
 138         attroff(COLOR_PAIR(3));
 139 
 140         attron(COLOR_PAIR(4));
 141         for (cols=colourSwitchB;cols<bWidth;cols=cols+2) {
 142             mvaddch(rows,cols,'_');  
 143         }
 144         attroff(COLOR_PAIR(4));
 145  
 146     }
 147         
 148     move(bHeight+2,0);
 149     printw("Press 'x' to choose a spot.");
 150     move(bHeight+3,0);
 151     printw("Press 'q' to quit.");
 152 
 153 }
 154 
 155 /* Decides to end game or initiate next turn.
 156    IN: player names, board dimensions, player scores.
 157    OUT: Nothing. */
 158 
 159 void statusHandler(char player1[11], char player2[11], int bHeight, int bWidth, char nameAI[11], int player1Score, int player2Score) {
 160     int gameStatus = 1;
 161     int turnStatus = 1;
 162     char againOrQuit;
 163     
 164     printScore(player1Score,player2Score);
 165 
 166     /* Stay in game play loop until victory conditions are met. Responsible for changing turns and initiating playGame function. */
 167     while (gameStatus == 1) {
 168         if (turnStatus == 1) {
 169             turnStatus = 2;
 170             move(bHeight+1,0);
 171             clrtoeol();
 172             attron(COLOR_PAIR(5));
 173             printw("It is %s's turn.", player1);
 174             attroff(COLOR_PAIR(5));
 175             move(1,1);
 176             playGame(bHeight,bWidth,&gameStatus,turnStatus);
 177             
 178         } else if (turnStatus == 2) {
 179             turnStatus = 1;
 180             move(bHeight+1,0);
 181             clrtoeol();
 182             attron(COLOR_PAIR(6));
 183             printw("It is %s's turn.", player2);
 184             attroff(COLOR_PAIR(6));
 185             move(1,1);
 186             if (strcmp(player2,nameAI) == 0) {
 187                 playGameAI(bHeight,bWidth,&gameStatus,turnStatus);
 188             } else {  
 189                 playGame(bHeight,bWidth,&gameStatus,turnStatus);
 190             }
 191         }
 192                 
 193     }
 194 
 195     /* If victory conditions are met, ask user if they want to play again or quit. Resets game board or ends window according to user input. */
 196     if (gameStatus == 0) {
 197         move(bHeight+1,0);
 198         clrtoeol();
 199         move(bHeight+2,0);
 200         clrtoeol();
 201         move(bHeight+3,0);
 202         clrtoeol();
 203         move(bHeight+1,0);
 204         if (turnStatus == 1) {
 205             player2Score++;
 206             printw("%s wins! Press 'p' to play again. Press 'q' to quit.", player2);
 207         } else if (turnStatus == 2) {
 208             player1Score++;
 209             printw("%s wins! Press 'p' to play again. Press 'q' to quit.", player1);
 210         }
 211 
 212         printScore(player1Score,player2Score);
 213         
 214         while ((againOrQuit=getch()) != 'p') {
 215             if (againOrQuit == 'q') {
 216                 break;
 217             }
 218         }
 219         if (againOrQuit == 'p') {
 220             clear();
 221             drawBoard(bHeight,bWidth);
 222             refresh();
 223             
 224             statusHandler(player1,player2,bHeight,bWidth,nameAI,player1Score,player2Score);
 225             
 226          } else {
 227             endwin();
 228         }
 229     } else if (gameStatus == 2) {
 230         endwin();
 231     }
 232 
 233 }
 234 
 235 /* Reads user control and initiates spot choosing function.
 236    IN: Board dimensions, game status, and turn status.
 237    OUT: Nothing. */
 238 
 239 void playGame(int bHeight,int bWidth,int *gameStatus, int turnStatus) {
 240     int posX=1;
 241     int posY=1;
 242     char input;
 243    
 244    /* Read in user control until spot is chosen or user quits. */ 
 245    while (1) {
 246         noecho();
 247         input = getch();
 248         
 249         if (input == 'q') { 
 250             *gameStatus = 2;
 251             break;
 252         }
 253         else if (input == 'x') {
 254             if (placeCheck(posY,posX,turnStatus) == 1) {
 255                 break;
 256             } else {
 257                 move (bHeight+1,0);
 258                 printw("That spot has been obstructed! Try again.");
 259                 move(posY,posX);
 260             }
 261         } else if (input == 'j') {
 262 
 263             posX = posX - 1;
 264             if (posX < 1) {
 265                 posX=1;
 266             }
 267             
 268             move(posY,posX);   
 269           
 270         } else if (input == 'l') {
 271 
 272             posX = posX+1;
 273             if (posX >= bWidth) {
 274                 posX=bWidth-1;
 275             }
 276             
 277             move(posY,posX);
 278 
 279         } else if (input == 'k') {
 280 
 281             posY = posY+1;
 282             if (posY >= bHeight) {
 283                 posY = bHeight-1;
 284             }
 285             
 286             move(posY,posX);
 287 
 288         } else if (input == 'i') {
 289 
 290             posY = posY-1;
 291             if (posY < 1) {
 292                 posY = 1;
 293             }
 294             
 295              move(posY,posX);
 296 
 297         } else {
 298                         
 299         }
 300     }
 301 
 302     if (winCheck(bHeight,bWidth) == 1) {
 303         *gameStatus = 0;
 304     }
 305 }
 306 
 307 /* If player 2 is AI, chooses spot for player2.
 308    IN: Board dimensions, turn status, and game status.
 309    OUT: Nothing. */
 310 
 311 void playGameAI(int bHeight, int bWidth, int *gameStatus, int turnStatus) {
 312     int rows;
 313     int cols;
 314     char contentHolder;
 315     int coords[(bHeight*bWidth)*2+1];
 316     int arrayMarker = 0;
 317     int randomNumber;
 318     int randomY;
 319     int randomX;
 320     
 321     for (rows=1; rows<bHeight; rows++) {
 322         for (cols=1; cols<bWidth; cols++) {
 323             move(rows,cols);
 324             contentHolder = inch();
 325             if (contentHolder == '_') {
 326                 coords[arrayMarker] = rows;
 327                 arrayMarker++;
 328                 coords[arrayMarker] = cols;
 329                 arrayMarker++;
 330             }
 331         }
 332     }
 333    
 334     /* Return arrayMarker to correct length. */
 335     arrayMarker = arrayMarker-1;
 336  
 337     randomNumber = generateRandom(arrayMarker);
 338     randomY = coords[randomNumber];
 339     randomX = coords[randomNumber+1];
 340     move(randomY,randomX);
 341   
 342     placeCheck(randomY,randomX,turnStatus);
 343    
 344     if (winCheck(bHeight,bWidth) == 1) {
 345         *gameStatus = 0;
 346     } 
 347 }
 348 
 349 /* Generate random number to choose spot for AI.
 350    IN: Number range.
 351    OUT: Random number. */
 352     
 353 int generateRandom(int arrayMarker) {
 354     int randomNumber;
 355     
 356     /* Use time as seed */
 357     srand(time(NULL));
 358 
 359     /* Ensure randomNumber is between 0 and arrayMarker. */
 360     randomNumber = rand() % arrayMarker + 1;
 361     if (randomNumber % 2 == 0 || randomNumber == 0) {
 362         return randomNumber;
 363     } else {
 364         /* Ensure random number points to a row value in the coords array. */
 365         randomNumber = randomNumber-1;
 366         return randomNumber;
 367     }
 368     return 0;
 369 }
 370 
 371 /* Checks if cursor position is not obstructed and changes game board if not obstructed.
 372    IN: Cursor position and turn status.
 373    OUT: Integer indicating if spot is obstructed. */
 374 
 375 int placeCheck(int curY, int curX, int turnStatus) {
 376 
 377     int rowCounter;
 378     int colCounter;
 379     char spotContent;
 380 
 381     move(curY,curX);
 382     spotContent = inch();
 383     if (spotContent == '*'||spotContent == 'x') {
 384         return 0;
 385     } else {
 386         if (turnStatus == 2) {
 387             attron(COLOR_PAIR(5));
 388             printw("*");
 389             attroff(COLOR_PAIR(5));
 390         } else {
 391             attron(COLOR_PAIR(6));
 392             printw("*");
 393             attroff(COLOR_PAIR(6));
 394         } 
 395         for (rowCounter=curY-1;rowCounter<curY+2;rowCounter++) {
 396             for (colCounter=curX-1;colCounter<curX+2;colCounter++) {
 397                 move(rowCounter,colCounter);
 398                 spotContent = inch();
 399                 if (spotContent == '_') {
 400                     attron(COLOR_PAIR(2));              
 401                     printw("x");
 402                     attroff(COLOR_PAIR(2));
 403                 }
 404             } 
 405         }
 406         return 1;
 407         
 408     }
 409 }
 410 
 411 /* Check if victory conditions have been met.
 412    IN: Board dimensions.
 413    OUT: Integer indicating game status. */
 414 
 415 int winCheck(int bHeight, int bWidth) {
 416     int row, col, winCounter;
 417     char spotChecker;
 418     winCounter = 0;
 419 
 420     /* Loops through each grid spot. If spot is obstructed or taken, add to win counter. 
 421     If all spots are added to counter, initiate victory sequence. */ 
 422     for (row=1; row<bHeight; row++) {
 423         for (col=1; col<bWidth; col++) {
 424             move(row,col);
 425             spotChecker = inch();
 426             if (spotChecker == 'x' || spotChecker == '*') {
 427                 winCounter = winCounter + 1;
 428             }
 429         }
 430     }
 431 
 432     /* If winCounter is equal to the number grid squares, initiate victory sequence. */
 433     if (winCounter == (bHeight-1)*(bWidth-1)) {
 434         return 1;
 435     } else {
 436         return 0;
 437     }
 438 
 439 }
 440 
 441 /* Refresh the score board.
 442    IN: Player scores.
 443    OUT: Nothing. */
 444 
 445 void printScore(int player1Score, int player2Score) {
 446     move(1,15);
 447     attron(COLOR_PAIR(5));
 448     printw("%i",player1Score);
 449     attroff(COLOR_PAIR(5));
 450     printw("-");
 451     attron(COLOR_PAIR(6));
 452     printw("%i",player2Score);
 453     attroff(COLOR_PAIR(6));
 454 }
