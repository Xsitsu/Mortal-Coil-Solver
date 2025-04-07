#ifndef BOARDCOMMANDSET_H
#define BOARDCOMMANDSET_H

#include "BoardCommand.h"

class BoardCommandSet : public BoardCommand
{
private:

public:
	BoardCommandSet(GameBoard* board);
	virtual ~BoardCommandSet();

	virtual void Do();
	virtual void Undo();
	virtual char GetCommandID() { return 'S'; }
};

#endif