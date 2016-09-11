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
    bool win = false;
    int winCounter = 1;
    int tempPanel = panel;

    // Check backward the last two panels
    for(int i = 0; i <= totalMatch - 1; i++)
    {
        //CCLOG("In first reverse is %d", tempPanel);
        // Go back one diagonal
        tempPanel = tempPanel - increment;
        // If panel is available and player owns it
        if(isTaken(tempPanel)) winCounter++;
        else break;
    }
    // wins from past two panels
    if(winCounter == totalMatch) return true;
    
    // Reset the counters
    int startCounter = 1;
    winCounter = 1;
    //CCLOG("TESTING %d panel is %d and increment is %d", panel-increment, panel, increment);

    // Go back one panel and start going up
    if(isTaken(panel - increment))
    {
        // Go back one panel
        tempPanel = panel - increment;
        // reset counter to start from one panel behind
        startCounter = 0;
    }
    else
    {
        // Stay in current Panel, and check the next two
        tempPanel = panel;
    }
    
    // Check one panel back and three forward, at most check 4 panel, startCounter is 0,1,2,3
    for(startCounter; startCounter <= totalMatch; startCounter++)
    {
        //CCLOG("In second forward is %d, counter is %d and winCounter is %d", tempPanel, startCounter, winCounter);
        // If panel is available and player owns it, else there is a break and didnt win yet
        if(tempPanel > 0 && isTaken(tempPanel)) winCounter++;
        else
        {
            //CCLOG("BREAK NOW in second reverse");
            break;
        }
        tempPanel = tempPanel + increment;
    }
    
    if(winCounter > 3) return true;
    
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