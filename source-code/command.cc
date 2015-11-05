//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Command objects
// @version: 1.0 21/11/2014
//==============================================================================

// Command module (command.cc)

#include "command.h"
#include "board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
Board *Command::getBoard() {
   return theBoard;
} // getBoard

// See interface (header file).
Command::Command(Board *board)
   : theBoard(board) {} // Constructor

// See interface (header file).
Command::~Command() {} // Destructor
