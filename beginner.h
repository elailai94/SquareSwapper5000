//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Beginner objects
// @version: 1.0 21/11/2014
//==============================================================================

// Beginner module (beginner.h)

#ifndef __BEGINNER_H__
#define __BEGINNER_H__

#include <string>
#include "level.h"

// Object declaration
class Board;

// Object definition
class Beginner: public Level {
public:
   Beginner(Board *board, std::string filename); // Constructor
   ~Beginner();                                  // Destructor

   // Initializes the board
   virtual void initBoard();
	
   // Generates a square
   virtual void generateSquare(const int row, const int col);
};

#endif
