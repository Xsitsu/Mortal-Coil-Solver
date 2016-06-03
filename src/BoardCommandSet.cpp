#include "BoardCommandSet.h"

BoardCommandSet::BoardCommandSet(GameBoard* board) : BoardCommand(board)
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandSet constructed: " << int(this) << NEWLINE;
#endif
}

BoardCommandSet::~BoardCommandSet()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "BoardCommandSet destroyed: " << int(this) << NEWLINE;
#endif
}

void BoardCommandSet::Do()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Doing BoardCommandSet at BoardPosition: "
		<< start_pos.x << "x " << start_pos.y << "y!" << NEWLINE; 
#endif

	board->PushSquare(start_pos.x, start_pos.y);

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandSet finished at: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE << NEWLINE;
#endif
}

void BoardCommandSet::Undo()
{
#ifdef LOG_MOVEMENTS
	Logger::Instance() << "Undoing BoardCommandSet from BoardPosition: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#endif

	board->UnpushSquare(start_pos.x, start_pos.y);

#ifdef LOG_MOVEMENTS
	Logger::Instance() << "BoardCommandSet returned to: "
		<< board->GetBoardPosition().x << "x " << board->GetBoardPosition().y << "y!" << NEWLINE;
#ifndef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << NEWLINE;
#endif
#endif
}