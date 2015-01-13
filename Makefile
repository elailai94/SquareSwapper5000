CXX = g++
CXXFLAGS = -Wall -MMD
X11 = -lX11
NCURSES = -lncurses
EXEC = ss5k
OBJECTS = main.o level.o beginner.o intermediate.o advanced.o board.o scoreboard.o basicsquare.o square.o textdisplay.o unstablesquare.o uprightsquare.o lateralsquare.o psychedelicsquare.o command.o swap.o hint.o scramble.o levelup.o leveldown.o restart.o help.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${X11} ${NCURSES}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
