#ifndef GUESS_H
#define GUESS_H

#include "BoardCommand.h"
#include "BoardCommandUp.h"
#include "BoardCommandDown.h"
#include "BoardCommandLeft.h"
#include "BoardCommandRight.h"
#include "BoardCommandSet.h"

enum COMMAND_TYPES { CT_UP, CT_DOWN, CT_LEFT, CT_RIGHT, CT_EOF };

class Guess
{
private:
	GameBoard* board;

	bool no_good[CT_EOF];
	BoardCommand* command;

public:
	Guess(GameBoard* board);
	~Guess();

	char GetCommandType() { return command->GetCommandID(); }

	void DoGuess();
	void UndoGuess();
	bool CanGuess();

	void SetNoGood(COMMAND_TYPES ct);
};

#endif