//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Hint objects
// @version: 1.0 21/11/2014
//==============================================================================

// Hint module (hint.h)

#ifndef __HINT_H__
#define __HINT_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class Hint: public Command {
	bool silent;

public:
   Hint(Board *board, bool silent); // Constructor
   ~Hint();                         // Destructor

   // Runs the commmand.
   virtual void run();
};

#endif
