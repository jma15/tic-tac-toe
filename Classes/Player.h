#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player
{
public:
    Player();
    Player(int gameMode);
    ~Player();

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
private:
    int mode;
    bool panels[26];
};

#endif // __PLAYER_H__
