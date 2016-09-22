#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Player.h"

class Game : public cocos2d::Layer
{
	cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

	std::vector<cocos2d::Sprite*> spriteArray;
    
    Player playerOne;
    Player playerTwo;
    
    cocos2d::Label * labelOne;
    cocos2d::Sprite* labelOneBackground;
    cocos2d::Label * labelTwo;
    cocos2d::Sprite* labelTwoBackground;
    
    // 0 means no one wins, 1 is player1 and 2 is player2
    int gameWon;


public:
    Game() {};
	static cocos2d::Scene* createScene(int playMode);
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void createBackButton();
	void goBackToTitle();
    void createDisplay();
	void createPanel();
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event);
	void gameMode();
    void whichPanel(cocos2d::Point s);
    void playerPanelAdd(int panel);
    void switchTurns();
    void setDisplayOpacity();
    void changePanel(int panel);
    bool checkGameOver();

	CREATE_FUNC(Game);
};


#endif // __GAME_H__
