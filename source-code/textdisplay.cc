//=============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module to provide functions to work with TextDisplay objects
// @version: 1.0 17/11/2014
//=============================================================================

// Textdisplay module (textdisplay.cc)

#include "textdisplay.h"

using namespace std; // Provides direct access to std

// See interface (header file).
TextDisplay::TextDisplay(int height, int width)
   :theDisplay(0), height(height), width(width) {
   string **newDisplay = new string*[height];

   // Allocates new memory from heap for theDisplay
   for (int i = 0; i < height; ++i) {
   	newDisplay[i] = new string[width];
   	// Allocates new memory from heap for each Square in a row of theDisplay
   	for (int j = 0; j < width; ++j) {
   	  	newDisplay [i][j] = "___";
   	} // for
   } // for

   theDisplay = newDisplay;
} // Constructor

// See interface (header file).
TextDisplay::~TextDisplay() {
   // Returns all memory allocated for each row of theDisplay back
   // to the heap.
   for (int i = 0; i < height; ++i) {
   	delete [] theDisplay[i];
   } // for
   delete [] theDisplay;
} // Destructor

// See interface (header file).
void TextDisplay::notify(int row, int col, char feature, char type, int colour) {
   if (colour == -1) { // Empty square signal encountered?
   	theDisplay[row][col] = "___";
   } else {
      (theDisplay[row][col]).at(0) = feature;
      (theDisplay[row][col]).at(1) = type;
      (theDisplay[row][col]).at(2) = '0' + colour;
   } // if
} // notify

// See interface (header file).
ostream &operator<<(ostream &out, const TextDisplay &td) {
   // Prints out each element in theDisplay to the screen.
   for (int i = 0; i < td.height; ++i) {
   	  // Prints out each element for each row of theDisplay to the screen.
   	  for (int j = 0; j < td.width; ++j) {
   	  	 out << td.theDisplay[i][j] << ' ';
   	  } // for
   	  out << endl;
   } // for

   return out;
} // Overloaded operator<<
