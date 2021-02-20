#pragma once
#pragma once
#include "Gomoku.h"
#define	BOARD_SIZE (15)

class GameManager
{
private:
	eStones board[BOARD_SIZE][BOARD_SIZE];
	eTurns turn;
	std::pair<int, int> cursor;
	bool bGameOver;
	void DrawBoard();
	void SetCursor(eInputKeys key);
	ePlaceErrorCodes PlaceStone(std::pair<int, int>& cur);
	bool CheckGameOver();
	eInputKeys GetInputKey();
public:
	GameManager(void);
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
};
