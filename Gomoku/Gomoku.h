#pragma once
#include <iostream>
#include <cassert>
#include <conio.h>

enum class eRules	//�������� ������ ��
{
	FREE,
	STANDARD,
	RENJU
};

enum class turns	//���� ���ʰ� �� �÷��̾�
{
	BLACK,
	WHITE
};

enum class eStones	//�� ĭ�� �� �� �ִ� ��
{
	NONE,
	BLACK,
	WHITE,
	CURSOR
};

enum class eInputKeys	//��ȿ�� �Է� Ű��
{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	SPACE,
	ENTER
};

enum class eTitleActions	//Ÿ��Ʋ ȭ�鿡�� ������ �� �ִ� ���۵�
{
	START,
	HELP,
	EXIT
};
