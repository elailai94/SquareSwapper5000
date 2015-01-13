//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Advance objects
// @version: 2.1 01/12/2014
//==============================================================================

// Advance module (advance.h)

#ifndef __ADVANCE_H__
#define __ADVANCE_H__

#include <string>
#include "level.h"

// Object declaration
class Board;

// Object definition
class Advance: public Level {
   const bool bonusUnlocked;                                      // Indicator for whether bonus features are unlocked for level

   // Generates a random number between min and max for the height and width of the
   // board to be created.
   //    Note: generateNumber is a slightly improved version of the default rand()
   //    function provided by the cstdlib library and partially eliminates bias
   //    towards the lower end.
   int generateNumber(const int min, const int max);

   // Generates a random character representing the square feature to create.
   //    Note: generateFeature only generates the following characters: '_' and 'l'.
   //    The character '_' is generated with a probability of 4/5. The character 'l'
   //    is generated with a probability of 1/5.
   char generateFeature();

   // Generates a random number representing the colour of square.
   //    Note: Without bonus features, generateColour only generates a number between
   //    0 and 3. Each number has equal probability of being generated. With bonus
   //    features, generateColour only generates a number between 0 and 5. Each number
   //    has equal probability of being generated.
   int generateColour();
   
public:
	Advance(Board *board, std::string filename, const bool bonus); // Constructor
	~Advance();                                                    // Destructor

	// Initializes the board.
   virtual void initBoard();

   // Generates a square.
   virtual void generateSquare(const int row, const int col);
};

#endif
