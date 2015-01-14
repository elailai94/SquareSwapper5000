//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Help objects
// @version: 1.0 21/11/2014
//==============================================================================

// Help module (help.h)

#ifndef __HELP_H__
#define __HELP_H__

#include "command.h"

class Help: public Command {
public:
   Help(Board *board); // Constructor
   ~Help(); // Destructor

   // Runs the command.
   virtual void run();
};

#endif
