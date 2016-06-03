#include "Controller.h"

#include <iostream>
#include <exception>
#include <string>

Controller::Controller(int x, int y)
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "Controller constructed: " << int(this) << NEWLINE;
#endif
	state = CSTATE_INIT;
	game_board = new GameBoard();
	http = new HttpService;

    start_x = x;
    start_y = y;
}

Controller::~Controller()
{
#ifdef DEBUG_OUTPUT_CONSTRUCTORS
	Logger::Instance() << "Controller destroyed: " << int(this) << NEWLINE;
#endif

	delete game_board;
	delete http;

	if (fin.is_open())
		fin.close();
}

void Controller::Step()
{
	switch (state)
	{
	case CSTATE_INIT:
	{
		Logger::Instance().BreakLine();
		Logger::Instance() << "Mortal Coil Solver Starting!" << NEWLINE;

		state = CSTATE_LOAD;
		break;
	}
	case CSTATE_LOAD:
	{
		Logger::Instance().BreakLine();
		Logger::Instance() << "Requesting board data from website!" << NEWLINE;
		try
		{
			PuzzleData data = http->GetPuzzle();
			game_board->CreateBoard(data, start_x, start_y);
			Logger::Instance() << "Loaded Puzzle #" << data.number << NEWLINE;
		}
		catch (std::exception& ex)
		{
			Logger::Instance() << "Exception: " << ex.what() << NEWLINE;
			state = CSTATE_DONE;
			throw EX_HTTP_GET_FAIL;
		}

		state = CSTATE_SOLVING;

		Logger::Instance().BreakLine();
		Logger::Instance() << "Starting solving algorithm!" << NEWLINE;

		break;
	}
	case CSTATE_SOLVING:
	{
		if (guess_stack.empty())
		{
			BoardPosition pos = game_board->GetBoardPosition();
			int max_x = game_board->GetWidth();
			int max_y = game_board->GetHeight();

			do
			{
				pos.x++;
				if (pos.x >= max_x)
				{
					pos.x = 0;
					pos.y++;

					if (pos.y >= max_y)
					{
						Logger::Instance() << "This should never happen! Apparently every single board space has been attempted!" << NEWLINE;
						state = CSTATE_CLEAR;
					}
				}
				game_board->SetPosition(pos);
			} while (game_board->ReadSquare(pos.x, pos.y) == BLOCK);
			
			Logger::Instance().BreakLine();
			Logger::Instance() << "Starting new attempt from position: " << pos.x << "x " << pos.y << "y!" << NEWLINE;
			Logger::Instance() << "Max board size: " << game_board->GetWidth() - 1 << "x " << game_board->GetHeight() - 1 << "y!" << NEWLINE << NEWLINE;

			Guess* guess = new Guess(game_board);
			guess->SetNoGood(CT_UP);
			guess->SetNoGood(CT_DOWN);
			guess->SetNoGood(CT_LEFT);
			guess->SetNoGood(CT_RIGHT);
			guess->DoGuess();

			guess_stack.push(guess);

		}
		else if (!game_board->IsSolved())
		{
			Movements movements = game_board->GetMovements();

			Guess* guess = new Guess(game_board);

			if (!movements.up)
				guess->SetNoGood(CT_UP);

			if (!movements.down)
				guess->SetNoGood(CT_DOWN);

			if (!movements.left)
				guess->SetNoGood(CT_LEFT);

			if (!movements.right)
				guess->SetNoGood(CT_RIGHT);
			

			if (guess->CanGuess() && !game_board->IsUnsolvable())
			{
				guess->DoGuess();
				guess_stack.push(guess);
			}
			else
			{
				delete guess;

				bool good_redo = false;
				while (!good_redo && !guess_stack.empty())
				{
					guess = guess_stack.top();
					guess->UndoGuess();

					if (guess->CanGuess())
					{
						guess->DoGuess();
						good_redo = true;
					}
					else
					{
						guess_stack.pop();
						delete guess;
					}
				}
				
			}

		}
		else
		{
			state = CSTATE_SOLVED;
		}

		break;
	}
	case CSTATE_SOLVED:
	{
		Logger::Instance().BreakLine();
		Logger::Instance() << "Board has been solved!" << NEWLINE << NEWLINE;

		std::stack<char> char_stack;

		Guess* ptr;

		while (!guess_stack.empty())
		{
			char_stack.push(guess_stack.top()->GetCommandType());
			ptr = guess_stack.top();
			guess_stack.pop();
			ptr->UndoGuess();
			delete ptr;
		}

		char_stack.pop(); //Remove first set character

		std::string str = "";
		while (!char_stack.empty())
		{
			str += char_stack.top();
			char_stack.pop();
		}

		BoardPosition pos = game_board->GetBoardPosition();
		Logger::Instance() << "Start Position: " << pos.x << "x " << pos.y << "y" << NEWLINE;
		Logger::Instance() << "Solution: " << str << NEWLINE << NEWLINE;

		Logger::Instance() << "Output String: " << pos.x << "_" << pos.y << "_" << str << NEWLINE;

		http->PostSolution(pos.x, pos.y, str);

		state = CSTATE_CLEAR;
		break;
	}
	case CSTATE_CLEAR:
	{
		Logger::Instance().BreakLine();
		Logger::Instance() << "The board will now be cleared!" << NEWLINE;
		Logger::Instance() << "Current stack size: " << guess_stack.size() << NEWLINE;

		game_board->Clear();

        state = CSTATE_DONE;

        Logger::Instance().BreakLine();
        Logger::Instance() << "Solver program will now terminate!" << NEWLINE << NEWLINE;

		break;
	}
	default:
	{
		state = CSTATE_INIT;
		break;
	}
	}
}
