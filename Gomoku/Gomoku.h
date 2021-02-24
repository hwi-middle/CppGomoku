#pragma once
#include <iostream>
#include <cassert>
#include <conio.h>
#include <Windows.h>
#include <vector>

enum class eRules	//�������� ������ ��
{
	FREE,
	RENJU
};

enum class eTurns	//���� ���ʰ� �� �÷��̾�
{
	BLACK,
	WHITE
};

enum class eDirection	//���� ������ �� ����
{
	VERTICAL,
	HORIZONTAL,
	LEFT_UP_DIAGONAL,
	RIGHT_UP_DIAGONAL
};

enum class ePlaceErrorCodes	//���� ���� �Ǵ� ������ ������ �����ϴ� �ڵ�
{
	SUCCESS,
	FAIL_BROKE_CUR_RULE,
	FAIL_BLACK_STONE_EXISTS,
	FAIL_WHITE_STONE_EXISTS
};

enum class eStones	//�� ĭ�� �� �� �ִ� ��
{
	NONE,
	BLACK,
	WHITE,
	//CURSOR,
	NOT_PLACEABLE	//�Ϻ� �꿡 ���� ���� �Ұ��� ĭ
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
