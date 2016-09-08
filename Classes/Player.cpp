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
        if (panels[1])
        {
            if ((panels[2] && panels[3] && panels[4])
                || (panels[5] && panels[9] && panels[13])
                || (panels[6] && panels[11] && panels[16]))
                return true;
        }
        if (panels[10])
        {
            if ((panels[9] && panels[11] && panels[12])
                || (panels[2] && panels[6] && panels[14])
                || (panels[4] && panels[7] && panels[13]))
                return true;
        }
        if (panels[7])
        {
            if ((panels[5] && panels[6] && panels[8])
                || (panels[3] && panels[11] && panels[15]))
                return true;
        }
        if (panels[16])
        {
            if ((panels[13] && panels[14] && panels[15])
                || (panels[4] && panels[8] && panels[12]))
                return true;
        }
        break;
    case 5:
        if (panels[1])
        {
            if ((panels[2] && panels[3] && panels[4] && panels[5])
                || (panels[6] && panels[11] && panels[16] && panels[21])
                || (panels[7] && panels[13] && panels[19] && panels[25]))
                return true;
        }
        if (panels[13])
        {
            if ((panels[11] && panels[12] && panels[14] && panels[15])
                || (panels[3] && panels[8] && panels[18] && panels[23])
                || (panels[5] && panels[9] && panels[17] && panels[21]))
                return true;
        }
        if (panels[7])
        {
            if ((panels[6] && panels[8] && panels[9] && panels[10])
                || (panels[2] && panels[12] && panels[17] && panels[22]))
                return true;
        }
        if (panels[19])
        {
            if ((panels[16] && panels[17] && panels[18] && panels[20])
                || (panels[4] && panels[9] && panels[14] && panels[24]))
                return true;
        }
        if (panels[25])
        {
            if ((panels[21] && panels[22] && panels[23] && panels[24])
                || (panels[5] && panels[10] && panels[15] && panels[20]))
                return true;
        }

        break;
    }
    return false;
}

bool Player::isTaken(int panel)
{
    if (panels[panel])
        return true;
    return false;
}