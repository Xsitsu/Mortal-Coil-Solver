#include "BoardCommandDown.h"

BoardCommandDown::BoardCommandDown(GameBoard* board) : BoardCommand(board)
{

}

BoardCommandDown::~BoardCommandDown()
{

}

void BoardCommandDown::Do()
{
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
}

void BoardCommandDown::Undo()
{
	int cur_y = board->GetBoardPosition().y;
	for (int i = cur_y; i > start_pos.y; i--)
	{
		board->UnpushSquare(start_pos.x, i);
		board->SetPosition(start_pos.x, i-1);
	}
}