#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
public:
    Player();
    Player(int gameMode);
    std::string toString();
    int totalMatch = 3;

    /**
        Adds panel to player database

        @param panel Index number of panel (starting from 1)
    */
    void panelAdd(int panel);
    /**
        Checks if player has winning combination of panels

        @return Boolean if player has won
    */
    bool didWin(int panel);
    /**
        Checks if panel is taken by player

        @param panel Index number of panel (starting from 1)
        @return Boolean if panel is taken by player
    */
    bool isTaken(int panel);

private:
    int mode;
    bool panels[26];
    bool checkWin(int panel, int increment);
    bool checkHorizontal(int panel);
    bool checkVertical(int panel);
};

#endif // __PLAYER_H__
