//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Restart objects
// @version: 1.0 21/11/2014
//==============================================================================

// Restart module (restart.h)

#ifndef __RESTART_H__
#define __RESTART_H__

#include "command.h"

// Object declaration
class Board;

// Object definition
class Restart: public Command {
public:
   Restart(Board *board); // Constructor
   ~Restart();            // Destructor

   // Runs the command.
   virtual void run();
};

#endif
