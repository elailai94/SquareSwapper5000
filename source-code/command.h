//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Command objects
// @version: 1.0 21/11/2014
//==============================================================================

// Command module (command.h)

#ifndef __COMMAND_H__
#define __COMMAND_H__

// Object declaration
class Board;

// Object definition
class Command {
   Board *theBoard;

protected:
   Board *getBoard();     // Accessor to theBoard field

public:
	Command(Board *board);  // Constructor
	virtual ~Command() = 0; // Destructor
	
	// Executes the command.
    virtual void execute() = 0;
};

#endif
