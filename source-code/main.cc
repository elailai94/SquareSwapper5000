//=============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Program to enable a player to play the SquareSwapper5000 game
// @version: 1.4 29/11/2014
//=============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <vector>

#include "command.h"
#include "swap.h"
#include "hint.h"
#include "scramble.h"
#include "levelup.h"
#include "leveldown.h"
#include "restart.h"
#include "help.h"
#include "board.h"

using namespace std;                                     // Provides direct access to std

// Prints msg to screen in curses mode.
void printToScreen(string msg) {
   int row = 0;
   int col = 0;

   initscr();                                            // Starts curses mode
   getmaxyx(stdscr, row, col);                           // Gets dimensions of screen
   curs_set(false);                                      // Disables cursor from displaying 
   start_color();                                        // Starts colour mode

   init_pair(1, COLOR_GREEN, COLOR_BLACK);               // First pair of foreground and background colour
   attron(COLOR_PAIR(1));  

   // Print borders for four corners of screen
   mvprintw(0, 0, "%s", "+");
   mvprintw(row - 1, 0, "%s", "+");
   mvprintw(0, col - 1, "%s", "+");
   mvprintw(row - 1, col - 1, "%s", "+");

   mvprintw(1, 1, "%s", "+");
   mvprintw(row - 2, 1, "%s", "+");
   mvprintw(1, col - 2, "%s", "+");
   mvprintw(row - 2, col - 2, "%s", "+");
  
   // Print borders for left and right sides of screen
   for (int i = 1; i < (row - 1); i++) {
      mvprintw(i, 0, "%s", "|");
      mvprintw(i, col - 1, "%s", "|");
   } // for
   
   for (int i = 2; i < (row - 2); i++) {
      mvprintw(i, 1, "%s", "|");
      mvprintw(i, col - 2, "%s", "|");
   } // for

   // Print borders for top and bottom sides of screen
   for (int j = 1; j < (col - 1); j++) {
      mvprintw(0, j, "%s", "-");
      mvprintw(row - 1, j, "%s", "-");
   } // for

   for (int j = 2; j < (col - 2); j++) {
      mvprintw(1, j, "%s", "-");
      mvprintw(row - 2, j, "%s", "-");
   } // for
   
   attroff(COLOR_PAIR(1));

   init_pair(2, COLOR_MAGENTA, COLOR_BLACK);              // Second pair of foreground and background colour
   
   attron(COLOR_PAIR(2));
   mvprintw(row/2,(col-msg.length())/2,"%s",msg.c_str()); // Prints welcome message to center of screen
   attroff(COLOR_PAIR(2));
   refresh();                                             // Refreshes the screen
   sleep(4);                                              // Delays for 4 seconds before next event
   erase();                                               // Clears the screen
   endwin();                                              // End curses mode
} // welcomeScreen

int main(int argc, char *argv[]) {
   bool graphics = true;                                 // Indicates whether graphical version of the game is run
   bool seedSet = false;                                 // Indicates whether random number generator seed is set
   string filename = "";                                 // Stores the filename read in from command line
   int levelInt = 0;                                     // Stores the read in level
   bool bonusUnlocked = false;                           // Indicates whether bonus features in the game is unlock
   string s = "";                                        // Stores the read in command

   if (argc > 1) {                                       // Optional arguments are specified at the command line?
      // Processes all optional argument specified at the command line
      for (int i = 1; i < argc; ++i) {
         string optionalArgument = argv[i];              // Stores the optional argument read in from command line
         
         if (optionalArgument == "-text") {              // Run text-only version of game?
            graphics = false;
         } else if (optionalArgument == "-seed") {       // Set random number generator seed?
            
            if (i + 1 < argc) {                          // More optional arguments available?                 
               string seedStr = argv[i + 1];             // Stores the random number generator seed read in from command line
            
               if (seedStr == "time") {
                  srand(time(0));                        // Initializes random seed with time
                  seedSet = true;
               } else {
                  int seedInt = 0;                       // Stores the read in random number generator seed
                  istringstream iss(seedStr);            // Connects stream and seedStr
                  
                  if (iss >> seedInt) {                  // Successful conversion of seedStr to integer
                     srand(seedInt);                     // Initializes random seed with seedInt
                     seedSet = true;
                  } // if
               } // if
            } // if
         
         } else if (optionalArgument == "-scriptfile") { // Initialize board configuration from a file?
            
            if (i + 1 < argc) {                          // More optional arguments available?
               string file = argv[i + 1];                // Stores the filename read in from command line
               ifstream ifs(file.c_str());               // Connects stream and filename
               
               if (ifs.good()) {                         // File exists in directory?
                  filename = file;
                  i += 1;
               } // if
            } // if 
         
         } else if (optionalArgument == "-startlevel") { // Start the game on a different level?
            
            if (i + 1 < argc) {                          // More optional arguments available?
               string levelStr = argv[i + 1];            // Stores the level read in from command line
               istringstream iss(levelStr);              // Connects stream and levelStr
            
               if (iss >> levelInt) {                    // Successful conversion from levelInt to integer
                  i += 1;
               }
            } // if
         
         } else if (optionalArgument == "-unlock") {     // Unlock all bonus features?
            bonusUnlocked = true;
         } // if
      } // for
   } // if

   if (seedSet == false) {                               // Random number generator seed is set?                                
      srand(579756);                                     // Initializes random seed with constant
   } // if

   if (bonusUnlocked) {                                  // Bonus features unlocked?
      printToScreen("Welcome to SquareSwapper5000!");
   } // if

   Board *newBoard = new Board(graphics, filename, levelInt, bonusUnlocked);
   
   // Vector to hold command names for renaming
   vector<string *> commands;

   string swapVar = "swap";
   commands.push_back(&swapVar);
   string hintVar = "hint";
   commands.push_back(&hintVar);
   string scrambleVar = "scramble";
   commands.push_back(&scrambleVar);
   string levelUpVar = "levelup";
   commands.push_back(&levelUpVar);
   string levelDownVar = "leveldown";
   commands.push_back(&levelDownVar);
   string restartVar = "restart";
   commands.push_back(&restartVar);
   string helpVar = "help";
   commands.push_back(&helpVar);


   // Reads in game commands until an EOF signal is encountered and performs the commands
   while (cin >> s) {
      
      if (s == swapVar) {                            
      	 int x = 0;                                      // Stores the read in row-coordinate of square to be swap
      	 int y = 0;                                      // Stores the read in col-coordinate of square to be swap
      	 int z = 0;                                      // Stores the read in direction for swap

      	 cin >> x >> y >> z;
      	 Swap swapCommand(x, y, z, newBoard);
      	 swapCommand.run();
         if (newBoard->isWon()) {                        // Game won?
            if (bonusUnlocked) {                         // Bonus features unlocked?
               printToScreen("You Win!");
            } else {
               cout << "You Win!" << endl;
            } // if
            break;
         } // if
      } else if (s == hintVar) {                         // Generate a hint?
      	Hint hintCommand(newBoard, false);
      	hintCommand.run();
         cout << *newBoard << endl;
      } else if (s == scrambleVar) {                     // Reshuffle squares on board?
      	Scramble scrambleCommand(newBoard);
      	scrambleCommand.run();
      } else if (s == levelUpVar) {                      // Increase level difficulty?
      	LevelUp levelUpCommand(newBoard);
      	levelUpCommand.run();
      } else if (s == levelDownVar) {                    // Decrease level difficulty?
      	LevelDown levelDownCommand(newBoard);
      	levelDownCommand.run();
      } else if (s == restartVar) {                      // Restart level?
      	Restart restartCommand(newBoard);
      	restartCommand.run();
      } else if (s == helpVar) {                         // Need help?
         Help helpCommand(newBoard);
         helpCommand.run();
      } else if (s == "rename") {
         string oldName = "";                            // Stores the read in old command name                  
         string newName = "";                            // Stores the read in new command name

         cin >> oldName >> newName;
         // Finds and replaces old command name with new command name in commands vector
         for (std::vector<string *>::iterator i = commands.begin(); i != commands.end(); ++i) {
            if (**i == oldName) {                        // Old command name found?
               **i = newName;
               cout << "The command" << ' ' << oldName << ' ' << "has been renamed to" << ' ' << newName << '.' << endl;
               cout << "Please note that this change will not be reflected when you type 'help'." << endl;
               break;
            } // if
         } // for
      } else {
         cerr << "You have entered an invalid command. Please try again with a valid command." << endl;
         cerr << "Type 'help' to see the available commands." << endl;
      } //if

   } // while

   delete newBoard;

   if (bonusUnlocked) {                                   // Bonus features unlocked?
   	  printToScreen("Thank you for playing!");
   } // if
}
