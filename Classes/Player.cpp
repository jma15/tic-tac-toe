#include "Player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Player::Player(int gameMode)
{
	mode = gameMode;
	panels = new bool[gameMode * gameMode];
}

Player::~Player()
{
	delete[] panels;
}

void Player::panelAdd(int panel)
{
	if (panel > 0)
		panels[panel - 1] = true;
	else
		CCLOG("ERROR: PANEL INDEX LESS THAN 1");
    
    CCLOG("size is %d", sizeof(panels));
}

bool Player::didWin()
{
	switch (mode)
	{
	case 3:
		if (panels[1])
		{
			if ((panels[2] && panels[3])
				|| (panels[4] && panels[7])
				|| (panels[5] && panels[9]))
				return true;
		}
		if (panels[5])
		{
			if ((panels[4] && panels[6])
				|| (panels[2] && panels[8])
				|| (panels[3] && panels[7]))
				return true;
		}
		if (panels[9])
		{
			if ((panels[7] && panels[8])
				|| (panels[3] && panels[6]))
				return true;
		}
		break;
	case 4:
		break;
	case 5:
		break;
	}
	return false;
}