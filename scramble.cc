//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Scramble objects
// @version: 1.0 21/11/2014
//==============================================================================

// Scramble module (scramble.cc)

#include "scramble.h"
#include "board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
Scramble::Scramble(Board *board)
   : Command(board) {} // Constructor

// See interface (header file).
Scramble::~Scramble() {} // Destructor

// See interface (header file).
void Scramble::run() {
   if (getBoard() != 0) { // theBoard isn't NULL?
      getBoard()->scramble(false);
   } // if
} // run
