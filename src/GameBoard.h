#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include "Exceptions.h"
#include "Switches.h"
#include "Logger.h"

enum TILE_TYPES {UP, DOWN, BLOCK};

struct PuzzleData
{
	int number;
	int x;
	int y;
	std::string data;
};

struct Movements
{
	bool up;
	bool down;
	bool left;
	bool right;
};

struct BoardPosition
{
	int x;
	int y;
};

class GameBoard
{
private:
	TILE_TYPES* board;
	int board_width;
	int board_height;
	bool is_loaded;
	int board_number;

	BoardPosition position;

public:
	GameBoard();
	~GameBoard();

	int GetBoardNumber() { return board_number; }
	int GetHeight() { return board_height; }
	int GetWidth() { return board_width; }
	BoardPosition GetBoardPosition() { return position; }

	bool IsSolved();
	void CreateBoard(PuzzleData data, int start_x = 0, int start_y = 0);
	void Clear();

	TILE_TYPES ReadSquare(int x, int y);
	void PushSquare(int x, int y);
	void UnpushSquare(int x, int y);

	void SetPosition(int x, int y);
	void SetPosition(BoardPosition position);

	Movements GetMovements();

	bool IsUnsolvable();

};

#endif
