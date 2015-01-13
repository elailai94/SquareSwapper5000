/==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Advance objects
// @version: 2.1 01/12/2014
//==============================================================================

// Advance module (advance.cc)

#include <cstdlib>
#include <fstream>
#include "advance.h"
#include "Board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
int Advance::generateNumber(const int min, const int max) {
   const int n = max - min + 1;
   const int r = RAND_MAX % n;
   int x = 0;
   
   do {
        x = rand();
   } while (x >= RAND_MAX - r);
   
   return min + x % n;
} // generateNumber

// See interface (header file).
char Advance::generateFeature() {
   const int randNum = rand() % 5;                                             // Stores a randomly generated number between 0 and 4

   if ((randNum == 0) || (randNum == 1) || (randNum == 2) || (randNum == 3)) { // Need to map 0-3 to '_'?
   	  return '_';
   } else {
   	  return 'l';
   }
} // generateFeature

// See interface (header file).
int Advance:generateColour() {
   int randNum = 0;         // Stores a randomly generated number
   if (bonusUnlocked) {     // Bonus features unlocked?
      randNum = rand() % 6; // Generates number between 0 and 5
   } else {
      randNum = rand() % 4; // Generates number between 0 and 3
   } // if

   return randNum;
} // generateColour

// See interface (header file).
Advance::Advance(Board *board, string filename, const bool bonus)
   : Level(board, 0), bonusUnlocked(bonus) {
   if (filename != "") {                         // No file name specified on command line?
      setStream(new ifstream(filename.c_str()));
   } // if

   if (bonusUnlocked) {                          // Bonus features unlocked?
      const int randNum = generateNumber(8, 12); // Stores a randomly generated number between 8 and 12
      getBoard()->setHeight(randNum);
      getBoard()->setWidth(randNum);
   } else {
      getBoard()->setHeight(10);
      getBoard()->setWidth(10);
   } // if
} // Constructor

// See interface (header file).
Advance::~Advance() {
   delete getStream();
} // Destructor

// See interface (header file).
void Advance::initBoard() {
   // Fills in squares on board
   for (int i = 0; i < getBoard()->getHeight(); ++i) {
      for (int j = 0; j < getBoard()->getWidth(); j++) {
      	 if (getStream() != 0) {                        // File stream isn't NULL?
      	 	char f = '\0';                              // Stores the read in feature
            char t = '\0';                              // Stores the read in type
            int c = 0;                                  // Stores the read in colour

            *getStream() >> f >> t >> c;
		      getBoard()->createSquare(i, j, f, t, c);
      	 } else {
            const char genFeature = generateFeature(); // Stores the randomly generated feature
            const int genColour = generateColour();    // Stores the randomly generated colour

            getBoard()->createSquare(i, j, genFeature, '_', genColour);
         } // if
      } // for
   } // for

   char c = '\0';                                      // Stores the read in colour

   if (getStream() != 0) {                             // File stream isn't NULL?
   	  // Adds each digit on the last line of file (if any) to genSeq
      while (*getStream() >> c) {
         addToGenSeq(c - '0');
      } // while
   } else {
      getBoard()->scramble(true);
   } // if
} // initBoard

// See interface (header file).
void Advance::generateSquare(const int row, const int col) {
   if (genSeqSize() > 0) {                    // Non-empty genSeq?
      const int genColour = getFromGenSeq();  // Stores the colour for the this generated square
      getBoard()->createSquare(row, col, '_', '_', genColour);
   } else {
      const int genColour = generateColour(); // Stores the randomly generated colour
      getBoard()->createSquare(row, col, '_', '_', genColour);
   } // if
} // generateSquare
