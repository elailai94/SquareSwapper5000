/==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with LevelDown objects
// @version: 1.0 21/11/2014
//==============================================================================

// LevelDown module (leveldown.cc)

#include "leveldown.h"
#include "Board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
LevelDown::LevelDown(Board *board)
   : Command(board) {} // Constructor

// See interface (header file).
LevelDown::~LevelDown() {} // Destructor

// See interface (header file).
void LevelDown::run() {
   if (getBoard() != 0) { // theBoard isn't NULL?
      getBoard()->levelDown();
   } // if
} // run
