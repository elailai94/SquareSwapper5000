//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Level objects
// @version: 1.0 21/11/2014
//==============================================================================

// Level module (level.h)

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <fstream>
#include <vector>

// Object declaration
class Board;

// Object definition
class Level {
   Board *theBoard;                         // Pointer to the board object
   std::ifstream *ifs;                      // Input file stream
   int genSeqPos;                           // Position to retrieve the next colour from genSeq
   std::vector<int> genSeq;                 // Generation sequence of colours for basic squares

protected:
   std::ifstream *getStream() const;        // Accessor to ifs field
   Board *getBoard() const;                 // Accessor to theBoard field

   void setStream(std::ifstream *ifs);      // Setter for ifs field

   // Returns the number of colours in genSeq.
   int genSeqSize() const;

   // Adds colour to genSeq.
   void addToGenSeq(int colour);

   // Gets the next colour from genSeq.
   int getFromGenSeq();

public:
   Level(Board *board, std::ifstream *ifs); // Constructor
   virtual ~Level();                        // Destructor
   
   // Initializes the board
   virtual void initBoard() = 0;

   // Generates a square
   virtual void generateSquare(const int row, const int col) = 0;
};

#endif
