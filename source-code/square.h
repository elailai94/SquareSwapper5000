//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Square objects
// @version: 1.0 17/11/2014
//==============================================================================

// Square module (square.h)

#ifndef __SQUARE_H__
#define __SQUARE_H__

// Object declarations
class TextDisplay;
class Xwindow;

// Object definition
class Square {
   int row;                  // Row co-ordinate of the square
   int col;                  // Column co-ordinate of the square
   char feature;             // Advanced feature of the square
   char type;                // Type of square
   int colour;               // Current colour of the square
   TextDisplay *textdisplay; // Pointer to the text display

   // Note: The following fields are to be used in conjunction with the window.
   int x;                    // X co-ordinate of square 
   int y;                    // Y co-ordinate of square
   int height;               // Height of square to be display in window
   int width;                // Width of square to be display in window
   Xwindow *window;          // Pointer to the window

   // Notifies the TextDisplay of the change.
   void notifyDisplay();

   // Notifies the Window of the change for a special type of square.
   void drawSpecialType(int typeColour);

   // Notifies the Window of the change.
   void notifyWindow();

public:
   Square(char type);       // Constructor
   virtual ~Square() = 0;   // Destructor
   
   // Returns the row field.
   int getRow() const;

   // Returns the col field.
   int getCol() const;

   // Returns the feature field.
   char getFeature() const;

   // Returns the type field.
   char getType() const;

   // Returns the colour field.
   int getColour() const;

   // Sets feature field to newFeature.
   void setFeature(const char newFeature);

   // Sets colour field to newColour.
   void setColour(const int newColour);

   // Sets textdisplay field to textdisplay.
   void setDisplay(TextDisplay *textdisplay);

   // Notifies the TextDisplay and Window of any changes.
   //    Note: Board calls notify to notify the TextDisplay and Window of any changes.
   void notify();

   // Sets row, col, x, and y fields to their respective new values.
   //    Note: This method is to be used when only height, width, and window remains the same.
   void setCoords(int row, int col, int x, int y);

   // Sets row, col, x, y, height, width, and window fields to their respective new values.
   //    Note: This method is to be used when no fields remains the same.
   void setCoords(int row, int col, int x, int y, int height, int width, Xwindow *window);
};

#endif
