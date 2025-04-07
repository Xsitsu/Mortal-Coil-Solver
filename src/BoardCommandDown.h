#ifndef BOARDCOMMANDDOWN_H
#define BOARDCOMMANDDOWN_H

#include "BoardCommand.h"

class BoardCommandDown : public BoardCommand
{
private:

public:
	BoardCommandDown(GameBoard* board);
	virtual ~BoardCommandDown();

	virtual void Do();
	virtual void Undo();
	virtual char GetCommandID() { return 'D'; }
};

#endif