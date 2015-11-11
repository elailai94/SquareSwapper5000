//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Square objects
// @version: 1.0 17/11/2014
//==============================================================================

// Square module (square.cc)

#include "square.h"
#include "textdisplay.h"
#include "window.h"

using namespace std; // Provides direct access to std

// See interface (header file).
void Square::notifyDisplay() {
   textdisplay->notify(row, col, feature, type, colour);
} // notifyDisplay

// See interface (header file).
void Square::drawSpecialType(int typeColour) {
   if (feature == 'l') { // Square with special feature?
   	  window->fillArc(x, y, width, height, -180, 180, typeColour);
   } else {
   	  const int halfWidth = width / 2;
      window->fillRectangle(x + halfWidth, y, halfWidth, height, typeColour);
      window->outlineRectangle(x, y, width, height);
   } // if 
} // drawSpecialType

// See interface (header file).
void Square::notifyWindow() {
   if (colour == -1) {         // A hole created?
   	  window->fillRectangle(x, y, width, height);
   } else {
   	  if (feature == 'l') {    // Square with special feature?
         window->fillRectangle(x, y, width, height);
         window->fillCircle(x, y, width, colour);
      } else {
         window->fillRectangle(x, y, width, height, colour);      
      } // if

      if (type == 'h') {        // Lateral square?
         drawSpecialType(6);
      } else if (type == 'v') { // Upright square?
         drawSpecialType(7);
      } else if (type == 'b') { // Unstable square?
         drawSpecialType(8);
      } else if (type == 'p') { // Psychedelic square?
         drawSpecialType(9);
      } // if
   } // if
} // notifyWindow

// See interface (header file).
Square::Square(char type)
   : row(0), col(0), feature('_'), type(type), colour(0), textdisplay(0),
     x(0), y(0), height(0), width(0), window(0) {} // Constructor

// See interface (header file).
Square::~Square() {} // Destructor

// See interface (header file).
int Square::getRow() const {
   return row;
} // getRow

// See interface (header file).
int Square::getCol() const {
   return col;
} // getCol

// See interface (header file).
char Square::getFeature() const {
   return feature;
} // getFeature

// See interface (header file).
char Square::getType() const {
   return type;
} // getType

// See interface (header file).
int Square::getColour() const {
   return colour;
} // getColour

// See interface (header file).
void Square::setFeature(const char newFeature) {
   feature = newFeature;
} // setFeature

// See interface (header file).
void Square::setColour(const int newColour) {
   colour = newColour;
} // setColour

// See interface (header file).
void Square::setDisplay(TextDisplay *textdisplay) {
   this->textdisplay = textdisplay;
} // setDisplay

// See interface (header file).
void Square::notify() {
   if (textdisplay != 0) { // textdisplay isn't NULL?
      notifyDisplay();
   } // if

   if (window != 0) {      // window isn't NULL?
      notifyWindow();
   } // if
} // notify

// See interface (header file).
void Square::setCoords(int row, int col, int x, int y) {
   this->row = row;
   this->col = col;
   this->x = x;
   this->y = y;
} // setCoords

// See interface (header file).
void Square::setCoords(int row, int col, int x, int y, int height, int width, Xwindow *window) {
   this->row = row;
   this->col = col;
   this->x = x;
   this->y = y;
   this->height = height;
   this->width = width;
   this->window = window;
} // setCoords
