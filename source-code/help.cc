//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Help objects
// @version: 1.0 21/11/2014
//==============================================================================

// Help module (help.cc)

#include <iostream>
#include "help.h"
#include "board.h"
#include "scoreboard.h"

using namespace std; // Provides direct access to std

// See interface(header file).
Help::Help(Board *board)
   : Command(board) {} // Constructor

// See interface(header file).
Help::~Help() {} // Destructor

// See interface(header file).
void Help::run() {
   const int currentLevel = getBoard()->getScoreboard()->getLevel(); // Stores the current level

   cout << "--------------------Game Commands---------------------" << endl;
   cout << "swap x y z" << endl;
   cout << "  where x is a row number between 0 and " << (getBoard()->getHeight() - 1) << ',' << endl;
   cout << "  where y is a column number between 0 and " << (getBoard()->getWidth() - 1) << ',' << endl;
   cout << "  where z is a swap direction number between 0 and 3 such that:" << endl;
   cout << "    0: Up" << endl;
   cout << "    1: Down" << endl;
   cout << "    2: Left" << endl;
   cout << "    3: Right" << endl; 
   cout << "hint" << endl;
   cout << "scramble" << endl;
   cout << "levelup" << endl;
   cout << "leveldown" << endl;
   cout << "restart" << endl;
   cout << "help" << endl;
   cout << "rename" << endl;
   cout << "  Note: If you rename any of the preceding game commands," << endl;
   cout << "  the changes will not be reflected here." << endl;
   if (currentLevel == 2) {                                 // Advanced level?
      cout << "-------------------Square Features--------------------" << endl;
      cout << "Circle:     l" << endl;
   } // if
   
   cout << "---------------------Square Types---------------------" << endl;
   cout << "Pink:       h" << endl;
   cout << "Orange:     v" << endl;
   cout << "Brown:      b" << endl;
   cout << "Dark Green: p" << endl;
   cout << "--------------------Square Colours--------------------" << endl;
   cout << "White:      0" << endl;
   cout << "Red:        1" << endl;
   cout << "Green:      2" << endl;
   cout << "Blue:       3" << endl;
   
   if (currentLevel > 0 && getBoard()->isBonusUnlocked()) { // At least intermdiate level and bonus features unlocked?
      cout << "Light Blue: 4" << endl;
      cout << "Yellow:     5" << endl;
   } // if
   
   cout << "-------------------Level Objective--------------------" << endl;
   // Stores the score difference between current score and score at the start of the level
   const unsigned long scoreDiff =
      (getBoard()->getScoreboard()->getScore()) - (getBoard()->getScoreboard()->getInitScore());

   if (currentLevel == 0) {                                // Beginner level?
      cout << "To complete the level, you must get a score of at least" << endl;
      cout << 200 - scoreDiff << " more." << endl;
   } else if (currentLevel == 1) {                         // Intermediate level?
      cout << "To complete the level, you must get a score of at least" << endl;
      cout << 300 - scoreDiff << " more." << endl;
   } else {
      cout << "To complete the level, you must ";
      
      if (scoreDiff < 500) {
         cout << "get a score of at least" << endl;
         cout << 500 - scoreDiff << " more and ";
      } // if
      
      cout << "unlock every locked square on the board." << endl;
   } // if
   
   cout << "------------------------------------------------------" << endl;
} // run
