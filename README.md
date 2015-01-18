   1 *******************************************************
   2 Geofferson Camp  
   3 CIS*2500                   Assignement 1 - Obstruction
   4 Januray 16th, 2015
   5 *******************************************************
   6 
   7 
   8 ************
   9 Compilation
  10 ************
  11 
  12 gcc -Wall -std=c99 -pedantic -Iinclude src/a1.c -o bin/a1 -lncurses
  13 
  14 ***********************
  15 Running the program(s)
  16 ***********************
  17 
  18 - User selects '1' or '2' indicating number of players.
  19 - User enters name(s) of players.
  20 - User chooses spot by pressing 'x' key.
  21 - At the end of a game, user can press 'p' key to play again or 'q' to quit.
  22 - User can quit at any time by pressing the 'q' key.
  23 
  24 
  25 *****************
  26 Known Limitations
  27 *****************
  28 
  29 - Player names can be a maximum of 10 characters.
  30 - nCurses window is set to 98x98.
  31 - Player 2 can't select "computerAI" as a name.
  32 
  33 *****************
  34 Testing Done
  35 *****************
  36 
  37 - Player unable to leave game board.
  38 - Name input for size and all characters.
  39 - AI function
  40 - Only able to select unobstructed places.
  41 - Selecting non obstructed spot changes board accordingly.
  42 - Ensuring system restricts user input for number of players and player 2 name.
  43 
  44 *****************
  45 Sources
  46 *****************
  47 
  48 - nCurses functions referenced from linux.die.net/man
  49 - nCurses colour features referenced from tldp.org/HOWTO/NCURSES-Programming-HOWTO/color.html
  50 - drawBoard approach taken from Dr. McCuaig's nCursesExample files.
