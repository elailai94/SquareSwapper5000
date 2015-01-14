//=============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module to provide functions to work with Window objects
// @version: 1.0 29/11/2014
//=============================================================================

// Window module (window.cc)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std; // Provides direct access to std

// See interface (header file).
Xwindow::Xwindow(int width, int height): width(width), height(height) {
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[11][11]={"white", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown", "darkgreen", "black"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 11; ++i) {
      if (!XParseColor(d,cmap,color_vals[i],&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      if (!XAllocColor(d,cmap,&xcolour)) {
         cerr << "Bad colour: " << color_vals[i] << endl;
      }
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  XSelectInput(d,w,ExposureMask);
  XFlush(d);
  XEvent event;
  XNextEvent(d,&event); //Hang until the window is ready.
  XSelectInput(d,w,0);
} // Constructor

// See interface (header file).
Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
} // Destructor

// See interface (header file).
void Xwindow::clearWindow() {
   XClearWindow(d, w);
} // clearWindow

// See interface (header file).
void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
} // fillRectangle

// See interface (header file).
void Xwindow::outlineRectangle(int x, int y, int width, int height) {
  XDrawRectangle(d, w, gc, x, y, width - 1, height - 1);
} // outlineRectangle

// See interface (header file).
void Xwindow::drawString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
  XSetForeground(d, gc, colours[Black]);
} // drawString

// See interface (header file).
void Xwindow::drawBigString(int x, int y, string msg, int colour) {
  XSetForeground(d, gc, colours[colour]);
  // Font f = XLoadFont(d, "-*-helvetica-bold-r-normal--*-240-*-*-*-*-*");
  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";

  XFontStruct * f = XLoadQueryFont(d, name.str().c_str());
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f->fid;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
} // drawBigString

// See interface (header file).
void Xwindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
} // showAvailableFonts

// See interface (header file).
void Xwindow::drawLine(int x1, int y1, int x2, int y2){
  XDrawLine(d, w, gc, x1, y1, x2, y2);
} // drawLine

// See interface (header file).
void Xwindow::drawArc(int x1, int y1, int width, int height, int sAngle, int eAngle){
	XDrawArc(d,w,gc,x1,y1,width,height,sAngle*64,eAngle*64);
} // drawArc

// See interface (header file).
void Xwindow::fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour){	
  XSetForeground(d, gc, colours[colour]);
  XFillArc(d,w,gc,x,y,width,height,angle1*64,angle2*64);
  XSetForeground(d, gc, colours[Black]);
} // fillArc

// See interface (header file).
void Xwindow::fillCircle(int x, int y, int r, int colour){
  XSetForeground(d, gc, colours[colour]);
  XFillArc(d, w, gc, x, y, r,r,0*64,360*64);
  XSetForeground(d, gc, colours[Black]);
} // fillCircle
