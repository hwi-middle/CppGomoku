#include "Gomoku.h"
#include "GameManager.h"

int main(void)
{
	system("mode con cols=100 lines=30 | title Gomoku");
	while (true)
	{
		GameManager* gameManager = new GameManager(eRules::FREE);
		eTitleActions selection;

		selection = gameManager->ShowTitle();

		switch (selection)
		{
		case eTitleActions::START:
			gameManager->StartGame();
			break;
		case eTitleActions::HELP:
			gameManager->ShowHelp();
			break;
		case eTitleActions::EXIT:
			delete gameManager;
			return 0;
			break;
		default:
			assert(false);
			break;
		}
	}
	return 0;
}