#pragma once
#include "Gomoku.h"

class GameManager
{
private:
	eStones board[15][15];

	void DrawBoard();
public:
	GameManager(void);
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
	eInputKeys GetInputKey(bool bIsPlaying, float bonusTime);
};
