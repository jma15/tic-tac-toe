#include "game.h"
#include "HelloWorldScene.h"

USING_NS_CC;

int mode;
Scene* Game::createScene(int playMode){
    auto scene = Scene::create();
    
    mode = playMode;
    // 'layer' is an autorelease object
    auto layer = Game::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Game::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::string gameModeString = "The game is " + std::to_string(mode);
    
    auto label = Label::createWithTTF(gameModeString, "fonts/Marker Felt.ttf",32);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(label);

    CCLOG("GAME");
    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}