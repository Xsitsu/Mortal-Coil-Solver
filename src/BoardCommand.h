#ifndef BOARDCOMMAND_H
#define BOARDCOMMAND_H

#include "GameBoard.h"
#include "Switches.h"

class BoardCommand
{
protected:
	GameBoard* board;
	BoardPosition start_pos;

public:
	BoardCommand(GameBoard* board)
	{
		this->board = board;
		this->start_pos = board->GetBoardPosition();
	}
	virtual ~BoardCommand() {}

	virtual void Do() = 0;
	virtual void Undo() = 0;
	virtual char GetCommandID() = 0;

};

#endif