#pragma once
#pragma once
#include "Gomoku.h"
#define	BOARD_SIZE (15)

class GameManager
{
private:
	eStones board[BOARD_SIZE][BOARD_SIZE];
	eTurns turn;
	eRules currentRule;
	std::pair<int, int> cursor;
	std::pair<int, int> lastPlaced;
	std::vector<std::pair<int, int>> final_stones;
	bool bGameOver;
	bool bRefreshNeeded;
	bool SelectRule();
	void DrawBoard();
	void SetConsoleCursorAbsoluteCoordinate(int x, int y);
	void SetConsoleCursorByBoardCoordinate(int x, int y);
	void PrintSystemMessage(std::string str, bool bIsErrorMessage);
	void PrintBoardCharByCoordinate(int x, int y);
	void SetAndPrintBoardCursor(eInputKeys key);
	ePlaceErrorCodes PlaceStone();
	bool CheckMeetRules(int count);
	bool CheckGameOver();
	void CheckRenju();
	eInputKeys GetInputKey();
public:
	GameManager();
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
};
