#ifndef BOARDCOMMANDSET_H
#define BOARDCOMMANDSET_H

#include "BoardCommand.h"

class BoardCommandSet : public BoardCommand
{
private:

public:
	BoardCommandSet(GameBoard* board);
	~BoardCommandSet();

	void Do();
	void Undo();
	char GetCommandID() { return 'S'; }
};

#endif