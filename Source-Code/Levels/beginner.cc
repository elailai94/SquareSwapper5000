//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Beginner objects
// @version: 1.0 21/11/2014
//==============================================================================

// Beginner module (beginner.cc)

#include <fstream>
#include <stack>
#include "beginner.h"
#include "Board.h"

using namespace std; // Provides direct access to std

// See interface (header file).
Beginner::Beginner(Board *board, string filename)
   : Level(board, 0) {
   if (filename == "") { // No file name specified on command line?
      setStream(new ifstream("sequence.txt"));
   } else {
   	  setStream(new ifstream(filename.c_str()));
   } // if

   // Sets height and width to 10
   getBoard()->setHeight(10);
   getBoard()->setWidth(10);
} // Constructor

// See interface (header file).
Beginner::~Beginner() {
   delete getStream();
} // Destructor

// See interface (header file).
void Beginner::initBoard() {
   // Fills in squares on board
   for (int i = 0; i < getBoard()->getHeight(); i++) {
	  for (int j = 0; j < getBoard()->getWidth(); j++) {
	  	 char f = '\0';                           // Stores the read in feature
         char t = '\0';                           // Stores the read in type
         int c = 0;                               // Stores the read in colour
         
		 *getStream() >> f >> t >> c;
		 getBoard()->createSquare(i, j, f, t, c);
	  } // for
   } // for

   char c = '\0';                                 // Stores the read in colour

   // Adds each digit on the last line of file to genSeq
   while (*getStream() >> c) {
      addToGenSeq(c - '0');
   } // while

   if (genSeqSize() == 0) {                       // No generation sequence specified?
      stack<int> genSeqStack;                     // Temporary stack to store the generation sequence

      ifstream otherStream("sequence.txt");       // Connects stream and sequence.txt
      otherStream.seekg(0, otherStream.end);      // Moves stream position to EOF in sequence.txt
      const int streamSize = otherStream.tellg(); // Stores position of EOF in sequence.txt
      // Reads in the last line of sequence.txt until a newline character is
      // encountered
      for (int i = streamSize - 2; i > 0; --i) {
      	char c = '\0';                            // Stores the read in character

      	otherStream.seekg(i);
      	otherStream.get(c);

      	if (c == '\n') {                         // Newline character encountered?
      		break;
      	} // if
      	
      	genSeqStack.push(c - '0'); 
      } // for
      
      // Copies over all colours in genSeqStack to genSeq
      while (!genSeqStack.empty()) {
         const int c = genSeqStack.top();       // Stores the top colour of genSeqStack
         genSeqStack.pop();
         addToGenSeq(c);
      } // while
   } // if
} // initBoard

// See interface (header file).
void Beginner::generateSquare(const int row, const int col) {
   const int genColour = getFromGenSeq();
   getBoard()->createSquare(row, col, '_', '_', genColour);
} // generateSquare
