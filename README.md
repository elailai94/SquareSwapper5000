# SquareSwapper5000
### About
SquareSwapper5000 is a simple tile-matching puzzle game, which is inspire by Candy Crush and Bejeweled. SquareSwapper5000 is written entirely in C++08 and builts on most UNIX-like operating systems (i.e.: Linux or Mac). The graphical component of the game is implemented using the X11 library.

### Screenshots
#### Welcome Screen
![SS5K_Screenshot1](https://cloud.githubusercontent.com/assets/7763904/7016955/b40af728-dcbd-11e4-8f0b-3ce54870f3c0.png)
#### Board (Text Display)
![SS5K_Screenshot2](https://cloud.githubusercontent.com/assets/7763904/7016997/7491dbb0-dcbe-11e4-9620-3b800a20139c.png)
#### Board (Graphical Display)
![SS5K_Screenshot3](https://cloud.githubusercontent.com/assets/7763904/7017035/f9791ca8-dcbe-11e4-95d7-bc570de1f78f.png)

### Compilation
```bash
make
```

### Execution
```bash
./ss5k
```

### Usage
#### Command-Line Options
- **-text** runs the program in text-mode only. No graphics displayed. The default behaviour (no **-text**) is to show both text and graphics.
- **-seed xxx** sets the random number generator's seed to *xxx*. If the seed isn't set, the same random sequence is obtain every time the program is run.
- **-seed time** sets the random number generator's seed to the system time. If the seed isn't set, the same random sequence is obtain every time the program runs.
- **-scriptfile xxx** uses *xxx* for this level's initial board configuration. Files may contain a last line indicating a pre-determined order in which coloured BasicSquare should be generated. If a specified sequence is provided, this overrides any random generation of squares for that level. If no such sequence is provided, the default behaviour for that level should take place.
- **-startlevel n** starts the game in level *n*. The game starts in level 0 if this option is not supplied.
- **-unlock** unlocks additional bonus features (see **Bonus Features** section) in the game.

#### Game Commands 
- **swap x y z** swaps the square at the (x,y) co-ordinate with the square in the z direction (0 for north, 1 for south, 2 for west, and 3 for east). For example, *swap 4 5 3* results in an attempt to swap the square at (4,5) to the square to the east (right) [i.e.: the square at cell location (4,6)].
- **hint** returns a valid move (x, y, z as above) that would lead to a match.
- **scramble** is only available if no moves are possible. This command reshuffles the squares on the board (no new cells are created).
- **levelup** increases the difficulty level of the game by one. The board is cleared and a new board is created for that level. If there is no higher level, this command has no effect.
- **leveldown** is the same as above, but this time decreasing the difficulty level of the game by one.
- **restart** clears the board and starts a new game at the same level.
- **help** provides a list of the available game commands. A key is provided to inform the player of how the encoding in the text display corresponds to the shapes and colours used in the graphical display. Additionally, there is an objective for the completion of the current level which the player is on.

> Note: By pressing **CTRL-D**, an end-of-file (EOF) signal terminates the game.

### Bonus Features
- There are welcome & exit screens.
- For the beginner and intermediate levels, there is an addition of light blue and yellow squares. The randomly generated grid size ranges from 8x8 to 12x12 inclusviely.

### Known Issues
- Ncurses and X11 library has memory leaks.
