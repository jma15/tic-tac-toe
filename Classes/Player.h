#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
public:
    Player();
    Player(int gameMode);
    std::string toString();

    /**
        Adds panel to player database

        @param panel Index number of panel (starting from 1)
    */
    void panelAdd(int panel);
    /**
        Checks if player has winning combination of panels

        @return Boolean if player has won
    */
    bool didWin();
    /**
        Checks if panel is taken by player

        @param panel Index number of panel (starting from 1)
        @return Boolean if panel is taken by player
    */
    bool isTaken(int panel);

private:
    int mode;
    bool panels[26];
};

#endif // __PLAYER_H__
