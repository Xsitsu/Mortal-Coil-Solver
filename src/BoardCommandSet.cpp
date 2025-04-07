#include "BoardCommandSet.h"

BoardCommandSet::BoardCommandSet(GameBoard* board) : BoardCommand(board)
{

}

BoardCommandSet::~BoardCommandSet()
{

}

void BoardCommandSet::Do()
{
	board->PushSquare(start_pos.x, start_pos.y);
}

void BoardCommandSet::Undo()
{
	board->UnpushSquare(start_pos.x, start_pos.y);
}