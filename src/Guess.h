#ifndef GUESS_H
#define GUESS_H

#include "board_command/BoardCommand.h"
#include "board_command/BoardCommandUp.h"
#include "board_command/BoardCommandDown.h"
#include "board_command/BoardCommandLeft.h"
#include "board_command/BoardCommandRight.h"
#include "board_command/BoardCommandSet.h"

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