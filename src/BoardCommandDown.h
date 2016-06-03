#ifndef BOARDCOMMANDDOWN_H
#define BOARDCOMMANDDOWN_H

#include "BoardCommand.h"

class BoardCommandDown : public BoardCommand
{
private:

public:
	BoardCommandDown(GameBoard* board);
	~BoardCommandDown();

	void Do();
	void Undo();
	char GetCommandID() { return 'D'; }
};

#endif