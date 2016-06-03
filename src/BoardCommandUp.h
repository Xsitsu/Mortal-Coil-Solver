#ifndef BOARDCOMMANDUP_H
#define BOARDCOMMANDUP_H

#include "BoardCommand.h"

class BoardCommandUp : public BoardCommand
{
private:

public:
	BoardCommandUp(GameBoard* board);
	~BoardCommandUp();

	void Do();
	void Undo();
	char GetCommandID() { return 'U'; }
};

#endif