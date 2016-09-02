#include "game.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    std::string gameModeString = "The game is " + std::to_string(mode);
    
    auto label = Label::createWithTTF(gameModeString, "fonts/Marker Felt.ttf",32);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(label);

    createBackButton();
    CCLOG("GAME");
    return true;
}

void Game::createBackButton()
{
    auto button = cocos2d::ui::Button::create("back.png");//put image in Constructor if needed
    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                  {
                                      switch (type)
                                      {
                                          case ui::Widget::TouchEventType::BEGAN:
                                              goBackToTitle();
                                              //CCLOG("Start Began");
                                              break;
                                          case ui::Widget::TouchEventType::ENDED:
                                              //CCLOG("Start End");
                                              break;
                                          default:
                                              //CCLOG("Start Default");
                                              break;
                                      }
                                  });
    button->setPosition(Point(visibleSize.width * 0.9, (visibleSize.height * 0.05)));
    button->setScale(0.3f);
    this->addChild(button);
    
}

void Game::goBackToTitle()
{
    auto scene = HelloWorld::createScene();
    Director::getInstance( )->replaceScene(scene);
}


void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}