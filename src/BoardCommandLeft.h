#ifndef BOARDCOMMANDLEFT_H
#define BOARDCOMMANDLEFT_H

#include "BoardCommand.h"

class BoardCommandLeft : public BoardCommand
{
private:

public:
	BoardCommandLeft(GameBoard* board);
	virtual ~BoardCommandLeft();

	virtual void Do();
	virtual void Undo();
	virtual char GetCommandID() { return 'L'; }
};

#endif