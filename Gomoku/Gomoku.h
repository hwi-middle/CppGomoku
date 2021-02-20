#pragma once
#include <iostream>
#include <cassert>
#include <conio.h>
#include <Windows.h>

enum class eRules	//�������� ������ ��
{
	FREE,
	STANDARD,
	RENJU
};

enum class eTurns	//���� ���ʰ� �� �÷��̾�
{
	BLACK,
	WHITE
};

enum class ePlaceErrorCodes
{
	SUCCESS,
	FAIL_BROKE_CUR_RULE,
	FAIL_ALREADY_EXISTS
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
