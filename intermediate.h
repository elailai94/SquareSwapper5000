//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Intermediate objects
// @version: 1.2 23/11/2014
//==============================================================================

// Intermediate module (intermediate.h)

#ifndef __INTERMEDIATE_H__
#define __INTERMEDIATE_H__

#include <string>
#include "level.h"

// Object declaration
class Board;

// Object definition
class Intermediate: public Level {
   const bool bonusUnlocked;                                           // Indicator for whether bonus features are unlocked for level

   // Generates a random number between min and max for the height and width of the
   // board to be created.
   //    Note: generateNumber is a slightly improved version of the default rand()
   //    function provided by the cstdlib library and partially eliminates bias
   //    towards the lower end.
   int generateNumber(const int min, const int max);

   // Generates a random character representing the special type of square to create.
   //    Note: generateSpecialType only generates the following characters: 'h', 'v', 'b', and 'p'.
   //    Each character has an equal probability of being generated.
   char generateSpecialType();

   // Generates a random number representing the colour of square.
   //    Note: Without bonus features, generateColour only generates a number between 0 and 3.
   //    The numbers 0 and 1 is generated with a probability of 1/3 each. The numbers 2 and 3
   //    is generated with a probability of 1/6 each. With bonus features, generateColour only
   //    generates a number between 0 and 5. Each number has an equal probability of being
   //    generated.
   int generateColour();
   
public:
   Intermediate(Board *board, std::string filename, const bool bonus); // Constructor
   ~Intermediate();                                                    // Destructor

   // Initializes the board.
   virtual void initBoard();

   // Generates a square.
   virtual void generateSquare(const int row, const int col);
};

#endif
