//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Intermediate objects
// @version: 1.2 23/11/2014
//==============================================================================

// Intermediate module (intermediate.cc)

#include <cstdlib>
#include <fstream>
#include "intermediate.h"
#include "Board.h"

using namespace std;     // Provides direct access to std

int numofSquaresGen = 0; // Stores the number of squares generated so far

// See interface (header file).
int Intermediate::generateNumber(const int min, const int max) {
   const int n = max - min + 1;
   const int r = RAND_MAX % n;
   int x = 0;
   
   do {
        x = rand();
   } while (x >= RAND_MAX - r);
   
   return min + x % n;
} // generateNumber

// See interface (header file).
char Intermediate::generateSpecialType() {
   const int randNum = rand() % 4; // Stores a randomly generated number between 0 and 3

   if (randNum == 0) {             // Generate lateral square type? 
      return 'h';
   } else if (randNum == 1) {      // Generate upright square type?
      return 'v';
   } else if (randNum == 2) {      // Generate unstable square type?
      return 'b';
   } else {
      return 'p';
   } // if
} // generateType

// See interface (header file).
int Intermediate::generateColour() {
   int randNum = rand() % 6;     // Stores a randomly generated number between 0 and 5

   if (!bonusUnlocked) {         // Bonus features aren't unlocked?          
      if (randNum == 4) {        // Need to map four to zero?
         randNum = 0;
      } else if (randNum == 5) { // Need to map five to one?
         randNum = 1;
      } // if
   } // if

   return randNum;
} // generateColour

// See interface (header file).
Intermediate::Intermediate(Board *board, string filename, const bool bonus)
   : Level(board, 0), bonusUnlocked(bonus) {
   if (filename != "") { // File name specified on command line?
      setStream(new ifstream(filename.c_str()));
   } // if

   if (bonusUnlocked) {                          // Bonus features unlocked?
      const int randNum = generateNumber(8, 12); // Stores a randomly generated number between 8 and 12
      getBoard()->setHeight(randNum);
      getBoard()->setWidth(randNum);
   } else {
      getBoard()->setHeight(10);
      getBoard()->setWidth(10);
   }
} // Constructor

// See interface (header file).
Intermediate::~Intermediate() {
   delete getStream();
} // Destructor

// See interface (header file).
void Intermediate::initBoard() {
   // Fills in squares on board
   for (int i = 0; i < getBoard()->getHeight(); ++i) {
   	  for (int j = 0; j < getBoard()->getWidth(); j++) {
         if (getStream() != 0) {  // File stream isn't NULL?
            char f = '\0';        // Stores the read in feature
            char t = '\0';        // Stores the read in type
            int c = 0;            // Stores the read in colour

            *getStream() >> f >> t >> c;
            getBoard()->createSquare(i, j, f, t, c);
         } else {
            generateSquare(i,j);
         }
   	  } // for
   } // for

   char c = '\0';                // Stores the read in colour

   if (getStream() != 0) {       // File stream isn't NULL?
      // Adds each digit on the last line of file (if any) to genSeq
      while (*getStream() >> c) {
         addToGenSeq(c - '0');
      } // while
   } else {
   	  getBoard()->scramble(true);
   } // if
   
   numofSquaresGen = 0;  
} //initBoard

// See interface (header file).
void Intermediate::generateSquare(const int row, const int col) {
   if (genSeqSize() > 0) {                          // Non-empty genSeq?
      const int genColour = getFromGenSeq();        // Stores the colour for the this generated square
      getBoard()->createSquare(row, col, '_', '_', genColour);
   } else {
      const int genColour = generateColour();       // Stores the randomly generated colour
   
      if ((numofSquaresGen % 5) == 0) {             // Special square needed?
   	   const int genType = generateSpecialType(); // Stores the randomly generated special type
   	   getBoard()->createSquare(row, col, '_', genType, genColour);
      } else {
   	   getBoard()->createSquare(row, col, '_', '_', genColour);
      } // if
   } // if

   numofSquaresGen += 1;
} // generateSquare
