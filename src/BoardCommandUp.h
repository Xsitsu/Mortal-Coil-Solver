#ifndef BOARDCOMMANDUP_H
#define BOARDCOMMANDUP_H

#include "BoardCommand.h"

class BoardCommandUp : public BoardCommand
{
private:

public:
	BoardCommandUp(GameBoard* board);
	virtual ~BoardCommandUp();

	virtual void Do();
	virtual void Undo();
	virtual char GetCommandID() { return 'U'; }
};

#endif