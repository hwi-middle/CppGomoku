#pragma once
#include <iostream>
#include <cassert>
#include <conio.h>
#include <Windows.h>
#include <vector>

enum class eRules	//진행중인 게임의 룰
{
	FREE,
	RENJU
};

enum class eTurns	//착수 차례가 된 플레이어
{
	BLACK,
	WHITE
};

enum class eDirection	//돌의 갯수를 셀 방향
{
	VERTICAL,
	HORIZONTAL,
	LEFT_UP_DIAGONAL,
	RIGHT_UP_DIAGONAL
};

enum class ePlaceErrorCodes	//착수 성공 또는 실패의 원인을 구분하는 코드
{
	SUCCESS,
	FAIL_BROKE_CUR_RULE,
	FAIL_BLACK_STONE_EXISTS,
	FAIL_WHITE_STONE_EXISTS
};

enum class eStones	//각 칸에 올 수 있는 돌
{
	NONE,
	BLACK,
	WHITE,
	//CURSOR,
	NOT_PLACEABLE	//일부 룰에 의해 착수 불가한 칸
};

enum class eInputKeys	//유효한 입력 키들
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	SPACE,
	ENTER
};

enum class eTitleActions	//타이틀 화면에서 선택할 수 있는 동작들
{
	START,
	HELP,
	EXIT
};
