//==============================================================================
// SquareSwapper 5000
//
// @author: Elisha Lai & Laxman Sooriyathas
// @description: Module for providing functions to work with Board objects
// @version: 1.0 21/11/2014
//==============================================================================

// Board module (board.cc)

#include "board.h"
#include "square.h"
#include "level.h"
#include "beginner.h"
#include "intermediate.h"
#include "advanced.h"
#include "textdisplay.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include "scoreboard.h"
#include "window.h"
#include <cmath>
#include <cstdlib>

using namespace std;                                          // Provides direct access to std

// Length and width of window for graphical version of game
const int windowSize = 600;

// See interface (header file).
Board::Board(const bool graphics, string filename, int level, const bool bonus)
   : theBoard(0), td(0), l(0), sb(0), win(0), initialLevel(0), initBoard(filename),
     bonusUnlocked(bonus), height(0), width(0) {
    if (level < 0 || level > 2) { // Invalid level?
       level = 0;
	  } // if

    initialLevel = level;
	  sb = new ScoreBoard(level);

	  if (graphics) { // Graphical version of game required?
		   win = new Xwindow(windowSize, windowSize);
	  } // if
	init(filename);
} // Constructor

// See interface (header file).
void Board::init(string filename) {
	// calls level's init method to initialize grid;
	if (sb->getLevel() == 0) {
		l = new Beginner(this, filename);
	} else if (sb->getLevel() == 1) {
		l = new Intermediate(this, filename, bonusUnlocked);
	} else if (sb->getLevel() == 2) {
		l = new Advanced(this, filename, bonusUnlocked);
	} // if

	theBoard = new Square**[height];
	for (int i = 0; i < height; i++) {
		theBoard[i] = new Square*[width];
		for (int j = 0; j < width; j++) {
			theBoard[i][j] = 0;
		}
	}

	td = new TextDisplay(height, width);

	if (win != 0) {
		win->clearWindow();
	}

	l->initBoard();
	cout << *this << endl;
} // init

// See interface (header file).
Board::~Board() {
	clearBoard();
	delete td;
	delete l;
	delete sb;
	delete win;
} // Destructor

// See interface (header file).
void Board::clearBoard() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete theBoard[i][j];
			theBoard[i][j] = 0;
		}
		delete [] theBoard[i];
	}
	delete [] theBoard;
} // clearBoard

// See interface (header file).
void Board::setHeight(int height) {
	this->height = height;
} // setHeight

// See interface (header file).
void Board::setWidth(int width) {
	this->width = width;
} // setWidth

// See interface (header file).
int Board::getHeight() const {
	return height;
} // getHeight

// See interface (header file).
int Board::getWidth() const {
	return width;
} // getWidth

// See interface (header file).
ScoreBoard *Board::getScoreboard() const {
   return sb;
} // getScoreboard

// See interface (header file).
bool Board::isBonusUnlocked() const {
   return bonusUnlocked;
} // isBonusUnlocked

// See interface (header file).
void Board::setDisplay(TextDisplay *t) {
    td = t;
} // setDisplay

// See interface (header file).
ostream &operator<<(ostream &out, const Board &b) {
	out << "Level:       " << b.sb->getLevel() << endl;
	out << "Score:       " << b.sb->getScore() << endl;
	out << string(3 * b.width, '-') << endl;
	out << *(b.td);
	return out;
} // Overloaded operator<<

// See interface (header file).
void Board::createSquare(const int h, const int w, const char feature, const char type, const int colour) {

	if (theBoard[h][w]) {
		delete theBoard[h][w];
	}

	switch (type) {
		case 'h':
			theBoard[h][w] = new LateralSquare;
			break;
		case 'v':
			theBoard[h][w] = new UprightSquare;
			break;
		case 'b':
			theBoard[h][w] = new UnstableSquare;
			break;
		case 'p':
			theBoard[h][w] = new PsychedelicSquare;
			break;
		default:
			theBoard[h][w] = new BasicSquare;
			break;
	}

    // window dimensions for each cell
	const int cellSizeWidth = windowSize / width;
	const int cellSizeHeight = windowSize / height;

	// settings characteristics of new square
	theBoard[h][w]->setDisplay(td);
	theBoard[h][w]->setFeature(feature);
	theBoard[h][w]->setCoords(h,w, w * cellSizeWidth, h * cellSizeHeight, cellSizeHeight, cellSizeWidth, win);
	theBoard[h][w]->setColour(colour);
	theBoard[h][w]->notify();
} // createSquare

// See interface (header file).
void Board::swap(Square* &s1, Square* &s2) {
  // swapping pointers
	Square *temp = s1;
	s1 = s2;
	s2 = temp;
	temp = 0;

  // window dimensions for each cell
  const int cellSizeWidth = windowSize / width;
	const int cellSizeHeight = windowSize / height;

	// switching coords
	const int tempX = s1->getRow();
	const int tempY = s1->getCol();
	s1->setCoords(s2->getRow(), s2->getCol(), s2->getCol() * cellSizeWidth, s2->getRow() * cellSizeHeight);
	s2->setCoords(tempX, tempY, tempY * cellSizeWidth, tempX * cellSizeHeight);

	// notify the textdisplay
	s1->notify();
	s2->notify();
} // swap

// See interface (header file).
void Board::swap(const int x, const int y, const int z) {
  int r = x;
	int c = y;
	// checking for valid co-ordinates
	if ((x >= 0) && (x < height) && (y >= 0) && (y < width)) {

		switch (z) {		// find the co-ordinates of the location we're swapping with
			case 0:
				if (x > 0) {
					r = r - 1;
				}
				break;
			case 1:
				if (x < (height - 1)) {
					r = r + 1;
				}
				break;
			case 2:
				if (y > 0) {
					c = c - 1;
				}
				break;
			case 3:
				if (y < (width - 1)) {
					c = c + 1;
				}
				break;
			default:
				cerr << "Not a valid direction" << endl;
				break;
		}

		// make the swap, check if any points were made
		if ((r != x) || (c != y)) {		// check if we're not swapping the same square
			swap(theBoard[x][y], theBoard[r][c]);
			cout << *this << endl;
			int points = countPoints();
			if (!points) {				// swap didn't get any points, so it's an invalid swap
				swap(theBoard[x][y], theBoard[r][c]);		// swap back to original
				cout << *this << endl;
			}
		}
	} else {
		cerr << "Invalid coordinates" << endl;
	}
} // swap

// See interface (header file).
int Board::countPoints() {
	int total = 0;		// tracks total score
	int i = 0;			// used to track chain reaction count
	bool madeMatch = true;		// true if match was made

	while (madeMatch) {
		int score = checkBoardMatch();		// check if there's any matches and store points
		if (!score) {						// if no points were scored, then there's no matches
			madeMatch = false;
		} else {
			score = score * pow(2.0, i++);
			total = total + score;		// add to total score including bonus for chain reaction
			sb->addScore(score);
			cout << *this << endl;
			if (sb->isLevelComplete(this)) {
				break;
			}
			fillHoles();
			cout << *this << endl;
		}
	}
	if (sb->isLevelComplete(this)) {
		cout << "Level Complete!" << endl;
		levelUp();
	}
	return total;
} // countPoints

// See interface (header file).
bool Board::isWon() {
	return sb->isLevelComplete(this) && sb->isMaxLevel();
} // isWon

// See interface (header file).
int Board::checkMatch(Square **arr, const int len) {

	int lenMatch = 0; // length of the match
	vector<Square *> curMatch; // hold the pointers that are currently being matched
	int score = 0;

	// loop through array to find matches
	for (int i = 0; i < len; i++) {
		if (!lenMatch) {				// must be first square
			curMatch.push_back(arr[i]);
			lenMatch++;
			continue;
		} else if (curMatch.back()->getColour() == arr[i]->getColour()) {	// current square matches previous square
			curMatch.push_back(arr[i]);
			lenMatch++;

			if (i != (len - 1)) {
				continue;
			}
		} else if (lenMatch < 3) {
			// current square is different, so clear vector and start count
			curMatch.clear();
			lenMatch = 0;
			curMatch.push_back(arr[i]);
			lenMatch++;
		}


		if (lenMatch >= 3) {  // we found a match of 3 or more, so it's a valid match

			int numHoles = 0;    // number of holes created by special squares

			int colour = curMatch[0]->getColour(); // colour of the matched squares

			// try to find l-match
			int lMatchPos = findLMatch(curMatch, colour);



		    // change each matched square to a hole
			for (vector<Square *>::iterator j = curMatch.begin(); j < curMatch.end(); j++) {
				numHoles = numHoles + createHole(*j, lenMatch);
			}

			score = score + calcScore(numHoles); // calculates score for single match


			if (lMatchPos != -1) {
				// found an l-Match create unstable square
				createSquare(curMatch[lMatchPos]->getRow(), curMatch[lMatchPos]->getCol(), '_', 'b', colour);
				curMatch.erase(curMatch.begin() + lMatchPos);
			} else {
				checkSpecialSquares(curMatch, lenMatch, colour);	// will create special squares if necessary
			}

			curMatch.clear();
			lenMatch = 0;
			curMatch.push_back(arr[i]);
			lenMatch++;
		}

	}
	return score;
} // checkMatch

// See interface (header file).
int Board::findLMatch(vector<Square *> &v, const int colour) {

	vector<Square *> lpiece;
	bool horizontalSearch = true;

	// check if we're going to find the horizontal piece or vertical
	if (v[0]->getRow() == v[1]->getRow()) {
		horizontalSearch = false;
	}

	// check beginning and end of our current match to find the other piece of the l-match
	for (unsigned int i = 0; i < v.size(); i = i + v.size() - 1) {
		bool foundMatch = false;

		// checks each direction for matches
		for (int inc = 1; inc >= -1; inc = inc - 2) {

			int row = v[i]->getRow();
			int col = v[i]->getCol();

			horizontalSearch ? col = col + inc : row = row + inc;

			// keep adding squares to the vector if colours match
			do {
				if (isValid(row, col) && (theBoard[row][col]->getColour() == colour)) {
					lpiece.push_back(theBoard[row][col]);
					horizontalSearch ? col = col + inc : row = row + inc;
					foundMatch = true;
				} else {
					foundMatch = false;
				}
			} while (foundMatch);

			// if there are at least 2 new squares, we have an l-match
			if (lpiece.size() >= 2) {
				v.insert(v.end(), lpiece.begin(), lpiece.end());
				return i;
			}
		}
	}

	return -1;
} // findLMatch

// See interface (header file).
int Board::createHole(Square *sq, const int lenMatch) {
    // check if square is not a hole
	if (sq->getColour() != -1) {

		// destroying a basic block
		if (sq->getType() == '_') {
			sq->setColour(-1);
			sq->notify();
			return 1;
		}

		// destroy all blocks in a radius depending on lenMatch
		if (sq->getType() == 'b') {
			sq->setColour(-1);
			sq->notify();
			int numHoles = 1;
			int radius = (lenMatch == 3) ? 1 : 2;

			for (int i = sq->getRow() - radius; i <= (sq->getRow() + radius); i++) {
				for (int j = sq->getCol() - radius; j <= (sq->getCol() + radius); j++) {
					if (isValid(i, j)) {
						numHoles = numHoles + createHole(theBoard[i][j], lenMatch);
					}
				}
			}
			return numHoles;
		}

		// destroy all blocks on the row
		if (sq->getType() == 'h') {
			sq->setColour(-1);
			sq->notify();
			int numHoles = 1;
			for (int i = 0; i < width; i++) {
				numHoles = numHoles + createHole(theBoard[sq->getRow()][i], lenMatch);
			}
			return numHoles;
		}

		// destroy all blocks on the column
		if (sq->getType() == 'v') {
			sq->setColour(-1);
			sq->notify();
			int numHoles = 1;
			for (int i = 0; i < height; i++) {
				numHoles = numHoles + createHole(theBoard[i][sq->getCol()], lenMatch);
			}
			return numHoles;
		}

		// destroy all blocks that are the same colour as sq
		if (sq->getType() == 'p') {
			int prevColour = sq->getColour();
			sq->setColour(-1);
			sq->notify();
			int numHoles = 1;
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					if (theBoard[i][j]->getColour() == prevColour) {
						numHoles = numHoles + createHole(theBoard[i][j], lenMatch);
					}
				}
			}
			return numHoles;
		}

	}

	return 0;
} // createHole

// See interface (header file).
void Board::checkSpecialSquares(vector<Square *> &v, const int len, const int colour) {
	// get the characteristics of the new special square
	char type = '\0';
	int halfLen = len / 2;
	int row = v[halfLen]->getRow();
	int col = v[halfLen]->getCol();

	// determine what special square we are going to create
	if (len <= 3) {
		return;
	}  else if (len == 4) {

		// figure out if the special square will be lateral or upright
		if (v[0]->getRow() == v[1]->getRow()) {			// horizontal match
			type = 'h';
		} else {
			type = 'v';
		}
	} else {
		// match is 5 or greater
		type = 'p';
	}


	v.erase(v.begin() + halfLen);
	createSquare(row, col, '_', type, colour);
} // checkSpecialSquares

// See interface (header file).
int Board::calcScore(const int len) {
	// return points for matches of various sizes
	if (len == 3) {
		return 3;
	} else if (len == 4) {
		return 8;
	} else if (len == 5) {
		return 15;
	} else if (len > 5) {
		return 4 * len;
	} else {
		return 0;
	}
} // calcScore

// See interface (header file).
int Board::checkBoardMatch() {
	int score = 0;

	// look for horizontal matches and add points to score
	for (int i = 0; i < height; i++) {
		score = score + checkRowMatch(i);
	}
	// look for vertical matches and add points to score
	for (int j = 0; j < width; j++) {
		score = score + checkColMatch(j);
	}

	return score;
} // checkBoardMatch

// See interface (header file).
int Board::checkRowMatch(const int row) {
	return checkMatch(theBoard[row], width);
} // checkRowMatch

// See interface (header file).
int Board::checkColMatch(const int col) {
	Square *arr[height];
	// create an array of squares from the ith row of col
	for (int i = 0; i < height; i++) {
		arr[i] = theBoard[i][col];
	}
	return checkMatch(arr, height);
} // checkColMatch

// See interface (header file).
void Board::fillHoles() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (theBoard[i][j]->getColour() == -1) {    // if square is a whole
				int k = i;

				// keep swapping hole to the top
				while (k > 0) {
					swap(theBoard[k][j], theBoard[k - 1][j]);
					k--;
				}
				l->generateSquare(k, j);                // generate new square at hole
			}
		}
	}
} // fillHoles

// See interface (header file).
bool Board::unlocked() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (theBoard[i][j]->getFeature() == 'l') {	// if square is locked then board is not unlocked
				return false;
			}
		}
	}
	return true;
} // unlocked

// See interface (header file).
void Board::restart() {
	sb->rollbackScore();
	clearBoard();
	delete td;
	delete l;
	if (sb->getLevel() == initialLevel) {
		init(initBoard);
	} else {
		init("");
	}
} // restart

// See interface (header file).
void Board::levelUp() {
	sb->incLevel(this);
} // levelUp

// See interface (header file).
void Board::levelDown() {
	sb->decLevel(this);
} // levelDown

// See interface (header file).
bool Board::sameColour(const Square *s1, const Square *s2) {
	return s1->getColour() == s2->getColour();
} // sameColour

// See interface (header file).
bool Board::printHint(const int row, const int col, const int pos, const bool silent) {
	if (pos != -1) {
		if (!silent) {
			cout << "Hint: swap " << row << " " << col << " " << pos << endl;
		}
		return true;
	}
	return false;
} // printHint

// See interface (header file).
bool Board::hint(const bool silent) {

	// holds the relative position of matching square
	int horizontalSquare = -1;
	int verticalSquare = -1;

	// look for horizontal match first
	for (int i = 0; i < height; i++) {
		for (int j = 0; (j + 2) < width; j++) {
			if (sameColour(theBoard[i][j], theBoard[i][j+1])) {


				// find third square to the left
				horizontalSquare = findThirdSquare(i, j - 1, true, theBoard[i][j]->getColour(), true, true);

				if (printHint(i, j - 1, horizontalSquare, silent)) {
					return true;
				}

				// find third square to the right
				horizontalSquare = findThirdSquare(i, j + 2, true, theBoard[i][j]->getColour(), true, false);

				if (printHint(i, j + 2, horizontalSquare, silent)) {
					return true;
				}

			// find third square in the middle
			} else if (sameColour(theBoard[i][j], theBoard[i][j + 2])) {
				horizontalSquare = findThirdSquare(i, j + 1, true, theBoard[i][j]->getColour(), false, false);

				if (printHint(i, j + 1, horizontalSquare, silent)) {
					return true;
				}

			}
		}
	}

	// look for vertical match
	for (int i = 0; i < height; i++) {
		for (int j = 0; (j + 2) < width; j++) {
			if (sameColour(theBoard[j][i], theBoard[j + 1][i])) {

				// find third square at the top
				verticalSquare = findThirdSquare(j - 1, i, false, theBoard[i][j]->getColour(), true, true);

				if (printHint(j - 1, i, verticalSquare, silent)) {
					return true;
				}

				// find third square at the bottom
				verticalSquare = findThirdSquare(i + 2, j, false, theBoard[i][j]->getColour(), true, false);

				if (printHint(j + 2, i, verticalSquare, silent)) {
					return true;
				}
				// find the middle square
			} else if (sameColour(theBoard[j][i], theBoard[j + 2][i])) {

				verticalSquare = findThirdSquare(j + 1, i, false, theBoard[i][j]->getColour(), false, false);

				if (printHint(j + 1, i, verticalSquare, silent)) {
					return true;
				}
			}
		}
	}

	if (!silent) {
		cout << "No moves available. Please scramble." << endl;
	}

	return false;
} // hint

// See interface (header file).
int Board::findThirdSquare(const int row, const int col, const bool horizontalSearch, const int colour, const bool edgeBlock, const bool leftBlock) {

	if (horizontalSearch) {
		// look up and below for a match
		if (isValid(row - 1, col) && (theBoard[row - 1][col]->getColour() == colour)) {
			return 0;
		} else if (isValid(row + 1, col) && (theBoard[row + 1][col]->getColour() == colour)) {
			return 1;
		}
		// check if edge block
		if (edgeBlock) {
			// look to the left
			if (leftBlock) {
				if (isValid(row, col - 1) && (theBoard[row][col - 1]->getColour() == colour)) {
					return 2;
				}
			// look to the right
			} else {
				if (isValid(row, col + 1) && (theBoard[row][col + 1]->getColour() == colour)) {
					return 3;
				}
			}
		}
	} else {
		// look to the left and right for a match
		if (isValid(row, col - 1) && (theBoard[row][col - 1]->getColour() == colour)) {
			return 2;
		} else if (isValid(row, col + 1) && (theBoard[row][col + 1]->getColour() == colour)) {
			return 3;
		}
		// check if its an edge block
		if (edgeBlock) {
			// look above for a match
			if (leftBlock) {
				if (isValid(row - 1, col) && (theBoard[row - 1][col]->getColour() == colour)) {
					return 0;
				}
				// look below for a match
			} else {
				if (isValid(row + 1, col) && (theBoard[row + 1][col]->getColour() == colour)) {
					return 1;
				}
			}
		}
	}

	return -1;
} // findThirdSquare

// See interface (header file).
bool Board::isValid(const int row, const int col) {
	return (row >= 0) && (row < height) && (col >= 0) && (col < width);
} // isValid

// See interface (header file).
void Board::scramble(const bool override) {
	// randomly selects numbers for coordinates of squares to swap
	if (!hint(true) || override) {
		for (int i = 0; i < width * height; i++) {
			const int s1row = rand() % (height - 1);
			const int s1col = rand() % (width - 1);
			const int s2row = rand() % (height - 1);
			const int s2col = rand() % (width - 1);
			swap(theBoard[s1row][s1col], theBoard[s2row][s2col]);
		}
	} else {
		cout << "Can't scramble when a move is available." << endl;
	} // if

    if (!override) {
	   cout << *this << endl;
    }
} // scramble
