#include "BoardCommandDown.h"

BoardCommandDown::BoardCommandDown(GameBoard* board) : BoardCommand(board)
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandDown constructed: " << int(this) << NEWLINE;
#endif
}

BoardCommandDown::~BoardCommandDown()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandDown destroyed: " << int(this) << NEWLINE;
#endif
}

void BoardCommandDown::Do()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Doing BoardCommandDown at BoardPosition: "
		<< start_pos.x << "x " << start_pos.y << "y!" << NEWLINE;
#endif

	int cur_y = start_pos.y;
	int max_y = board->GetHeight() - 1;

	bool is_going = true;
	while (is_going)
	{
		if (cur_y == max_y)
		{
			is_going = false;
		}
		else if (board->ReadSquare(start_pos.x, cur_y + 1) != UP)
		{
			is_going = false;
		}
		else
		{
			cur_y++;
			board->PushSquare(start_pos.x, cur_y);
			board->SetPosition(start_pos.x, cur_y);
		}
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandDown finished at: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE << NEWLINE;
#endif
}

void BoardCommandDown::Undo()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Undoing BoardCommandDown from BoardPosition: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#endif

	int cur_y = board->GetBoardPosition().y;
	for (int i = cur_y; i > start_pos.y; i--)
	{
		board->UnpushSquare(start_pos.x, i);
		board->SetPosition(start_pos.x, i-1);
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandDown returned to: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#ifndef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << NEWLINE;
#endif
#endif
}