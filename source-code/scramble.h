/==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Scramble objects
// @version: 1.0 21/11/2014
//==============================================================================

// Scramble module (scramble.h)

#ifndef __SCRAMBLE_H__
#define __SCRAMBLE_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class Scramble: public Command {
public:
   Scramble(Board *board); // Constructor
   ~Scramble();            // Destructor

   // Runs the command.
   virtual void run();
};

#endif
