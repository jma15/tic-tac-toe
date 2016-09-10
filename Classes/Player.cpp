#include "Player.h"
#include "ui/CocosGUI.h"
#include <string>

USING_NS_CC;

Player::Player()
{
    mode = 0;
}

Player::Player(int gameMode) 
{ 
    mode = gameMode;
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
    if (panel > 0)
        panels[panel] = true;
    else
        CCLOG("ERROR: PANEL INDEX LESS THAN 1");

    CCLOG("size is %d and panel is %d", sizeof(panels), panel);

}

bool Player::didWin(int panel)
{
    if (checkHorizontal(panel) || checkVertical(panel))
        return true;
    return false;
}

bool Player::isTaken(int panel)
{
    if (panels[panel])
        return true;
    return false;
}

bool Player::checkHorizontal(int panel)
{
    int l1 = panel - 1;
    int l2 = panel - 2;
    int r1 = panel + 1;
    int r2 = panel + 2;

    if (l1 > 0 && l1 <= mode*mode)
    {
        if (panels[l1])
        {
            if (l2 > 0 && l2 <= mode*mode)
            {
                if (panels[l2])
                    return true;
            }
        }
        if (r1 > 0 && r1 <= mode*mode)
        {
            if (panels[r1])
                return true;
        }
    }
    if (r1 > 0 && r1 <= mode*mode)
    {
        if (panels[r1])
        {
            if (r2 > 0 && r2 <= mode*mode)
            {
                if (panels[r2])
                    return true;
            }
        }
    }

    return false;
}

bool Player::checkVertical(int panel)
{
    int u1 = panel + mode;
    int u2 = panel + mode * 2;
    int d1 = panel - mode;
    int d2 = panel - mode * 2;

    if (u1 > 0 && u1 <= mode*mode)
    {
        if (panels[u1])
        {
            if (u2 > 0 && u2 <= mode*mode)
            {
                if (panels[u2])
                    return true;
            }
        }
        if (d1 > 0 && d1 <= mode*mode)
        {
            if (panels[d1])
                return true;
        }
    }
    if (d1 > 0 && d1 <= mode*mode)
    {
        if (panels[d1])
        {
            if (d2 > 0 && d2 <= mode*mode)
            {
                if (panels[d2])
                    return true;
            }
        }
    }

    return false;
}