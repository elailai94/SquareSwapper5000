//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with LevelDown objects
// @version: 1.0 21/11/2014
//==============================================================================

// LevelDown module (leveldown.h)

#ifndef __LEVELDOWN_H__
#define __LEVELDOWN_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class LevelDown: public Command {
public:
   LevelDown(Board *board); // Constructor
   ~LevelDown();            // Destructor

   // Runs the command.
   virtual void run();
};

#endif
