#include "Guess.h"

#include <iostream>

Guess::Guess(GameBoard* board)
{
	this->board = board;

	for (int i = 0; i < CT_EOF; i++)
		no_good[i] = false;

	command = nullptr;
}

Guess::~Guess()
{
	if (command != nullptr)
	{
		delete command;
	}
}

void Guess::DoGuess()
{
	if (!no_good[CT_UP])
	{
		command = new BoardCommandUp(board);
		no_good[CT_UP] = true;
	}
	else if (!no_good[CT_DOWN])
	{
		command = new BoardCommandDown(board);
		no_good[CT_DOWN] = true;
	}
	else if (!no_good[CT_LEFT])
	{
		command = new BoardCommandLeft(board);
		no_good[CT_LEFT] = true;
	}
	else if (!no_good[CT_RIGHT])
	{
		command = new BoardCommandRight(board);
		no_good[CT_RIGHT] = true;
	}
	else
	{
		command = new BoardCommandSet(board);
	}

	command->Do();
}

void Guess::UndoGuess()
{
	if (command != nullptr)
	{
		command->Undo();
		delete command;
		command = nullptr;
	}
}

bool Guess::CanGuess()
{
	bool ret = false;
	for (int i = 0; i < CT_EOF; i++)
	{
		ret = ret || !no_good[i];
	}
	return ret;
}

void Guess::SetNoGood(COMMAND_TYPES ct)
{
	if (ct >= CT_UP && ct < CT_EOF)
		no_good[ct] = true;
}