#pragma once
#include "Gomoku.h"

class GameManager
{
private:
public:
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
	bool CheckTimePassed(float bonusTime);
	void ResetTimer(void);
	eInputKey GetInputKey(bool bIsPlaying, float bonusTime);
};
