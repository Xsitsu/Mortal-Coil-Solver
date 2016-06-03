#include "BoardCommandLeft.h"

BoardCommandLeft::BoardCommandLeft(GameBoard* board) : BoardCommand(board)
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandLeft constructed: " << int(this) << NEWLINE;
#endif
}

BoardCommandLeft::~BoardCommandLeft()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandLeft destroyed: " << int(this) << NEWLINE;
#endif
}

void BoardCommandLeft::Do()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Doing BoardCommandLeft at BoardPosition: "
		<< start_pos.x << "x " << start_pos.y << "y!" << NEWLINE;
#endif

	int cur_x = start_pos.x;

	bool is_going = true;
	while (is_going)
	{
		if (cur_x == 0)
		{
			is_going = false;
		}
		else if (board->ReadSquare(cur_x - 1, start_pos.y) != UP)
		{
			is_going = false;
		}
		else
		{
			cur_x--;
			board->PushSquare(cur_x, start_pos.y);
			board->SetPosition(cur_x, start_pos.y);
		}
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandLeft finished at: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE << NEWLINE;
#endif
}

void BoardCommandLeft::Undo()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Undoing BoardCommandLeft from BoardPosition: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#endif

	int cur_x = board->GetBoardPosition().x;
	for (int i = cur_x; i < start_pos.x; i++)
	{
		board->UnpushSquare(i, start_pos.y);
		board->SetPosition(i+1, start_pos.y);
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandLeft returned to: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#ifndef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << NEWLINE;
#endif
#endif
}