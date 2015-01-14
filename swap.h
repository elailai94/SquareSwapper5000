//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Swap objects
// @version: 1.0 21/11/2014
//==============================================================================

// Swap module (swap.h)

#ifndef __SWAP_H__
#define __SWAP_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class Swap: public Command {
   int x;
   int y;
   int z;
public:
   Swap(int x, int y, int z, Board *board); // Constructor
   ~Swap();                                 // Destructor

   // Runs the command.
   virtual void run();
};

#endif
