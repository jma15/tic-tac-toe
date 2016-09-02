#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"


class Game : public cocos2d::Layer
{
    
    cocos2d::Size visibleSize;
public:
    static cocos2d::Scene* createScene(int playMode);
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void createBackButton();
    void goBackToTitle();

    CREATE_FUNC(Game);
    
};


#endif // __GAME_H__
