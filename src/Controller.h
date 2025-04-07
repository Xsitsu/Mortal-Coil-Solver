#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <fstream>
#include <stack>

#include "GameBoard.h"
#include "Switches.h"
#include "Guess.h"

#include "http/http_handler.hpp"

enum CSTATE {CSTATE_INIT, CSTATE_LOAD, CSTATE_SOLVING, CSTATE_SOLVED, CSTATE_CLEAR, CSTATE_DONE};

class Controller
{
private:
	CSTATE state;
	GameBoard* game_board;
	HttpHandler* http;
	std::stack<Guess*> guess_stack;

	std::ifstream fin;

	int current_level;
    int start_x;
    int start_y;

public:
	Controller(HttpHandler *handler, int start_level, int start_x, int start_y);
	~Controller();

	CSTATE GetState() { return state; }
	void Step();

private:
	void DoStep();
};

#endif
