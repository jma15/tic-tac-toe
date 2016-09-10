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
    int horizontalI = 1;
    int verticalI = mode;
    int diagonalI = mode + 1;
    int diagonalI2 = mode - 1;

    if (checkWin(panel, horizontalI) || checkWin(panel, verticalI) 
        || checkWin(panel, diagonalI) || checkWin(panel, diagonalI2))
        return true;
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

bool Player::checkWin(int panel, int increment)
{
    int check1 = panel + increment;
    int check2 = panel + (increment * 2);
    int check3 = panel - increment;
    int check4 = panel - (increment * 2);

    if ((isTaken(check1) && isTaken(check2))
        || (isTaken(check1) && isTaken(check3))
        || (isTaken(check3) && isTaken(check4)))
        return true;

    return false;
}
//
//bool Player::checkHorizontal(int panel)
//{
//    int l1 = panel - 1;
//    int l2 = panel - 2;
//    int r1 = panel + 1;
//    int r2 = panel + 2;
//
//    if ((isTaken(l1) && isTaken(l2))
//        || (isTaken(l1) && isTaken(r1))
//        || (isTaken(r1) && isTaken(r2)))
//        return true;
//
//    return false;
//}
//
//bool Player::checkVertical(int panel)
//{
//    int u1 = panel + mode;
//    int u2 = panel + mode * 2;
//    int d1 = panel - mode;
//    int d2 = panel - mode * 2;
//
//    if ((isTaken(u1) && isTaken(u2))
//        || (isTaken(u1) && isTaken(d1))
//        || (isTaken(d1) && isTaken(d2)))
//        return true;
//
//    return false;
//}