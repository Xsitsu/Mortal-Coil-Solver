CC = g++
PROG = solver
P = src/

all: $(PROG) clean

$(PROG): $(P)main.cpp controller.o logger.o
	$(CC) -o $(PROG).exe $(P)main.cpp $(P)controller.o $(P)logger.o $(P)httpservice.o $(P)gameboard.o $(P)guess.o $(P)fileio.o $(P)bcu.o $(P)bcd.o $(P)bcl.o $(P)bcr.o $(P)bcs.o

controller.o: $(P)Controller.cpp $(P)Controller.h httpservice.o gameboard.o logger.o guess.o
	$(CC) -c -o $(P)controller.o $(P)Controller.cpp $(P)httpservice.o $(P)gameboard.o $(P)logger.o $(P)guess.o

httpservice.o: $(P)HttpService.cpp $(P)HttpService.h logger.o gameboard.o fileio.o
	$(CC) -c -o $(P)httpservice.o $(P)HttpService.cpp $(P)logger.o $(P)gameboard.o $(P)fileio.o

fileio.o: $(P)fileio.cpp $(P)fileio.hpp
	$(CC) -c -o $(P)fileio.o $(P)fileio.cpp 

guess.o: $(P)Guess.cpp $(P)Guess.h bcu.o bcd.o bcl.o bcr.o bcs.o
	$(CC) -c -o $(P)guess.o $(P)Guess.cpp $(P)bcu.o $(P)bcd.o $(P)bcl.o $(P)bcr.o $(P)bcs.o

bcu.o: $(P)BoardCommandUp.cpp $(P)BoardCommandUp.h logger.o gameboard.o
	$(CC) -c -o $(P)bcu.o $(P)BoardCommandUp.cpp $(P)logger.o $(P)gameboard.o 

bcd.o: $(P)BoardCommandDown.cpp $(P)BoardCommandDown.h logger.o gameboard.o
	$(CC) -c -o $(P)bcd.o $(P)BoardCommandDown.cpp $(P)logger.o $(P)gameboard.o 

bcl.o: $(P)BoardCommandLeft.cpp $(P)BoardCommandLeft.h logger.o gameboard.o
	$(CC) -c -o $(P)bcl.o $(P)BoardCommandLeft.cpp $(P)logger.o $(P)gameboard.o 

bcr.o: $(P)BoardCommandRight.cpp $(P)BoardCommandRight.h logger.o gameboard.o
	$(CC) -c -o $(P)bcr.o $(P)BoardCommandRight.cpp $(P)logger.o $(P)gameboard.o 

bcs.o: $(P)BoardCommandSet.cpp $(P)BoardCommandSet.h 
	$(CC) -c -o $(P)bcs.o $(P)BoardCommandSet.cpp $(P)logger.o $(P)gameboard.o

gameboard.o: $(P)GameBoard.cpp $(P)GameBoard.h logger.o
	$(CC) -c -o $(P)gameboard.o $(P)GameBoard.cpp $(P)logger.o

logger.o: $(P)Logger.cpp $(P)Logger.h
	$(CC) -c -o $(P)logger.o $(P)Logger.cpp

clean:
	rm -f *.o *~ \#* $(P)*.o $(P)*~ $(P)\#*
