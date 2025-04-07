#include "Controller.h"

#include <iostream>
#include <exception>
#include <string>
#include <format>
#include <regex>



std::string ExtractVariable(std::string puzzle_data, std::string var_name)
{
    std::string base = std::format("var {} = ", var_name);
    std::regex pattern(std::format("{}.*?;", base));
    std::smatch matches;
    std::regex_search(puzzle_data, matches, pattern);

    std::string result;
    for (auto match : matches)
    {
        result += match;
    }

    int start_pos = base.length();
    int new_len = result.length() - start_pos - 1;

    return result.substr(base.length(), new_len);
}

int DecodeLevel(std::string puzzle_data)
{
	return std::stoi(ExtractVariable(puzzle_data, "curLevel"));
}

int DecodeWidth(std::string puzzle_data)
{
    return std::stoi(ExtractVariable(puzzle_data, "width"));
}

int DecodeHeight(std::string puzzle_data)
{
    return std::stoi(ExtractVariable(puzzle_data, "height"));
}

std::string DecodeBoardData(std::string puzzle_data)
{
	std::string var = ExtractVariable(puzzle_data, "boardStr");
	return var.substr(1, var.length() - 2);
}





Controller::Controller(HttpHandler *handler, int start_level, int start_x, int start_y)
{
	state = CSTATE_INIT;
	game_board = new GameBoard();
	http = handler;

	this->current_level = start_level;
    this->start_x = start_x;
    this->start_y = start_y;
}

Controller::~Controller()
{
	delete game_board;
	// Don't delete HttpHandler.
	// We create it on the stack and just pass the pointer in.

	if (fin.is_open())
		fin.close();
}

void Controller::Step()
{
	try
	{
		this->DoStep();
	}
	catch (EXCEPTION ex)
	{
		switch (ex)
		{
		case EX_BOARD_ALREADY_LOADED:
			break;
		case EX_BOARD_NOT_LOADED:
			break;
		case EX_BAD_BOARD_LOAD_ATTEMPT:
			break;
		case EX_FAIL_FILE_OPEN:
			break;
		case EX_OUT_OF_BOARD_RANGE:
			break;
		case EX_ILLEGAL_BOARD_OPERATION:
			break;
		default:
			std::cout << "Error: Unknown exception: " << ex << "!" << std::endl;
			break;
		}
	}
}

void Controller::DoStep()
{
	switch (state)
	{
	case CSTATE_INIT:
	{
		state = CSTATE_LOAD;
		break;
	}
	case CSTATE_LOAD:
	{
		try
		{
			std::string puzzle_data = this->overwrite_data;
			if (puzzle_data == "")
				puzzle_data = http->GetPuzzleData(this->current_level);
			else
			{
				this->current_level = DecodeLevel(puzzle_data);
			}

			PuzzleData data;
			data.number = current_level;
			data.x = DecodeWidth(puzzle_data);
			data.y = DecodeHeight(puzzle_data);
			data.data = DecodeBoardData(puzzle_data);

			game_board->CreateBoard(data, start_x, start_y);
		}
		catch (std::exception& ex)
		{
			std::cout << "Exception: " << ex.what() << std::endl;
			state = CSTATE_DONE;
			throw EX_HTTP_GET_FAIL;
		}

		state = CSTATE_SOLVING;
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
						// Every space has been attempted, and yet no solution has been found...
						// Should never happen
						state = CSTATE_CLEAR;
					}
				}
				game_board->SetPosition(pos);
			} while (game_board->ReadSquare(pos.x, pos.y) == BLOCK);
			
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
		if (this->http != nullptr)
			http->PostPuzzleSolution(pos.x, pos.y, str);
		else
			std::cout << pos.x << "_" << pos.y << "_" << str << std::endl;

		state = CSTATE_CLEAR;
		break;
	}
	case CSTATE_CLEAR:
	{
		game_board->Clear();
        state = CSTATE_DONE;
		break;
	}
	default:
	{
		state = CSTATE_INIT;
		break;
	}
	}
}

void Controller::OverwritePuzzleData(std::string puzzle_data)
{
	this->overwrite_data = puzzle_data;
}