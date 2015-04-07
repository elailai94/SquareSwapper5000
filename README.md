# SquareSwapper5000
### About
SquareSwapper5000 is a simple tile-matching puzzle game, which is inspire by Candy Crush and Bejeweled. SquareSwapper5000 is written entirely in C++08 and builts on most UNIX-like operating systems (i.e.: Linux or Mac). The graphical component of the game is implemented using the X11 library.

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
- **-text** runs the program in text-mode only. No graphics displayed. The default behaviour (no **-text**) is to show both text and graphics
- **-seed xxx** sets the random number generator's seed to xxx. If the seed isn't set, the same random sequence is obtain every time the program is run
- **-scriptfile xxx** uses xxx for this level's initial board configuration. Files may contain a last line indicating a pre-determined order in which coloured BasicSquare should be generated. If a specified sequence is provided, this overrides any random generation of squares for that level. If no such sequence is provided, the default behaviour for that level should take place.
- **-startlevel n** starts the game in level n. The game starts in level 0 if this option is not supplied.

#### Game Commands 

### Known Issues
- Ncurses and Xwindow library has memory leaks
