#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"


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


public:
	static cocos2d::Scene* createScene(int playMode);
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void createBackButton();
	void goBackToTitle();
	void createPanel();
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event);
	void gameMode();

	CREATE_FUNC(Game);

};


#endif // __GAME_H__
