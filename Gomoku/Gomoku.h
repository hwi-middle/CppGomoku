#pragma once
#include <iostream>
#include <cassert>

enum class eInputKey	//유효한 입력 키들
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	ENTER
};

enum class eTitleActions	//타이틀 화면에서 선택할 수 있는 동작들
{
	START,
	HELP,
	EXIT
};
