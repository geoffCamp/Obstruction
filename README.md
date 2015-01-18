 *******************************************************
Geofferson Camp  
CIS*2500                   Assignement 1 - Obstruction
Januray 16th, 2015
*******************************************************
 

************
Compilation
************

gcc -Wall -std=c99 -pedantic -Iinclude src/a1.c -o bin/a1 -lncurses
 
 ***********************
Running the program(s)
***********************
 
- User selects '1' or '2' indicating number of players.
 - User enters name(s) of players.
 - User chooses spot by pressing 'x' key.
 - At the end of a game, user can press 'p' key to play again or 'q' to quit.
 - User can quit at any time by pressing the 'q' key.
 
 
 *****************
 Known Limitations
 *****************
 
 - Player names can be a maximum of 10 characters.
 - nCurses window is set to 98x98.
 - Player 2 can't select "computerAI" as a name.
 
 *****************
 Testing Done
 
 - Player unable to leave game board.
 - Name input for size and all characters.
 - AI function
 - Only able to select unobstructed places.
 - Selecting non obstructed spot changes board accordingly.
 - Ensuring system restricts user input for number of players and player 2 name.
 
 *****************
 Sources
 *****************
 
 - nCurses functions referenced from linux.die.net/man
 - nCurses colour features referenced from tldp.org/HOWTO/NCURSES-Programming-HOWTO/color.html
 - drawBoard approach taken from Dr. McCuaig's nCursesExample files.
