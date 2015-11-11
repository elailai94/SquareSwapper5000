//=============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module to provide functions to work with TextDisplay objects
// @version: 1.0 17/11/2014
//=============================================================================

// Textdisplay module (textdisplay.h)

#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include <iostream>
#include <string>

// Object definition
class TextDisplay {
   std::string **theDisplay;                     // height x width display
   const int height;                             // height of the display
   const int width;                              // width of the display

public:
   TextDisplay(int height = 10, int width = 10); // Constructor
   ~TextDisplay();                               // Destructor
   
   // Notifies the location at row and col on theDisplay to update its colour,
   // type, and feature.
   //    Note: The TextDisplay is an observer of each Square. Squares call notify to
   //    update the (row,col) location to be colour, type, and feature.
   void notify(int row, int col, char feature, char type, int colour);

   // Prints out each element in td to the screen.
   //    Note: This function overloads the operator <<.
   friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
