//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Board objects
// @version: 1.0 21/11/2014
//==============================================================================

// Board module (board.h)

#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <string>
#include <vector>

// Object declarations
class Square;
class Level;
class TextDisplay;
class ScoreBoard;
class Xwindow;

// Object definition
class Board {
	Square ***theBoard;
	TextDisplay *td;
	Level *l;
	Scoreboard *sb;
	Xwindow *win;
	int initialLevel;
	std::string initBoard;
	bool bonusUnlocked;

	int height;
	int width;

	// Swaps two squares
	void swap(Square* &s1, Square* &s2);

	// Checks for matches horizontal matches at row
	int checkRowMatch(const int row);

	// Checks for matches vertical at col
	int checkColMatch(const int col);

	// Helper function for finding matches
	int checkMatch(Square **arr, const int len);

	// Checks whole board for any matches
	int checkBoardMatch();

	// Calculates score of a single match
	int calcScore(const int len);

	// Fills the holes when squares are cleared
	void fillHoles();

	// Creates hole caused by matching a square and returns number of extra holes created
	// lenMatch is the size of the original match
	int createHole(Square *sq, const int lenMatch);

	// Counts the points from getting a match with chain reactions
	int countPoints();

	// Helper function for constructor
	void init(std::string filename);

	// Creates Special squares if needed
	void checkSpecialSquares(std::vector<Square *> &v, const int len, const int colour);

	// Finds a third square for potential match and returns its relative position
	//   according to swap
	// Specify if you want to search for a horizontal match or vertical
	// Row and col specify the square you want to swap out
	int findThirdSquare(const int row, const int col, const bool horizontalSearch, const int colour, const bool edgeBlock, const bool leftBlock);

	// Checks if coord is a valid coordinate.
	// Set yCoord to true if you want to see if the coord is valid in the y - direction
	bool isValid(const int row, const int col);

	// Checks if squares are the same colour
	bool sameColour(const Square *s1, const Square *s2);

	// Prints hint if silent is false and one is available.  Returns true if hint is available
	bool printHint(const int row, const int col, const int pos, const bool silent);

	// Finds match to make an l-shaped match.  Returns the index where the lmatch occures
	// or -1 if no lmatch exists
	int findLMatch(std::vector<Square *> &v, const int colour);
	
public:
   Board(const bool graphics, std::string filename, int level, const bool bonus); // Constructor
   ~Board();                                                                      // Destructor

   int getHeight() const;                                                         // Accessor to height field
   int getWidth() const;                                                          // Accessor to width field
   Scoreboard *getScoreboard() const;                                             // Accessor to sb field
   bool isBonusUnlocked() const;                                                  // Accessor to bonusUnlocked field

   void setHeight(int height);                                                    // Setter for height field
   void setWidth(int width);                                                      // Setter for width field
   void setDisplay(TextDisplay *t);                                               // Setter for td field
	
   // Destroys theBoard
   void clearBoard();

   // Prints out grid to ostream
   friend std::ostream &operator<<(std::ostream &out, const Board &b);

   // Generates new square
   void createSquare(const int h, const int w, const char feature, const char type, const int colour);

   // Swaps square at (x,y) in direction of z
   void swap(const int x, const int y, const int z);

   // Checks if all squares on board are unlocked
   bool unlocked();

   // Restarts board at current level
   void restart();

   // Goes to the next level
   void levelUp();

   // Goes to previous level
   void levelDown();

   // Outputs a valid move if available
   // Returns true if move is available
   // Silence output if silent is true
   bool hint(const bool silent);

   // Scrambles the board if no move is available, if override is true, scramble is forced
   void scramble(const bool override);

   // Checks if game is won
   bool isWon();
};

#endif
