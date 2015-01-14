//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with LevelUp objects
// @version: 1.0 21/11/2014
//==============================================================================

// LevelUp module (levelup.cc)

#include "levelup.h"
#include "board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
LevelUp::LevelUp(Board *board)
   : Command(board) {} // Constructor

// See interface (header file).
LevelUp::~LevelUp() {} // Destructor

// See interface (header file).
void LevelUp::run() {
   if (getBoard() != 0) { // theBoard isn't NULL?
      getBoard()->levelUp();
   } // if
} // run
