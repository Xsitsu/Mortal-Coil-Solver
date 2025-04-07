#ifndef BOARDCOMMANDRIGHT_H
#define BOARDCOMMANDRIGHT_H

#include "BoardCommand.h"

class BoardCommandRight : public BoardCommand
{
private:

public:
	BoardCommandRight(GameBoard* board);
	virtual ~BoardCommandRight();

	virtual void Do();
	virtual void Undo();
	virtual char GetCommandID() { return 'R'; }
};

#endif