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
	void SetConsoleCursorAbsoluteCoordinate(SHORT x, SHORT y);
	void SetConsoleCursorByBoardCoordinate(SHORT x, SHORT y);
	void PrintSystemMessage(std::string str, bool bIsErrorMessage);
	void PrintBoardCharByCoordinate(int x, int y);
	void SetAndPrintBoardCursor(eInputKeys key);
	ePlaceErrorCodes PlaceStone();
	void CheckForbiddenMoves();
	int CountContinuousStones(int x, int y, eDirection dir);
	bool CheckMeetRules(int count);
	bool CheckGameOver();
	eInputKeys GetInputKey();
public:
	GameManager();
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
};
