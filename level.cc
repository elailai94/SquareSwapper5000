//==============================================================================
// SquareSwapper5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Level objects
// @version: 1.0 21/11/2014
//==============================================================================

// Level module (level.cc)

#include "level.h"

using namespace std;             // Provides direct access to std

// See interface (header file).
ifstream *Level::getStream() const {
   return ifs;
} // getStream

// See interface (header file).
Board *Level::getBoard() const {
   return theBoard;
} // getBoard

// See interface (header file).
void Level::setStream(ifstream *ifs) {
   this->ifs = ifs;
} // setStream

// See interface (header file).
int Level::genSeqSize() const {
   return genSeq.size();
} // genSeqSize

// See interface (header file).
void Level::addToGenSeq(int colour) {
   genSeq.push_back(colour);
} // addToGenSeq

// See interface (header file).
int Level::getFromGenSeq() {
   if (genSeqPos >= genSeqSize()) { // Retrieval position out of range?
      genSeqPos = 0;
   } // if
   
   const int retval = genSeq.at(genSeqPos); // Stores the retrived value from genSeq to be return
   genSeqPos += 1;
   
   return retval;
} // getFromGenSeq

// See interface (header file).
Level::Level(Board *board, ifstream *ifs)
   : theBoard(board), ifs(ifs), genSeqPos(0) {} // Constructor

// See interface (header file).
Level::~Level() {}               // Destructor
