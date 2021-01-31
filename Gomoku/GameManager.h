#pragma once
#include "Gomoku.h"

class GameManager
{
private:
public:
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
	eInputKeys GetInputKey(bool bIsPlaying, float bonusTime);
};
