#include "Player.h"
#include "ui/CocosGUI.h"
#include <string>
#include <cmath>

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
    int edgeCounter = 0;

    int startPanel = panel;
    int tempPanel = panel;
    int tempPanelRow = 0;

    // start from furthest back (totalMatch - 1) panels
    for (int i = -1 * (totalMatch - 1); i <= 0; i++)
    {
        // set counters & startPanel index number
        winCounter = 0;
        edgeCounter = 0;
        startPanel = panel + (i * increment);

        // check if there are (totalMatch) panels in a row
        for (int j = 0; j < totalMatch; j++)
        {
            // current panel being checked & its row #
            tempPanel = startPanel + (j * increment);
            tempPanelRow = ceil(tempPanel / static_cast<double>(mode));

            // if current panel isTaken by player
            if (isTaken(tempPanel))
            {
                // if currently checking horizontal && is in same row, then win++
                if (increment == 1 && tempPanelRow == ceil(panel / static_cast<double>(mode)))
                    winCounter++; 
                // else if checking diagonal && is an edge panel, then edge++ & win++
                else if (increment == mode + 1 || increment == mode - 1)
                {
                    winCounter++;
                    // check if panel is on the edge of board
                    if (tempPanelRow == mode || tempPanelRow == 1
                        || tempPanel % mode == 1 || tempPanel % mode == 0)
                        edgeCounter++;
                }
                // else just win++
                else
                    winCounter++;
            }
        }

        // if there were more than 2 edges, panels not in same diagonal
        if (edgeCounter > 2)
            return false;
        // if panels in a row == totalMatch, then win
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