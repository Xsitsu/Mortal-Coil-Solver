#ifndef BOARDCOMMAND_H
#define BOARDCOMMAND_H

#include "GameBoard.h"
#include "Switches.h"
#include "Logger.h"

class BoardCommand
{
protected:
	GameBoard* board;
	BoardPosition start_pos;

public:
	BoardCommand(GameBoard* board)
	{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
		Logger::Instance() << "BoardCommand constructed: " << int(this) << NEWLINE;
#endif
		this->board = board;
		this->start_pos = board->GetBoardPosition();
	}
	virtual ~BoardCommand()
	{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
		Logger::Instance() << "BoardCommand destroyed: " << int(this) << NEWLINE;
#endif
	}

	virtual void Do() = 0;
	virtual void Undo() = 0;
	virtual char GetCommandID() = 0;

};

#endif