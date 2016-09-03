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
    createPanel();
    
    //single touch
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    //detect a touch
    touchListener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    //detect a touch and hold
    touchListener->onTouchMoved = CC_CALLBACK_2(Game::onTouchMoved, this);
    //detect end of touch
    touchListener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    //detect touch cancel
    touchListener->onTouchCancelled = CC_CALLBACK_2(Game::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
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

void Game::createPanel()
{
    
    gameMode();
    
    /*
    panel1 = cocos2d::Sprite::create();
    panel1->setTextureRect(Rect(0.0, 0.0, 50.0, 100));
    panel1->setPosition(visibleSize.width/3, visibleSize.height/3);
    panel1->setColor(Color3B(192, 192, 192));
    
    this->addChild(panel1);
     */
}

void Game::gameMode()
{
    panel1 = cocos2d::Sprite::create();
    panel2 = cocos2d::Sprite::create();
    panel3 = cocos2d::Sprite::create();
    panel4 = cocos2d::Sprite::create();
    panel5 = cocos2d::Sprite::create();
    panel6 = cocos2d::Sprite::create();
    panel7 = cocos2d::Sprite::create();
    panel8 = cocos2d::Sprite::create();
    panel9 = cocos2d::Sprite::create();

    spriteArray.push_back(panel1);
    spriteArray.push_back(panel2);
    spriteArray.push_back(panel3);
    spriteArray.push_back(panel4);
    spriteArray.push_back(panel5);
    spriteArray.push_back(panel6);
    spriteArray.push_back(panel7);
    spriteArray.push_back(panel8);
    spriteArray.push_back(panel9);

    // Use 80% of screen
    float boardSizeEndx = visibleSize.width * 0.8f;
    float boardSizeStartx = visibleSize.width * 0.2f;
    float boardSizex = boardSizeEndx - boardSizeStartx;
    // 10% gap between each panel
    float gapx = (boardSizex/mode)*0.20f;
    float panelWidthx = boardSizex/mode - gapx;
    
    // Use 80% of screen
    float boardSizeEndy = visibleSize.height * 0.8f;
    float boardSizeStarty = visibleSize.height * 0.2f;
    float boardSizey = boardSizeEndy - boardSizeStarty;
    // 10% gap between each panel
    float gapy = (boardSizey/mode)*0.20f;
    float panelHeight = boardSizey/mode - gapy;
    
    for(int i=0; i<3; i++)
    {
        //CCLOG("width is %f and gap is %f and panel widrh is %f", panelWidth*i, gap, panelWidth);
        spriteArray[i]->setTextureRect(Rect(0.0, 0.0, panelWidthx, panelHeight));
        spriteArray[i]->setAnchorPoint(Vec2(0,0));
        spriteArray[i]->setPosition( boardSizeStartx + (panelWidthx+ gapx)*i, boardSizeStarty + (panelHeight+ gapy)*i);
        spriteArray[i]->setColor(Color3B(192, 192, 192));
        //CCLOG("position is %f", spriteArray[i]->getPositionX());
        this->addChild(spriteArray[i]);
    }

}

bool Game::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event)
{
    auto sprite = event->getCurrentTarget();
    Point s = touch->getLocation();
    CCLOG("TouchBegin x => %f  y => %f tag is %d", s.x, s.y, sprite->getTag());
    
    if(panel1->boundingBox().containsPoint(s)){
        CCLOG("In the SPRITEEE");

    }
    
    return true;
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}