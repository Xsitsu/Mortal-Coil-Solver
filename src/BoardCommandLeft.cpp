#include "BoardCommandLeft.h"

BoardCommandLeft::BoardCommandLeft(GameBoard* board) : BoardCommand(board)
{

}

BoardCommandLeft::~BoardCommandLeft()
{

}

void BoardCommandLeft::Do()
{
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
}

void BoardCommandLeft::Undo()
{
	int cur_x = board->GetBoardPosition().x;
	for (int i = cur_x; i < start_pos.x; i++)
	{
		board->UnpushSquare(i, start_pos.y);
		board->SetPosition(i+1, start_pos.y);
	}
}