//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Swap objects
// @version: 1.0 21/11/2014
//==============================================================================

// Swap module (swap.cc)

#include "swap.h"
#include "board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
Swap::Swap(int x, int y, int z, Board *board)
   : Command(board), x(x), y(y), z(z) {} // Constructor

// See interface (header file).
Swap::~Swap() {} // Destructor

// See interface (header file).
void Swap::run() {
	if (getBoard() != 0) { // theBoard isn't NULL?
	   getBoard()->swap(x, y, z);
    } // if
} // run
