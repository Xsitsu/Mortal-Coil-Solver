#include "GameBoard.h"

#include <iostream>

GameBoard::GameBoard()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "Gameboard constructed: " << int(this) << NEWLINE;
#endif

	board = nullptr;
	board_width = 0;
	board_height = 0;
	is_loaded = false;
	board_number = 0;

	position.x = 0;
	position.y = 0;
}

GameBoard::~GameBoard()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "Gameboard destroyed: " << int(this) << NEWLINE;
#endif
}

bool GameBoard::IsSolved()
{
	bool ret = true;
	int c = 0;
	int total = board_width * board_height;
	while (ret == true && c < total)
	{
		ret = (board[c] == UP) ? false : true;
		c++;
	}

	return ret;
}

void GameBoard::CreateBoard(PuzzleData data, int start_x, int start_y)
{
	if (is_loaded) throw EX_BOARD_ALREADY_LOADED;

	board_number = data.number;
	board_width = data.x;
	board_height = data.y;
	int len = data.data.length();

	if (board_width * board_height != len) throw EX_BAD_BOARD_LOAD_ATTEMPT;

	board = new TILE_TYPES[board_width * board_height];

	for (int i = 0; i < len; i++)
		board[i] = (data.data[i] == 'X') ? BLOCK : UP;

	is_loaded = true;

	position.x = start_x - 1;
	position.y = start_y;
}

void GameBoard::Clear()
{
	if (!is_loaded) throw EX_BOARD_NOT_LOADED;

	delete[] board;
	is_loaded = false;
}


TILE_TYPES GameBoard::ReadSquare(int x, int y)
{
	if (x >= board_width || y >= board_height || x < 0 || y < 0)
		throw EX_OUT_OF_BOARD_RANGE;

	return board[x + (y * board_width)];
}

void GameBoard::PushSquare(int x, int y)
{
	if (x >= board_width || y >= board_height || x < 0 || y < 0)
		throw EX_OUT_OF_BOARD_RANGE;

	if (board[x + (y * board_width)] != UP)
		throw EX_ILLEGAL_BOARD_OPERATION;

	board[x + (y * board_width)] = DOWN;
}

void GameBoard::UnpushSquare(int x, int y)
{
	if (x >= board_width || y >= board_height)
		throw EX_OUT_OF_BOARD_RANGE;

	if (board[x + (y * board_width)] != DOWN)
		throw EX_ILLEGAL_BOARD_OPERATION;

	board[x + (y * board_width)] = UP;
}

void GameBoard::SetPosition(int x, int y)
{
	if (x >= board_width || y >= board_height || x < 0 || y < 0)
		throw EX_OUT_OF_BOARD_RANGE;

	position.x = x;
	position.y = y;
}

void GameBoard::SetPosition(BoardPosition position)
{
	GameBoard::SetPosition(position.x, position.y);
}

Movements GameBoard::GetMovements()
{
	Movements movements;
	movements.up = false;
	movements.down = false;
	movements.left = false;
	movements.right = false;

	if (position.x > 0)
	{
		if (ReadSquare(position.x - 1, position.y) == UP)
		{
			movements.left = true;
		}
	}

	if (position.x < board_width - 1)
	{
		if (ReadSquare(position.x + 1, position.y) == UP)
		{
			movements.right = true;
		}
	}

	if (position.y > 0)
	{
		if (ReadSquare(position.x, position.y - 1) == UP)
		{
			movements.up = true;
		}
	}

	if (position.y < board_height - 1)
	{
		if (ReadSquare(position.x, position.y + 1) == UP)
		{
			movements.down = true;
		}
	}

	return movements;
}

bool GameBoard::IsUnsolvable()
{
	bool unsolvable = false;
	bool running = true;

	int x = 0;
	int y = 0;
	int number_endpoints = 0;	// number of squares with only one adjacent square
	while (running)
	{
		if (this->ReadSquare(x, y) == UP)
		{
			int num_connections = 0;

			// Check if connects left
			if (x > 0)
			{
				TILE_TYPES check = this->ReadSquare(x - 1, y);
				if (check == UP || (x - 1 == position.x && y == position.y))
				{
					num_connections++;
				}
			}

			// Check if connects right
			if (x < board_width - 1)
			{
				TILE_TYPES check = this->ReadSquare(x + 1, y);
				if (check == UP || (x + 1 == position.x && y == position.y))
				{
					num_connections++;
				}
			}

			// Check if connects up
			if (y > 0)
			{
				TILE_TYPES check = this->ReadSquare(x, y - 1);
				if (check == UP || (x == position.x && y - 1 == position.y))
				{
					num_connections++;
				}
			}

			// Check if connects down
			if (y < board_height - 1)
			{
				TILE_TYPES check = this->ReadSquare(x, y + 1);
				if (check == UP || (x == position.x && y + 1 == position.y))
				{
					num_connections++;
				}
			}

			if (num_connections == 0)
			{
				running = false;
				unsolvable = true;
				continue;
			}
			else if (num_connections == 1)
			{
				number_endpoints++;
				if (number_endpoints > 1)
				{
					running = false;
					unsolvable = true;
					continue;
				}
			}
		}

		x++;
		if (x >= board_width)
		{
			x = 0;
			y++;
			if (y >= board_height)
			{
				running = false;
			}
		}
	}

	return unsolvable;
}
