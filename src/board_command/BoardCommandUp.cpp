#include "BoardCommandUp.h"

BoardCommandUp::BoardCommandUp(GameBoard* board) : BoardCommand(board)
{

}

BoardCommandUp::~BoardCommandUp()
{

}

void BoardCommandUp::Do()
{
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
}

void BoardCommandUp::Undo()
{
	int cur_y = board->GetBoardPosition().y;
	for (int i = cur_y; i < start_pos.y; i++)
	{
		board->UnpushSquare(start_pos.x, i);
		board->SetPosition(start_pos.x, i+1);
	}
}