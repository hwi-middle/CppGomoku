#define VERSION ("0.0.1b")

#include "Gomoku.h"
#include "GameManager.h"

GameManager::GameManager(void)
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

	int cursor = 0;

	while (true)
	{
		printf("┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼ ┼\n");
		std::cout << "┌ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ┬ ○┬ ┐\n";
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
			if (cursor == i)
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

			if (cursor == i)
			{
				std::cout << "<<";
			}
			std::cout << "\n";
		}

		eInputKeys key = GetInputKey(false, 0.0f);
		switch (key)
		{
		case eInputKeys::ARROW_UP:
			cursor--;
			if (cursor < 0) cursor = 0;
			break;
		case eInputKeys::ARROW_DOWN:
			cursor++;
			if (cursor > 2) cursor = 2;
			break;
		case eInputKeys::ENTER:
			if (cursor == 0) return eTitleActions::START;
			else if (cursor == 1) return eTitleActions::HELP;
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
	system("pause");
	system("cls");
}

void GameManager::DrawBoard()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board[i][j] == eStones::BLACK)
			{
				std::cout << "●";
				continue;
			}
			else if (board[i][j] == eStones::WHITE)
			{
				std::cout << "○";
				continue;
			}
			else if (board[i][j] == eStones::CURSOR)
			{
				std::cout << "⊙";
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

eInputKeys GameManager::GetInputKey(bool bIsPlaying, float bonusTime)
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
			/*
			else if (input == 32)
			{
				return eInputKeys::SPACE;
			}
			*/
			else if (input == '\r')
			{
				return eInputKeys::ENTER;
			}
		}
	}
}
