#pragma once
#include "Gomoku.h"
#define	BOARD_SIZE (15)

class GameManager
{
private:
	HANDLE screen[2]; //�� ���� ȭ����۸� ���� �迭
	int cur_buf_idx;

	eStones board[BOARD_SIZE][BOARD_SIZE];
	eTurns turn;
	std::pair<int, int> cursor;
	bool bGameOver;
	void DrawBoard();
	void SetCursor(eInputKeys key);
	bool PlaceStone(int x, int y);
	bool CheckGameOver();
	eInputKeys GetInputKey();
public:
	GameManager(void);
	eTitleActions ShowTitle(void);
	void ShowHelp(void);
	void StartGame(void);
};
