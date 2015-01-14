//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with LevelUp objects
// @version: 1.0 21/11/2014
//==============================================================================

// LevelUp module (levelup.h)

#ifndef __LEVELUP_H__
#define __LEVELUP_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class LevelUp: public Command {
public:
   LevelUp(Board *board); // Constructor
   ~LevelUp();            // Destructor

   // Runs the command.
   virtual void run();
};

#endif
