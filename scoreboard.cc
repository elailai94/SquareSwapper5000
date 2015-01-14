//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Scoreboard objects
// @version: 2.1 03/12/2014
//==============================================================================

// Scoreboard module (scoreboard.cc)

#include "scoreboard.h"
#include "board.h"

using namespace std;    // Provides direct access to std

const int MAXLEVEL = 2; // Stores the maximum level of the game

// See interface (header file).
Scoreboard::Scoreboard(int level)
   : initScore(0), curScore(0), level(level) {} // Constructor

// See interface (header file).
unsigned long ScoreBoard::getInitScore() {
   return initScore;
} // getInitScore

// See interface (header file).
unsigned long ScoreBoard::getScore() {
	return curScore;
} // getScore

// See interface (header file).
void ScoreBoard::addScore(const int s) {
	curScore = curScore + s;
} // addScore

// See interface (header file).
void ScoreBoard::rollbackScore() {
	curScore = initScore;
} // rollbackScore

// See interface (header file).
int ScoreBoard::getLevel() {
	return level;
} // getLevel

// See interface (header file).
void ScoreBoard::incLevel(Board *b) {
	if (level < MAXLEVEL) {
		level++;
		setInitScore(curScore);
		b->restart();
	} else {
		cout << *b << endl;
	}
} // incLevel

// See interface (header file).
bool ScoreBoard::isMaxLevel() {
	return level == MAXLEVEL;
} // isMaxLevel

// See interface (header file).
void ScoreBoard::decLevel(Board *b) {
	if (level > 0) {
		level--;
		setInitScore(curScore);
		b->restart();
	} else {
		cout << *b << endl;
	} // if
} // decLevel

// See interface (header file).
void ScoreBoard::setInitScore(const unsigned long score) {
	initScore = score;
} // setInitScore

// See interface (header file).
bool ScoreBoard::isLevelComplete(Board *b) {
	if (level == 0) {
		return (curScore - initScore) >= 200;
	} else if (level == 1) {
		return (curScore - initScore) >= 300;
	} else if (level == 2) {
		return ((curScore - initScore) >= 500) && b->unlocked();
	} // if
	
	return false;
} // isLevelComplete
