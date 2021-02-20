#define VERSION ("0.0.1b")
#define	BOARD_SIZE (15)
#define X first
#define Y second

#include "Gomoku.h"
#include "GameManager.h"

GameManager::GameManager(void) :bGameOver(false), bRefreshNeeded(true), cursor({ 0,0 }), turn(eTurns::BLACK)
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			board[i][j] = eStones::NONE;
		}
	}
}

eTitleActions GameManager::ShowTitle(void)
{
	system("cls");

	int title_cursor = 0;

	while (true)
	{
		std::cout << "v" << VERSION << "\n\n";
		std::cout << "  .oooooo.                                          oooo                    \n";
		std::cout << " d8P'  `Y8b                                         `888                    \n";
		std::cout << "888            .ooooo.  ooo. .oo.  .oo.    .ooooo.   888  oooo  oooo  oooo  \n";
		std::cout << "888           d88' `88b `888P\"Y88bP\"Y88b  d88' `88b  888 .8P'   `888  `888  \n";
		std::cout << "888     ooooo 888   888  888   888   888  888   888  888888.     888   888  \n";
		std::cout << "`88.    .88'  888   888  888   888   888  888   888  888 `88b.   888   888  \n";
		std::cout << " `Y8bood8P'   `Y8bod8P\' o888o o888o o888o `Y8bod8P\' o888o o888o  `V88V\"V8P\' \n";

		std::cout << "\n※상하 방향키로 이동, Enter키로 선택\n\n";

		for (int i = 0; i < 3; i++)
		{
			if (title_cursor == i)
			{
				std::cout << ">>";
			}
			else
			{
				std::cout << "  ";
			}

			switch (i)
			{
			case 0:
				std::cout << "  게 임 시 작  ";
				break;
			case 1:
				std::cout << "  게임 가이드  ";
				break;
			case 2:
				std::cout << "  게 임 종 료  ";
				break;
			default:
				assert(false);
				break;
			}

			if (title_cursor == i)
			{
				std::cout << "<<";
			}
			std::cout << "\n";
		}

		eInputKeys key = GetInputKey();
		switch (key)
		{
		case eInputKeys::ARROW_UP:
			title_cursor--;
			if (title_cursor < 0) title_cursor = 0;
			break;
		case eInputKeys::ARROW_DOWN:
			title_cursor++;
			if (title_cursor > 2) title_cursor = 2;
			break;
		case eInputKeys::ENTER:
			if (title_cursor == 0) return eTitleActions::START;
			else if (title_cursor == 1) return eTitleActions::HELP;
			else return eTitleActions::EXIT;
			break;
		default:
			break;
		}
		system("cls");
	}
}

void GameManager::ShowHelp(void)
{
	system("cls");

}

void GameManager::StartGame(void)
{
	DrawBoard();
	while (bGameOver == false)
	{
		switch (turn)
		{
		case eTurns::BLACK:
			std::cout << "검은돌";
			break;
		case eTurns::WHITE:
			std::cout << "흰돌";
			break;
		default:
			assert(0);
			break;
		}
		std::cout << "의 차례입니다.\n";

		bool try_place = false;
		eInputKeys key = GetInputKey();
		ePlaceErrorCodes success = ePlaceErrorCodes::SUCCESS;
		switch (key)
		{
		case eInputKeys::ARROW_UP:
		case eInputKeys::ARROW_DOWN:
		case eInputKeys::ARROW_LEFT:
		case eInputKeys::ARROW_RIGHT:
			SetBoardCursor(key);
			break;
		case eInputKeys::SPACE:
			try_place = true;
			success = PlaceStone(cursor);
			break;
		}

		if (try_place == true)
		{
			switch (success)
			{
			case ePlaceErrorCodes::SUCCESS:
				break;
			case ePlaceErrorCodes::FAIL_BROKE_CUR_RULE:
				std::cout << "룰에 의해 착수가 불가능한 곳 입니다.";
				break;
			case ePlaceErrorCodes::FAIL_ALREADY_EXISTS:
				switch (board[cursor.X][cursor.Y])
				{
				case eStones::BLACK:
					std::cout << "이미 흑돌이 놓여져 있습니다.";
					break;
				case eStones::WHITE:
					std::cout << "이미 백돌이 놓여져 있습니다.";
					break;
				default:
					break;
				}
				break;
			default:
				assert(0);
				break;
			}
		}
	}
}

void GameManager::SetBoardCursor(eInputKeys key)
{
	switch (key)
	{
	case eInputKeys::ARROW_UP:
		cursor.X--;
		break;
	case eInputKeys::ARROW_DOWN:
		cursor.X++;
		break;
	case eInputKeys::ARROW_LEFT:
		cursor.Y--;
		break;
	case eInputKeys::ARROW_RIGHT:
		cursor.Y++;
		break;
	}

	bRefreshNeeded = true;
	if (cursor.X >= BOARD_SIZE)
	{
		cursor.X = BOARD_SIZE - 1;
		bRefreshNeeded = false;
	}
	else if (cursor.X < 0)
	{
		cursor.X = 0;
		bRefreshNeeded = false;
	}

	if (cursor.Y >= BOARD_SIZE)
	{
		cursor.Y = BOARD_SIZE - 1;
		bRefreshNeeded = false;
	}
	else if (cursor.Y < 0)
	{
		cursor.Y = 0;
		bRefreshNeeded = false;
	}

	if (bRefreshNeeded == true)
	{
		DrawBoard();
	}
}

ePlaceErrorCodes GameManager::PlaceStone(std::pair<int, int>& cur)
{
	switch (board[cur.X][cur.Y])
	{

	case eStones::NOT_PLACEABLE:
		return ePlaceErrorCodes::FAIL_BROKE_CUR_RULE;
	case eStones::BLACK:
	case eStones::WHITE:
		return ePlaceErrorCodes::FAIL_ALREADY_EXISTS;
	case eStones::NONE:
		break;
	default:
		assert(0);
		break;
	}

	switch (turn)
	{
	case eTurns::BLACK:
		board[cur.X][cur.Y] = eStones::BLACK;
		turn = eTurns::WHITE;
		break;
	case eTurns::WHITE:
		board[cur.X][cur.Y] = eStones::WHITE;
		turn = eTurns::BLACK;
		break;
	default:
		assert(0);
		break;
	}

	return ePlaceErrorCodes::SUCCESS;
}

bool GameManager::CheckGameOver()
{
	return false;
}

void GameManager::DrawBoard()
{
	system("cls");
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (cursor == std::make_pair(i, j))	//커서 노출이 최우선
			{
				std::cout << "⊙";
				continue;
			}

			if (board[i][j] == eStones::BLACK)
			{
				std::cout << "○";
				continue;
			}
			else if (board[i][j] == eStones::WHITE)
			{
				std::cout << "●";
				continue;
			}
			else if (board[i][j] == eStones::NOT_PLACEABLE)
			{
				std::cout << "ⓧ";
				continue;
			}

			if (i == 0 && j == 0)
			{
				std::cout << "┌ ";
			}
			else if (i == 0 && j == 14)
			{
				std::cout << "┐ ";
			}
			else if (i == 14 && j == 0)
			{
				std::cout << "└ ";
			}
			else if (i == 14 && j == 14)
			{
				std::cout << "┘ ";
			}
			else if (i == 0)
			{
				std::cout << "┬ ";
			}
			else if (i == 14)
			{
				std::cout << "┴ ";
			}
			else if (j == 0)
			{
				std::cout << "├ ";
			}
			else if (j == 14)
			{
				std::cout << "┤ ";
			}
			else
			{
				std::cout << "┼ ";
			}
		}
		std::cout << "\n";
	}
}

eInputKeys GameManager::GetInputKey()
{
	while (true)
	{
		int input = 0;
		if (_kbhit())
		{
			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 72:
					return eInputKeys::ARROW_UP;
				case 80:
					return eInputKeys::ARROW_DOWN;
				case 75:
					return eInputKeys::ARROW_LEFT;
				case 77:
					return eInputKeys::ARROW_RIGHT;
				default:
					assert(false);
					break;
				}
			}

			else if (input == 32)
			{
				return eInputKeys::SPACE;
			}
			else if (input == '\r')
			{
				return eInputKeys::ENTER;
			}
		}
	}
}
