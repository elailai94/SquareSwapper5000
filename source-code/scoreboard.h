//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Scoreboard objects
// @version: 2.1 03/12/2014
//==============================================================================

// Scoreboard module (scoreboard.h)

#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

// Object declaration
class Board;

// Object definition
class Scoreboard {
   unsigned long initScore;
   unsigned long curScore;
   int level;

public:
	Scoreboard(int level);                       // Constructor
	
  unsigned long getInitScore();                 // Accessor to initScore field
	unsigned long getScore();                     // Accessor to curScore field
	int getLevel();                               // Accessor to level field
	
	void setInitScore(const unsigned long score); // Setter for initScore field
	
	// adds s to current score
	void addScore(const int s);

	// returns current score back to initial score
	void rollbackScore();

	// checks if you're on the max level
	bool isMaxLevel();

	// increases level
	void incLevel(Board *b);

	// decreases level
	void decLevel(Board *b);

	// checks if level has been completed
	bool isLevelComplete(Board *b);
};

#endif
