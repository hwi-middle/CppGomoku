#pragma once
#include <iostream>
#include <cassert>

enum class eRules	//�������� ������ ��
{
	FREE,
	STANDARD,
	RENJU
};

enum class eStones	//�� ĭ�� �� �� �ִ� ��
{
	BLACK,
	WHITE
};

enum class eInputKeys	//��ȿ�� �Է� Ű��
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	ENTER
};

enum class eTitleActions	//Ÿ��Ʋ ȭ�鿡�� ������ �� �ִ� ���۵�
{
	START,
	HELP,
	EXIT
};
