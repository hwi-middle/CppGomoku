﻿#define VERSION ("0.0.1b")
#define	BOARD_SIZE (15)
#define X first
#define Y second

#include "Gomoku.h"
#include "GameManager.h"

GameManager::GameManager() :bGameOver(false), bRefreshNeeded(true), cursor({ 0,0 }), lastPlaced({ -1,-1 }), turn(eTurns::BLACK), currentRule(eRules::FREE)
{
	dir[0] = eDirection::VERTICAL;
	dir[1] = eDirection::HORIZONTAL;
	dir[2] = eDirection::LEFT_UP_DIAGONAL;
	dir[3] = eDirection::RIGHT_UP_DIAGONAL;
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
			board[x][y] = eStones::NONE;
		}
	}
}

bool GameManager::SelectRule()
{
	system("cls");

	int ruleCursor = 0;

	while (true)
	{
		std::cout << "\n※상하 방향키로 이동, Enter키로 선택\n\n";

		for (int i = 0; i < 3; i++)
		{
			if (ruleCursor == i)
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
				std::cout << "  자 유 룰  ";
				break;
			case 1:
				std::cout << "  렌 주 룰  ";
				break;
			case 2:
				std::cout << "  뒤 로 가 기  ";
				break;
			default:
				assert(false);
				break;
			}

			if (ruleCursor == i)
			{
				std::cout << "<<";
			}
			std::cout << "\n";
		}

		eInputKeys key = GetInputKey();
		switch (key)
		{
		case eInputKeys::ARROW_UP:
			ruleCursor--;
			if (ruleCursor < 0) ruleCursor = 0;
			break;
		case eInputKeys::ARROW_DOWN:
			ruleCursor++;
			if (ruleCursor > 2) ruleCursor = 2;
			break;
		case eInputKeys::ENTER:
			if (ruleCursor == 0)
			{
				std::cout << "\n\n자유룰로 게임을 시작합니다.";
				Sleep(1000);
				currentRule = eRules::FREE;
				return true;
			}
			else if (ruleCursor == 1)
			{
				std::cout << "\n\n렌주룰로 게임을 시작합니다.";
				Sleep(1000);
				currentRule = eRules::RENJU;
				return true;
			}
			else
			{
				return false;
			}
		default:
			break;
		}
		system("cls");
	}
}

eTitleActions GameManager::ShowTitle(void)
{
	system("cls");

	int titleCursor = 0;

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
			if (titleCursor == i)
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

			if (titleCursor == i)
			{
				std::cout << "<<";
			}
			std::cout << "\n";
		}

		eInputKeys key = GetInputKey();
		switch (key)
		{
		case eInputKeys::ARROW_UP:
			titleCursor--;
			if (titleCursor < 0) titleCursor = 0;
			break;
		case eInputKeys::ARROW_DOWN:
			titleCursor++;
			if (titleCursor > 2) titleCursor = 2;
			break;
		case eInputKeys::ENTER:
			if (titleCursor == 0) return eTitleActions::START;
			else if (titleCursor == 1) return eTitleActions::HELP;
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
	if (SelectRule() == false)
	{
		return;
	}

	DrawBoard();
	SetConsoleCursorByBoardCoordinate(cursor.X, cursor.Y);
	PrintBoardCharByCoordinate(cursor.X, cursor.Y);
	bool bPrintTurn = true;
	ePlaceErrorCodes prevErrorCode = ePlaceErrorCodes::SUCCESS;

	while (bGameOver == false)
	{
		if (bPrintTurn == true)
		{
			switch (turn)
			{
			case eTurns::BLACK:
				PrintSystemMessage("흑돌의 차례입니다.", false);
				break;
			case eTurns::WHITE:
				PrintSystemMessage("백돌의 차례입니다.", false);
				break;
			default:
				assert(false);
				break;
			}
		}
		if (currentRule == eRules::RENJU)
		{
			PrintForbiddenMoves();
		}

		bool tryPlace = false;
		eInputKeys key = GetInputKey();
		ePlaceErrorCodes errorCode = ePlaceErrorCodes::SUCCESS;
		switch (key)
		{
		case eInputKeys::ARROW_UP:
		case eInputKeys::ARROW_DOWN:
		case eInputKeys::ARROW_LEFT:
		case eInputKeys::ARROW_RIGHT:
			SetAndPrintBoardCursor(key);
			break;
		case eInputKeys::SPACE:
			tryPlace = true;
			errorCode = PlaceStone();
			break;
		}

		if (tryPlace == true)
		{
			bPrintTurn = false;
			if (errorCode == ePlaceErrorCodes::SUCCESS)
			{
				bPrintTurn = true;
			}
			else if (prevErrorCode != errorCode)
			{
				if (errorCode == ePlaceErrorCodes::FAIL_BROKE_CUR_RULE)
				{
					PrintSystemMessage("오류: 룰에 의해 착수가 불가능한 곳 입니다.", true);
				}
				else if (errorCode == ePlaceErrorCodes::FAIL_BLACK_STONE_EXISTS)
				{
					PrintSystemMessage("오류: 이미 흑돌이 놓여져 있습니다.", true);
				}
				else if (errorCode == ePlaceErrorCodes::FAIL_WHITE_STONE_EXISTS)
				{
					PrintSystemMessage("오류: 이미 백돌이 놓여져 있습니다.", true);
				}
			}
			prevErrorCode = errorCode;
		}
	}

	//게임오버
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	cursor = { -1,-1 };
	for (auto co : finalStones)
	{
		SetConsoleCursorByBoardCoordinate(co.X, co.Y);
		PrintBoardCharByCoordinate(co.X, co.Y);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	switch (turn)
	{
	case eTurns::BLACK:
		board[cursor.X][cursor.Y] = eStones::WHITE;
		PrintSystemMessage("백돌이 승리하였습니다!", false);
		break;
	case eTurns::WHITE:
		board[cursor.X][cursor.Y] = eStones::BLACK;
		if (currentRule == eRules::RENJU)
		{
			PrintForbiddenMoves();	//금수 표시를 없앰
		}
		PrintSystemMessage("흑돌이 승리하였습니다!", false);
		break;
	default:
		assert(false);
		break;
	}
	Sleep(1000);
	PrintSystemMessage("", true);
	system("pause");
}

void GameManager::SetConsoleCursorAbsoluteCoordinate(SHORT x, SHORT y)
{
	COORD cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void GameManager::SetConsoleCursorByBoardCoordinate(SHORT x, SHORT y)
{
	//API는 x와 y가 반대
	bool check = false;
	COORD cur = { 3 + y * 2, 1 + x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void GameManager::PrintSystemMessage(std::string str, bool bIsErrorMessage)
{
	if (bIsErrorMessage == true)
	{
		SetConsoleCursorAbsoluteCoordinate(34, 13);
		std::cout << "│                                                         │";
		SetConsoleCursorAbsoluteCoordinate(38, 13);
		std::cout << str;
	}
	else
	{
		SetConsoleCursorAbsoluteCoordinate(34, 12);
		std::cout << "│                                                         │";
		SetConsoleCursorAbsoluteCoordinate(34, 13);
		std::cout << "│                                                         │";
		SetConsoleCursorAbsoluteCoordinate(38, 12);
		std::cout << str;
	}
}

void GameManager::PrintBoardCharByCoordinate(int x, int y)
{
	if (cursor == std::make_pair(x, y))	//커서 노출이 최우선
	{
		std::cout << "⊙";
		return;
	}

	if (board[x][y] == eStones::BLACK)
	{
		std::cout << "○";
		return;
	}
	else if (board[x][y] == eStones::WHITE)
	{
		std::cout << "●";
		return;
	}
	else if (board[x][y] == eStones::FORBIDDEN && turn == eTurns::BLACK)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "ⓧ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return;
	}

	if (x == 0 && y == 0)
	{
		std::cout << "┌ ";
	}
	else if (x == 0 && y == 14)
	{
		std::cout << "┐ ";
	}
	else if (x == 14 && y == 0)
	{
		std::cout << "└ ";
	}
	else if (x == 14 && y == 14)
	{
		std::cout << "┘ ";
	}
	else if (x == 0)
	{
		std::cout << "┬ ";
	}
	else if (x == 14)
	{
		std::cout << "┴ ";
	}
	else if (y == 0)
	{
		std::cout << "├ ";
	}
	else if (y == 14)
	{
		std::cout << "┤ ";
	}
	else
	{
		std::cout << "┼ ";
	}
}

void GameManager::SetAndPrintBoardCursor(eInputKeys key)
{
	std::pair<int, int> prev = { cursor.X, cursor.Y };

	SetConsoleCursorByBoardCoordinate(prev.X, prev.Y);
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
	if (prev.X == lastPlaced.X && prev.Y == lastPlaced.Y)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
	}
	PrintBoardCharByCoordinate(prev.X, prev.Y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleCursorByBoardCoordinate(cursor.X, cursor.Y);
	PrintBoardCharByCoordinate(cursor.X, cursor.Y);
}

ePlaceErrorCodes GameManager::PlaceStone()
{
	switch (board[cursor.X][cursor.Y])
	{
	case eStones::FORBIDDEN:
		if (turn == eTurns::BLACK)
		{
			return ePlaceErrorCodes::FAIL_BROKE_CUR_RULE;
		}
		break;
	case eStones::BLACK:
		return ePlaceErrorCodes::FAIL_BLACK_STONE_EXISTS;
	case eStones::WHITE:
		return ePlaceErrorCodes::FAIL_WHITE_STONE_EXISTS;
	case eStones::NONE:
		break;
	default:
		assert(false);
		break;
	}

	if (lastPlaced.X != -1)
	{
		SetConsoleCursorByBoardCoordinate(lastPlaced.X, lastPlaced.Y);
		switch (board[lastPlaced.X][lastPlaced.Y])
		{
		case eStones::BLACK:
			std::cout << "○";
			break;
		case eStones::WHITE:
			std::cout << "●";
			break;
		default:
			std::cout << lastPlaced.X;
			assert(false);
			break;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
	SetConsoleCursorByBoardCoordinate(cursor.X, cursor.Y);
	switch (turn)
	{
	case eTurns::BLACK:
		board[cursor.X][cursor.Y] = eStones::BLACK;
		std::cout << "○";
		bGameOver = CheckGameOver();
		turn = eTurns::WHITE;
		break;
	case eTurns::WHITE:
		board[cursor.X][cursor.Y] = eStones::WHITE;
		std::cout << "●";
		bGameOver = CheckGameOver();
		turn = eTurns::BLACK;
		break;
	default:
		assert(false);
		break;
	}
	lastPlaced = { cursor.X, cursor.Y };

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return ePlaceErrorCodes::SUCCESS;
}

void GameManager::PrintForbiddenMoves()
{
	assert(currentRule == eRules::RENJU);

	if (turn == eTurns::BLACK)
	{
		forbiddenMoves.clear();
		for (int x = 0; x < BOARD_SIZE; x++)
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				if (board[x][y] == eStones::NONE || board[x][y] == eStones::FORBIDDEN)
				{
					for (int i = 0; i < 4; i++)
					{
						bool forbidden = false;
						//장수 확인
						if (CountContinuousStones(x, y, dir[i]) > 5)
						{
							forbidden = true;
						}
						//33 확인
						else if (CheckDoubleThree(x, y, eStones::BLACK))
						{
							forbidden = true;
						}

						if (forbidden == true)
						{
							board[x][y] = eStones::FORBIDDEN;
							forbiddenMoves.push_back(std::make_pair(x, y));
							SetConsoleCursorByBoardCoordinate(x, y);
							PrintBoardCharByCoordinate(x, y);
						}
					}
				}
			}
		}
	}
	else
	{
		for (auto move : forbiddenMoves)
		{
			SetConsoleCursorByBoardCoordinate(move.X, move.Y);
			PrintBoardCharByCoordinate(move.X, move.Y);
		}
	}
}

int GameManager::CountContinuousStones(int x, int y, eDirection dir)
{
	finalStones.clear();
	sideStones.clear();
	std::pair<int, int> pos = { x, y };
	int count = 1;
	int posRow;
	int posCol;
	eStones color;

	switch (turn)
	{
	case eTurns::BLACK:
		color = eStones::BLACK;
		break;
	case eTurns::WHITE:
		color = eStones::WHITE;
		break;
	default:
		assert(false);
		break;
	}

	switch (dir)
	{
	case eDirection::VERTICAL:
		finalStones.push_back({ pos.X, pos.Y });
		count = 1;
		posRow = pos.X + 1;
		while (posRow < BOARD_SIZE)
		{
			if (board[posRow][pos.Y] == color)
			{
				finalStones.push_back({ posRow, pos.Y });
				count++;
				posRow++;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });

		posRow = pos.X - 1;
		while (posRow >= 0)
		{
			if (board[posRow][pos.Y] == color)
			{
				finalStones.push_back({ posRow, pos.Y });
				count++;
				posRow--;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });
		break;
	case eDirection::HORIZONTAL:
		finalStones.push_back({ pos.X, pos.Y });
		count = 1;
		posCol = pos.Y + 1;
		while (posCol < BOARD_SIZE)
		{
			if (board[pos.X][posCol] == color)
			{
				finalStones.push_back({ pos.X, posCol });
				count++;
				posCol++;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });

		posCol = pos.Y - 1;
		while (posCol >= 0)
		{
			if (board[pos.X][posCol] == color)
			{
				finalStones.push_back({ pos.X, posCol });
				count++;
				posCol--;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });
		break;
	case eDirection::LEFT_UP_DIAGONAL:
		finalStones.push_back({ pos.X, pos.Y });
		count = 1;
		posRow = pos.X + 1;
		posCol = pos.Y + 1;
		while (posCol < BOARD_SIZE && posRow < BOARD_SIZE)
		{
			if (board[posRow][posCol] == color)
			{
				finalStones.push_back({ posRow, posCol });
				count++;
				posCol++;
				posRow++;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });

		posRow = pos.X - 1;
		posCol = pos.Y - 1;
		while (posCol >= 0 && posRow >= 0)
		{
			if (board[posRow][posCol] == color)
			{
				finalStones.push_back({ posRow, posCol });
				count++;
				posCol--;
				posRow--;
			}
			else
			{
				break;
			}
		}		
		sideStones.push_back({ posRow, posCol });
		break;
	case eDirection::RIGHT_UP_DIAGONAL:
		finalStones.push_back({ pos.X, pos.Y });
		count = 1;
		posRow = pos.X - 1;
		posCol = pos.Y + 1;
		while (posCol < BOARD_SIZE && posRow >= 0)
		{
			if (board[posRow][posCol] == color)
			{
				finalStones.push_back({ posRow, posCol });
				count++;
				posCol++;
				posRow--;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });

		posRow = pos.X + 1;
		posCol = pos.Y - 1;
		while (posCol >= 0 && posRow < BOARD_SIZE)
		{
			if (board[posRow][posCol] == color)
			{
				finalStones.push_back({ posRow, posCol });
				count++;
				posCol--;
				posRow++;
			}
			else
			{
				break;
			}
		}
		sideStones.push_back({ posRow, posCol });
		break;
	default:
		assert(false);
		break;
	}

	return count;
}

bool GameManager::CheckMeetVictoryCondition(int count)
{
	if (currentRule == eRules::FREE && count == 5)
	{
		return true;
	}
	else if (currentRule == eRules::RENJU)
	{
		if (turn == eTurns::WHITE && count >= 5)
		{
			return true;
		}
		else if (turn == eTurns::BLACK && count == 5)
		{
			return true;
		}
	}
	return false;
}

bool GameManager::CheckOpenFour(int x, int y, eDirection dir, eStones color)
{
	if (CountContinuousStones(x, y, dir) == false)
	{
		return false;
	}
	for (int i = 0; i < 2; i++)
	{
		if (sideStones[i].X >= BOARD_SIZE || sideStones[i].Y >= BOARD_SIZE || sideStones[i].X < 0 || sideStones[i].Y < 0)
		{
			return false;
		}
	}

	bool res = true;
	

	return false;
}
bool GameManager::CheckDoubleThree(int x, int y, eStones color)
{
	assert(board[x][y] == eStones::NONE || board[x][y] == eStones::FORBIDDEN);

	int cnt = 0;
	board[x][y] = color;
	for (int i = 0; i < 4; i++)
	{
		if (CheckOpenFour(x, y, dir[i], color) == true)
		{
			cnt++;
		}
	}
	board[x][y] = eStones::NONE;
	return (cnt >= 2) ? true : false;
}
bool GameManager::CheckDoubleFour(int x, int y, eStones color)
{
	return true;
}

bool GameManager::CheckGameOver()
{
	eDirection dir[] = { eDirection::VERTICAL, eDirection::HORIZONTAL, eDirection::LEFT_UP_DIAGONAL, eDirection::RIGHT_UP_DIAGONAL };

	//승리조건을 만족하는지 판단
	for (int i = 0; i < 4; i++)
	{
		if (CheckMeetVictoryCondition(CountContinuousStones(cursor.X, cursor.Y, dir[i])) == true)
		{
			return true;
		}
	}

	return false;
}

void GameManager::DrawBoard()
{
	system("cls");
	std::cout << "    ";
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << (char)('A' + i) << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i < 9)
		{
			std::cout << " ";
		}
		std::cout << i + 1 << " ";

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			PrintBoardCharByCoordinate(i, j);
		}
		std::cout << "\n";
	}

	int w = 30;
	int h = 10;
	for (int i = 1; i <= h; i++)
	{
		SetConsoleCursorAbsoluteCoordinate(34, i - 1);
		for (int j = 1; j <= w; j++)
		{
			if (i == 1 && j == 1)
			{
				std::cout << "┌ ";
			}
			else if (i == 1 && j == w)
			{
				std::cout << "┐ ";
			}
			else if (i == h && j == 1)
			{
				std::cout << "└ ";
			}
			else if (i == h && j == w)
			{
				std::cout << "┘ ";
			}
			else if (i == 1)
			{
				std::cout << "─ ";
			}
			else if (i == h)
			{
				std::cout << "─ ";
			}
			else if (j == 1)
			{
				std::cout << "│ ";
			}
			else if (j == w)
			{
				std::cout << "│ ";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "\n";
	}

	h = 6;
	for (int i = 1; i <= h; i++)
	{
		SetConsoleCursorAbsoluteCoordinate(34, i + 9);
		for (int j = 1; j <= w; j++)
		{
			if (i == 1 && j == 1)
			{
				std::cout << "┌ ";
			}
			else if (i == 1 && j == w)
			{
				std::cout << "┐ ";
			}
			else if (i == h && j == 1)
			{
				std::cout << "└ ";
			}
			else if (i == h && j == w)
			{
				std::cout << "┘ ";
			}
			else if (i == 1)
			{
				std::cout << "─ ";
			}
			else if (i == h)
			{
				std::cout << "─ ";
			}
			else if (j == 1)
			{
				std::cout << "│ ";
			}
			else if (j == w)
			{
				std::cout << "│ ";
			}
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << "\n";
	}

	int line = 0;
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << " H E L P ";
	line++;
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "○ : 흑돌이 놓인 곳";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "● : 백돌이 놓인 곳";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "ⓧ : 금수(놓을 수 없음)";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "⊙ : 커서(자신이 놓을 곳)";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "←↑↓→ : 커서 이동";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "SPACE : 착수(돌 놓기)";

	line = 10;
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << " M E S S A G E ";
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
