#ifndef BOARDCOMMANDRIGHT_H
#define BOARDCOMMANDRIGHT_H

#include "BoardCommand.h"

class BoardCommandRight : public BoardCommand
{
private:

public:
	BoardCommandRight(GameBoard* board);
	~BoardCommandRight();

	void Do();
	void Undo();
	char GetCommandID() { return 'R'; }
};

#endif