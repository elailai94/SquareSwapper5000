//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Hint objects
// @version: 1.0 21/11/2014
//==============================================================================

// Hint module (hint.cc)

#include "hint.h"
#include "board.h"

using namespace std; // Provides direct acccess to std

// See interface (header file).
Hint::Hint(Board *board, bool silent)
   : Command(board), silent(silent) {} // Constructor

// See interface (header file).
Hint::~Hint() {} // Destructor

// See interface (header file).
void Hint::run() {
   if (getBoard() != 0) { // theBoard isn't NULL?
      getBoard()->hint(silent);
   } // if
} // run
