#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Player.h"

class Game : public cocos2d::Layer
{
	cocos2d::Size visibleSize;
	cocos2d::Sprite* panel1 = nullptr;
	cocos2d::Sprite* panel2 = nullptr;
	cocos2d::Sprite* panel3 = nullptr;
	cocos2d::Sprite* panel4 = nullptr;
	cocos2d::Sprite* panel5 = nullptr;
	cocos2d::Sprite* panel6 = nullptr;
	cocos2d::Sprite* panel7 = nullptr;
	cocos2d::Sprite* panel8 = nullptr;
	cocos2d::Sprite* panel9 = nullptr;
	std::vector<cocos2d::Sprite*> spriteArray;

	cocos2d::Sprite* panel10 = nullptr;
	cocos2d::Sprite* panel11 = nullptr;
	cocos2d::Sprite* panel12 = nullptr;
	cocos2d::Sprite* panel13 = nullptr;
	cocos2d::Sprite* panel14 = nullptr;
	cocos2d::Sprite* panel15 = nullptr;
	cocos2d::Sprite* panel16 = nullptr;
    
    cocos2d::Sprite* panel17 = nullptr;
    cocos2d::Sprite* panel18 = nullptr;
    cocos2d::Sprite* panel19 = nullptr;
    cocos2d::Sprite* panel20 = nullptr;
    cocos2d::Sprite* panel21 = nullptr;
    cocos2d::Sprite* panel22 = nullptr;
    cocos2d::Sprite* panel23 = nullptr;
    cocos2d::Sprite* panel24 = nullptr;
    cocos2d::Sprite* panel25 = nullptr;
    
    Player playerOne = Player(3);
    Player playerTwo = Player(3);
    
    cocos2d::Label * labelOne;
    cocos2d::Sprite* labelOneBackground;
    cocos2d::Label * labelTwo;
    cocos2d::Sprite* labelTwoBackground;


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

	CREATE_FUNC(Game);

};


#endif // __GAME_H__
