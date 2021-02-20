#define VERSION ("0.0.1b")
#define	BOARD_SIZE (15)
#define X first
#define Y second

#include "Gomoku.h"
#include "GameManager.h"

GameManager::GameManager(eRules rule) :bGameOver(false), bRefreshNeeded(true), cursor({ 0,0 }), turn(eTurns::BLACK), currentRule(rule)
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
	DrawBoard();
	SetConsoleCursorByBoardCoordinate(cursor.X, cursor.Y);
	PrintBoardCharByCoordinate(cursor.X, cursor.Y);
	SetConsoleCursorToSystemMessageZone();

	while (bGameOver == false)
	{
		switch (turn)
		{
		case eTurns::BLACK:
			std::cout << "흑돌";
			break;
		case eTurns::WHITE:
			std::cout << "백돌";
			break;
		default:
			assert(0);
			break;
		}
		std::cout << "의 차례입니다.\n";

		bool tryPlace = false;
		eInputKeys key = GetInputKey();
		ePlaceErrorCodes success = ePlaceErrorCodes::SUCCESS;
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
			success = PlaceStone();
			break;
		}

		if (tryPlace == true)
		{
			SetConsoleCursorToSystemMessageZone();
			switch (success)
			{
			case ePlaceErrorCodes::SUCCESS:
				break;
			case ePlaceErrorCodes::FAIL_BROKE_CUR_RULE:
				std::cout << "오류: 룰에 의해 착수가 불가능한 곳 입니다.\n";
				break;
			case ePlaceErrorCodes::FAIL_ALREADY_EXISTS:
				switch (board[cursor.X][cursor.Y])
				{
				case eStones::BLACK:
					std::cout << "오류: 이미 흑돌이 놓여져 있습니다.\n";
					break;
				case eStones::WHITE:
					std::cout << "오류: 이미 백돌이 놓여져 있습니다.\n";
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

	switch (turn)
	{
	case eTurns::BLACK:
		board[cursor.X][cursor.Y] = eStones::WHITE;
		cursor = { -1,-1 };
		DrawBoard();
		std::cout << "흰돌";
		break;
	case eTurns::WHITE:
		board[cursor.X][cursor.Y] = eStones::BLACK;
		cursor = { -1,-1 };
		DrawBoard();
		std::cout << "검은돌";
		break;
	default:
		assert(0);
		break;
	}
	std::cout << "이 승리하였습니다!\n";
	system("pause");
}

void GameManager::SetConsoleCursorAbsoluteCoordinate(int x, int y)
{
	COORD cur = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void GameManager::SetConsoleCursorByBoardCoordinate(int x, int y)
{
	//API는 x와 y가 반대
	COORD cur = { 2 + cursor.Y * 2, 1 + cursor.X };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void GameManager::SetConsoleCursorToSystemMessageZone()
{
	//API는 x와 y가 반대
	COORD cur = { 0, 16 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	for (int i = 0; i < 5; i++) 
	{
		for (int j = 0; j < 80; j++)
		{
			std::cout << " ";
		}
		std::cout << "\n";
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
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
	else if (board[x][y] == eStones::NOT_PLACEABLE)
	{
		std::cout << "ⓧ";
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
	
	PrintBoardCharByCoordinate(prev.X, prev.Y);
	SetConsoleCursorToSystemMessageZone();
	SetConsoleCursorByBoardCoordinate(cursor.X, cursor.Y);
	PrintBoardCharByCoordinate(cursor.X, cursor.Y);
	SetConsoleCursorToSystemMessageZone();
}

ePlaceErrorCodes GameManager::PlaceStone()
{
	switch (board[cursor.X][cursor.Y])
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
		assert(0);
		break;
	}
	SetConsoleCursorToSystemMessageZone();

	return ePlaceErrorCodes::SUCCESS;
}

bool GameManager::CheckGameOver()
{
	int count;
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
		assert(0);
		break;
	}

	//가로 점수 확인 
	count = 1;
	posCol = cursor.X + 1;
	while (posCol < BOARD_SIZE) {
		if (board[cursor.X][posCol] == color) {
			count++;
			posCol++;
		}
		else {
			break;
		}
	}

	posCol = cursor.X - 1;
	while (posCol >= 0) {
		if (board[cursor.X][posCol] == color) {
			count++;
			posCol--;
		}
		else {
			break;
		}
	}

	//측정된 점수 반영 
	if (count >= 5) { //프리룰인지 체크해야함(추후 구현)
		return true;
	}

	//세로 점수 확인 
	count = 1;
	posRow = cursor.Y + 1;
	while (posRow < BOARD_SIZE) {
		if (board[posRow][cursor.Y] == color) {
			count++;
			posRow++;
		}
		else {
			break;
		}
	}

	posRow = cursor.Y - 1;
	while (posRow >= 0) {
		if (board[posRow][cursor.Y] == color) {
			count++;
			posRow--;
		}
		else {
			break;
		}
	}

	//측정된 점수 반영 
	if (count >= 5) {
		return true;
	}

	//좌상향 대각선 점수 확인 
	count = 1;
	posRow = cursor.X + 1;
	posCol = cursor.Y + 1;
	while (posCol < BOARD_SIZE && posRow < BOARD_SIZE) {
		if (board[posRow][posCol] == color) {
			count++;
			posCol++;
			posRow++;
		}
		else {
			break;
		}
	}

	posRow = cursor.X - 1;
	posCol = cursor.Y - 1;
	while (posCol >= 0 && posRow >= 0) {
		if (board[posRow][posCol] == color) {
			count++;
			posCol--;
			posRow--;
		}
		else {
			break;
		}
	}

	//측정된 점수 반영 
	if (count >= 5) {
		return true;
	}

	//우상향 대각선 점수 확인 
	count = 1;
	posRow = cursor.X - 1;
	posCol = cursor.Y + 1;
	while (posCol < BOARD_SIZE && posRow >= 0) {
		if (board[posRow][posCol] == color) {
			count++;
			posCol++;
			posRow--;
		}
		else {
			break;
		}
	}

	posRow = cursor.X + 1;
	posCol = cursor.Y - 1;
	while (posCol >= 0 && posRow < BOARD_SIZE) {
		if (board[posRow][posCol] == color) {
			count++;
			posCol--;
			posRow++;
		}
		else {
			break;
		}
	}

	//측정된 점수 반영 
	if (count >= 5) {
		return true;
	}

	return false;
}

void GameManager::DrawBoard()
{
	system("cls");
	std::cout << "  ";
	for (int i = 0; i < 15; i++)
	{
		std::cout << (char)('A' + i) << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < 15; i++)
	{
		std::cout << (char)('A' + i) << " ";
		for (int j = 0; j < 15; j++)
		{
			PrintBoardCharByCoordinate(i, j);
		}
		std::cout << "\n";
	}
	
	int w = 30;
	int h = 9;
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

	h = 7;
	for (int i = 1; i <= h; i++)
	{
		SetConsoleCursorAbsoluteCoordinate(34, i + 8);
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
	std::cout << "⊙ : 커서(자신이 놓을 곳)";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "←↑↓→ : 커서 이동";
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "ENTER : 착수(돌 놓기)";

	line = 9;
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << " M E S S A G E ";
	line++;
	SetConsoleCursorAbsoluteCoordinate(38, line++);
	std::cout << "여기에는 시스템 메시지가 표시되어야 합니다.";
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
