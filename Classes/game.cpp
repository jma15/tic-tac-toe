#include "Player.h"
#include "game.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

int mode; // game mode size of board (3, 4, 5)
int playerMove; // player # whose turn it is
int totalMoves; // to keep track of moves & flag for accepting panel touch as move

Scene* Game::createScene(int playMode){
    auto scene = Scene::create();

    mode = playMode;
    playerMove = 1;
    totalMoves = 0;

    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool Game::init()
{
    if (!Layer::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // create players
    playerOne = Player(mode);
    playerTwo = Player(mode);
    
    std::string gameModeString = "The game is " + std::to_string(mode);

    auto label = Label::createWithTTF(gameModeString, "fonts/Marker Felt.ttf", 32);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(label);

    createBackButton();
    CCLOG("GAME");
    createDisplay();
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
    Director::getInstance()->replaceScene(scene);
}

void Game::createDisplay()
{
    //std::string gameModeString = "The game is " + std::to_string(mode);
    
    // declare percentage
    float labelOnePositionX = 0;
    float labelOnePositionY = visibleSize.height*0.90f;
    float labelTwoPositionX = visibleSize.width*0.81f;
    float labelTwoPositionY = visibleSize.height*0.90f;
    float labelWidth = visibleSize.width * 0.18f;
    
    // create label one
    labelOne = Label::createWithTTF("Player One", "fonts/Marker Felt.ttf",32);
    labelOne->setAnchorPoint(Vec2(0,0));
    
    labelTwo = Label::createWithTTF("Player Two", "fonts/Marker Felt.ttf",32);
    labelTwo->setAnchorPoint(Vec2(0,0));
    
    labelOne->setWidth(labelWidth);
    labelTwo->setWidth(labelWidth);
    
    // create background color
    labelOneBackground = cocos2d::Sprite::create();
    labelOneBackground->setTextureRect(Rect(0.0, 0.0, labelOne->getWidth(), labelOne->getWidth()));
    labelOneBackground->setAnchorPoint(Vec2(0,0));
    labelOneBackground->setPosition(labelOnePositionX, labelOnePositionY);
    labelOneBackground->setColor(Color3B(0, 128, 0));
    this->addChild(labelOneBackground);
    
    labelTwoBackground = cocos2d::Sprite::create();
    labelTwoBackground->setTextureRect(Rect(0.0, 0.0, labelTwo->getWidth(), labelTwo->getWidth()));
    labelTwoBackground->setAnchorPoint(Vec2(0,0));
    labelTwoBackground->setPosition(labelTwoPositionX, labelTwoPositionY);
    labelTwoBackground->setColor(Color3B(255, 0, 0));
    this->addChild(labelTwoBackground);
    
    // add label with words
    labelOne->setPosition(labelOnePositionX, labelOnePositionY);
    labelTwo->setPosition(labelTwoPositionX, labelTwoPositionY);
    this->addChild(labelOne);
    this->addChild(labelTwo);
    setDisplayOpacity();
}

void Game::createPanel()
{

    gameMode();

    // Check condition, incase mode and size does not match
    if (mode*mode != spriteArray.size())
    {
        return;
    }

    // Use 80% of screen
    float boardSizeEndx = visibleSize.width * 0.8f;
    float boardSizeStartx = visibleSize.width * 0.2f;
    float boardSizex = boardSizeEndx - boardSizeStartx;
    // 10% gap between each panel
    float gapx = (boardSizex / mode)*0.20f;
    float panelWidthx = boardSizex / mode - gapx;

    // Use 80% of screen
    float boardSizeEndy = visibleSize.height * 0.8f;
    float boardSizeStarty = visibleSize.height * 0.2f;
    float boardSizey = boardSizeEndy - boardSizeStarty;
    // 10% gap between each panel
    float gapy = (boardSizey / mode)*0.20f;
    float panelHeight = boardSizey / mode - gapy;


    for (int j = 0; j < mode; j++)
    {
        for (int i = 0; i < mode; i++)
        {
            int value = i + j*mode;
            //CCLOG("width is %f and gap is %f and panel width is %f", panelWidth*i, gap, panelWidth);
            spriteArray[value]->setTextureRect(Rect(0.0, 0.0, panelWidthx, panelHeight));
            spriteArray[value]->setAnchorPoint(Vec2(0, 0));
            spriteArray[value]->setPosition(boardSizeStartx + (panelWidthx + gapx)*i, boardSizeStarty + (panelHeight + gapy)*j);
            spriteArray[value]->setColor(Color3B(192, 192, 192));
            //CCLOG("position is %f", spriteArray[i]->getPositionX());
            this->addChild(spriteArray[value]);
        }
    }
}

void Game::gameMode()
{
    // Create basic 3x3 declaration. Need same for 4x4 and 5x5
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

    if (mode > 3)
    {
        panel10 = cocos2d::Sprite::create();
        panel11 = cocos2d::Sprite::create();
        panel12 = cocos2d::Sprite::create();
        panel13 = cocos2d::Sprite::create();
        panel14 = cocos2d::Sprite::create();
        panel15 = cocos2d::Sprite::create();
        panel16 = cocos2d::Sprite::create();

        spriteArray.push_back(panel10);
        spriteArray.push_back(panel11);
        spriteArray.push_back(panel12);
        spriteArray.push_back(panel13);
        spriteArray.push_back(panel14);
        spriteArray.push_back(panel15);
        spriteArray.push_back(panel16);
    }
    
    // mode 5
    if(mode > 4)
    {
        panel17 = cocos2d::Sprite::create();
        panel18 = cocos2d::Sprite::create();
        panel19 = cocos2d::Sprite::create();
        panel20 = cocos2d::Sprite::create();
        panel21 = cocos2d::Sprite::create();
        panel22 = cocos2d::Sprite::create();
        panel23 = cocos2d::Sprite::create();
        panel24 = cocos2d::Sprite::create();
        panel25 = cocos2d::Sprite::create();
        
        spriteArray.push_back(panel17);
        spriteArray.push_back(panel18);
        spriteArray.push_back(panel19);
        spriteArray.push_back(panel20);
        spriteArray.push_back(panel21);
        spriteArray.push_back(panel22);
        spriteArray.push_back(panel23);
        spriteArray.push_back(panel24);
        spriteArray.push_back(panel25);
    }

}

bool Game::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event)
{
    auto sprite = event->getCurrentTarget();
    Point s = touch->getLocation();
    CCLOG("TouchBegin x => %f  y => %f tag is %d", s.x, s.y, sprite->getTag());

    whichPanel(s);
    
    return true;
}

void Game::whichPanel(Point s)
{
    
    if(panel1->boundingBox().containsPoint(s))
    {
        playerPanelAdd(1);
    }
    else if(panel2->boundingBox().containsPoint(s))
    {
        playerPanelAdd(2);
    }
    else if(panel3->boundingBox().containsPoint(s))
    {
        playerPanelAdd(3);
    }
    else if(panel4->boundingBox().containsPoint(s))
    {
        playerPanelAdd(4);
    }
    else if(panel5->boundingBox().containsPoint(s))
    {
        playerPanelAdd(5);
    }
    else if(panel6->boundingBox().containsPoint(s))
    {
        playerPanelAdd(6);
    }
    else if(panel7->boundingBox().containsPoint(s))
    {
        playerPanelAdd(7);
    }
    else if(panel8->boundingBox().containsPoint(s))
    {
        playerPanelAdd(8);
    }
    else if(panel9->boundingBox().containsPoint(s))
    {
        playerPanelAdd(9);
    }
    else if(mode > 3 && panel10->boundingBox().containsPoint(s))
    {
        playerPanelAdd(10);
    }
    else if(mode > 3 && panel11->boundingBox().containsPoint(s))
    {
        playerPanelAdd(11);
    }
    else if(mode > 3 && panel12->boundingBox().containsPoint(s))
    {
        playerPanelAdd(12);
    }
    else if(mode > 3 && panel13->boundingBox().containsPoint(s))
    {
        playerPanelAdd(13);
    }
    else if(mode > 3 && panel14->boundingBox().containsPoint(s))
    {
        playerPanelAdd(14);
    }
    else if(mode > 3 && panel15->boundingBox().containsPoint(s))
    {
        playerPanelAdd(15);
    }
    else if(mode > 3 && panel16->boundingBox().containsPoint(s))
    {
        playerPanelAdd(16);
    }
    else if(mode > 4 && panel17->boundingBox().containsPoint(s))
    {
        playerPanelAdd(17);
    }
    else if(mode > 4 && panel18->boundingBox().containsPoint(s))
    {
        playerPanelAdd(18);
    }
    else if(mode > 4 && panel19->boundingBox().containsPoint(s))
    {
        playerPanelAdd(19);
    }
    else if(mode > 4 && panel20->boundingBox().containsPoint(s))
    {
        playerPanelAdd(20);
    }
    else if(mode > 4 && panel21->boundingBox().containsPoint(s))
    {
        playerPanelAdd(21);
    }
    else if(mode > 4 && panel22->boundingBox().containsPoint(s))
    {
        playerPanelAdd(22);
    }
    else if(mode > 4 && panel23->boundingBox().containsPoint(s))
    {
        playerPanelAdd(23);
    }
    else if(mode > 4 && panel24->boundingBox().containsPoint(s))
    {
        playerPanelAdd(24);
    }
    else if(mode > 4 && panel25->boundingBox().containsPoint(s))
    {
        playerPanelAdd(25);
    }
}

void Game::playerPanelAdd(int panel)
{
    if (totalMoves < mode * mode)
    {
        totalMoves++;
        if (!playerOne.isTaken(panel) && !playerTwo.isTaken(panel))
        {
            if (playerMove == 1)
            {
                playerOne.panelAdd(panel);
                CCLOG("%s", playerOne.toString().c_str());
                if (playerOne.didWin())
                {
                    CCLOG("P1 WINS");
                    totalMoves = 99;
                }
                else if (totalMoves == mode * mode)
                {
                    CCLOG("TIE");
                    totalMoves = 99;
                }
                else
                {
                    switchTurns();
                    setDisplayOpacity();
                }
            }
            else
            {
                playerTwo.panelAdd(panel);
                CCLOG("%s", playerTwo.toString().c_str());
                if (playerTwo.didWin())
                {
                    CCLOG("P2 WINS");
                    totalMoves = 99;
                }
                else if (totalMoves == mode * mode)
                {
                    CCLOG("TIE");
                    totalMoves = 99;
                }
                else
                {
                    switchTurns();
                    setDisplayOpacity();
                }
            }
        }
    }
}

void Game::switchTurns()
{
    // Switch to players turn
    if(playerMove == 1) playerMove = 2;
    else playerMove = 1;
}

void Game::setDisplayOpacity()
{
    if(playerMove == 1)
    {
        labelTwo->setOpacity(128);
        labelTwoBackground->setOpacity(128);
        labelOne->setOpacity(255);
        labelOneBackground->setOpacity(255);
    }
    else
    {
        labelOne->setOpacity(128);
        labelOneBackground->setOpacity(128);
        labelTwo->setOpacity(255);
        labelTwoBackground->setOpacity(255);
    }
}

void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}