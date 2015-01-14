//=============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module to provide functions to work with Window objects
// @version: 1.0 29/11/2014
//=============================================================================

// Window module (window.h)

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <X11/Xlib.h>
#include <iostream>
#include <string>

// Object definition
class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[11];
  int width, height;

 public:
  Xwindow(int width=500, int height=500);                                                   // Constructor; displays the window.
  ~Xwindow();                                                                               // Destructor; destroys the window.
  
  enum {White=0, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, DarkGreen, Black}; // Available colours.

  // Clears the window.
  void clearWindow();

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a border around a rectangle
  void outlineRectangle(int x, int y, int width, int height);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);

  // Draws a string
  void drawBigString(int x, int y, std::string msg, int colour=Black);

  // Prints the first 10000 available fonts
  void showAvailableFonts();

  // Draws a line
  void drawLine(int x1, int y1, int x2, int y2); 

  // Draws a border around an arc
  void drawArc(int x, int y, int width, int height, int angle1, int angle2);
  
  // Draws an arc
  void fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour);
  
  // Draws a circle
  void fillCircle(int x, int y, int r, int colour);
};

#endif
