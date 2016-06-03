#ifndef BOARDCOMMANDLEFT_H
#define BOARDCOMMANDLEFT_H

#include "BoardCommand.h"

class BoardCommandLeft : public BoardCommand
{
private:

public:
	BoardCommandLeft(GameBoard* board);
	~BoardCommandLeft();

	void Do();
	void Undo();
	char GetCommandID() { return 'L'; }
};

#endif