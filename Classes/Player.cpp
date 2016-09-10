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

    //CCLOG("size is %d and panel is %d", sizeof(panels), panel);

}

bool Player::winGame(int panel, int increment)
{
    bool win = false;
    int winCounter = 1;
    int tempPanel = panel;

    // Check backward the last two panels
    for(int i=0; i <= totalMatch - 1; i++)
    {
        //CCLOG("In first reverse is %d", tempPanel);
        // Go back one diagonal
        tempPanel = tempPanel - increment;
        // If panel is available and player owns it
        if(tempPanel > 0 && isTaken(tempPanel)) winCounter++;
        else break;
    }
    
    // wins from past two panels
    if(winCounter == 3) return true;
    
    // Reset the counters
    int startCounter = 1;
    winCounter = 1;
    //CCLOG("TESTING %d panel is %d and increment is %d", panel-increment, panel, increment);
    
    // Go back one panel and start going up
    if(panel - increment > 0 && isTaken(panel - increment))
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