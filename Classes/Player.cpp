#include "Player.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;

Player::Player()
{
    mode = 0;
    totalMatch = 3;
}

Player::Player(int gameMode, int match) 
{ 
    mode = gameMode;

    if (match >= 3 && match <= mode)
        totalMatch = match;
    else
        totalMatch = 3;

    for (int i = 1; i <= (mode * mode); i++)
        panels[i] = false;
}

std::string Player::toString()
{
    std::string s = "Panels Taken: ";
    for (int i = 1; i <= (mode * mode); i++)
    {
        if (panels[i])
        {
           s += std::to_string(i) + " ";
        }
    }
    return s;
}

void Player::panelAdd(int panel)
{
    if (panel > 0 && panel <= mode * mode)
        panels[panel] = true;
    else
        CCLOG("ERROR: PANEL INDEX LESS THAN 1");

    //CCLOG("size is %d and panel is %d", sizeof(panels), panel);

}

bool Player::didWin(int panel)
{
    int diagUp = mode + 1;
    int diagDown = mode - 1;
    int horizontal = 1;
    int vertical = mode;

    if (winGame(panel, diagUp) || winGame(panel, diagDown)
        || winGame(panel, horizontal) || winGame(panel, vertical))
        return true;

    return false;
}

bool Player::winGame(int panel, int increment)
{
    int winCounter = 0;
    int startPanel = panel;

    for (int i = -1 * (totalMatch - 1); i <= 0; i++)
    {
        winCounter = 0;
        startPanel = panel + (i * increment);
        for (int j = 0; j < totalMatch; j++)
        {
            if (isTaken(startPanel + (j * increment)))
                winCounter++;
        }
        if (winCounter == totalMatch)
            return true;
    }

    return false;
}

bool Player::isTaken(int panel)
{
    if (panel > 0 && panel <= mode * mode)
    {
        if (panels[panel])
            return true;
    }
    return false;
}