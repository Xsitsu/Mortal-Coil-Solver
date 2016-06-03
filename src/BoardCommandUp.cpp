#include "BoardCommandUp.h"

BoardCommandUp::BoardCommandUp(GameBoard* board) : BoardCommand(board)
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandUp constructed: " << int(this) << NEWLINE;
#endif
}

BoardCommandUp::~BoardCommandUp()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandUp destroyed: " << int(this) << NEWLINE;
#endif
}

void BoardCommandUp::Do()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Doing BoardCommandUp at BoardPosition: " 
		<< start_pos.x << "x " << start_pos.y << "y!" << NEWLINE;
#endif

	int cur_y = start_pos.y;

	bool is_going = true;
	while (is_going)
	{
		if (cur_y == 0)
		{
			is_going = false;
		}
		else if (board->ReadSquare(start_pos.x, cur_y - 1) != UP)
		{
			is_going = false;
		}
		else
		{
			cur_y--;
			board->PushSquare(start_pos.x, cur_y);
			board->SetPosition(start_pos.x, cur_y);
		}
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandUp finished at: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE << NEWLINE;
#endif
}

void BoardCommandUp::Undo()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Undoing BoardCommandUp from BoardPosition: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#endif

	int cur_y = board->GetBoardPosition().y;
	for (int i = cur_y; i < start_pos.y; i++)
	{
		board->UnpushSquare(start_pos.x, i);
		board->SetPosition(start_pos.x, i+1);
	}

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandUp returned to: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#ifndef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << NEWLINE;
#endif
#endif
}