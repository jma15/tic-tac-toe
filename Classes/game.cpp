#include "Player.h"
#include "game.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

int mode; // game mode size of board (3, 4, 5)
int matchesToWin; // matches in a row to win
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
    origin = Director::getInstance()->getVisibleOrigin();

    // background sprite
    auto background_sprite = Sprite::create("tic-tac-toe_background_game.png");
    background_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background_sprite, 0);

    // grid overlay sprite
    auto grid_sprite = Sprite::create("tic-tac-toe_3x3_grid.png");
    switch (mode)
    {
    case 3:
        break;
    case 4:
        grid_sprite = Sprite::create("tic-tac-toe_4x4_grid.png");
        break;
    case 5:
        grid_sprite = Sprite::create("tic-tac-toe_5x5_grid.png");
        break;
    default:
        CCLOG("ERROR: Defaulted to 3x3 grid. Invalid game mode encountered.");
    }
    grid_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(grid_sprite, 0);

    // set matches to win and create players
    switch (mode)
    {
    case 3:
        matchesToWin = 3;
        break;
    case 4: case 5: matchesToWin = 4;
        break;
    default:
        matchesToWin = 3;
        CCLOG("Invalid game mode. Matches to win set to 3.");
    }

    playerOne = Player(mode, matchesToWin);
    playerTwo = Player(mode, matchesToWin);

    //std::string gameModeString = "The game is " + std::to_string(mode);

    //auto label = Label::createWithTTF(gameModeString, "fonts/Marker Felt.ttf", 32);
    //label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //this->addChild(label);
    
    // Declare the gameWon as 0
    gameWon = 0;

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
    button->setPosition(Point(visibleSize.width * 0.9 + origin.x, visibleSize.height * 0.05 + origin.y));
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
    // declare percentage
    float labelOnePositionX = origin.x;
    float labelOnePositionY = visibleSize.height*0.90f + origin.y;
    float labelTwoPositionX = visibleSize.width*0.81f + origin.x;
    float labelTwoPositionY = visibleSize.height*0.90f + origin.y;
    float labelWidth = visibleSize.width * 0.19f + origin.x;
        
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
    float boardSizeEndx = visibleSize.width * 0.8f + origin.x;
    float boardSizeStartx = visibleSize.width * 0.2f + origin.x;
    float boardSizex = boardSizeEndx - boardSizeStartx;
    // 10% gap between each panel
    float gapx = (boardSizex / mode)*0.20f;
    float panelWidthx = boardSizex / mode - gapx;

    // Use 80% of screen
    float boardSizeEndy = visibleSize.height * 0.8f + origin.y;
    float boardSizeStarty = visibleSize.height * 0.2f + origin.y;
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
            //spriteArray[value]->setAnchorPoint(Vec2(0, 0));
            spriteArray[value]->setPosition(boardSizeStartx + (panelWidthx + gapx)*i + spriteArray[i]->getContentSize().width/2, boardSizeStarty + (panelHeight + gapy)*j + spriteArray[j]->getContentSize().height/2);
            spriteArray[value]->setOpacity(0);
            //CCLOG("position is %f", spriteArray[i]->getPositionX());
            this->addChild(spriteArray[value]);
        }
    }
}

void Game::gameMode()
{
    for(int i = 0; i < (mode*mode); i++)
    {
        cocos2d::Sprite* tempPanel = cocos2d::Sprite::create();
        spriteArray.push_back(tempPanel);
    }
}

bool Game::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event *event)
{
    auto sprite = event->getCurrentTarget();
    Point s = touch->getLocation();

    whichPanel(s);
    return true;
}

void Game::whichPanel(Point s)
{
    
    if(spriteArray[0]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(1);
    }
    else if(spriteArray[1]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(2);
    }
    else if(spriteArray[2]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(3);
    }
    else if(spriteArray[3]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(4);
    }
    else if(spriteArray[4]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(5);
    }
    else if(spriteArray[5]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(6);
    }
    else if(spriteArray[6]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(7);
    }
    else if(spriteArray[7]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(8);
    }
    else if(spriteArray[8]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(9);
    }
    else if(mode > 3 && spriteArray[9]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(10);
    }
    else if(mode > 3 && spriteArray[10]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(11);
    }
    else if(mode > 3 && spriteArray[11]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(12);
    }
    else if(mode > 3 && spriteArray[12]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(13);
    }
    else if(mode > 3 && spriteArray[13]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(14);
    }
    else if(mode > 3 && spriteArray[14]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(15);
    }
    else if(mode > 3 && spriteArray[15]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(16);
    }
    else if(mode > 4 && spriteArray[16]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(17);
    }
    else if(mode > 4 && spriteArray[17]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(18);
    }
    else if(mode > 4 && spriteArray[18]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(19);
    }
    else if(mode > 4 && spriteArray[19]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(20);
    }
    else if(mode > 4 && spriteArray[20]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(21);
    }
    else if(mode > 4 && spriteArray[21]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(22);
    }
    else if(mode > 4 && spriteArray[22]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(23);
    }
    else if(mode > 4 && spriteArray[23]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(24);
    }
    else if(mode > 4 && spriteArray[24]->boundingBox().containsPoint(s))
    {
        playerPanelAdd(25);
    }
}

void Game::playerPanelAdd(int panel)
{
    // If the game is over, do not do anything on panel click
    if(checkGameOver()) return;
    
    // Add the panel to the player
    if (totalMoves < mode * mode)
    {
        if (!playerOne.isTaken(panel) && !playerTwo.isTaken(panel))
        {
            totalMoves++;
            if (playerMove == 1)
            {
                playerOne.panelAdd(panel);
                setPanelMarker(panel, 1);
                CCLOG("%s", playerOne.toString().c_str());
                if (playerOne.didWin(panel))
                {
                    CCLOG("P1 WINS");
                    totalMoves = 99;
                    gameWon = 1;
                    showWinStatus();
                    for (int i = 0; i < matchesToWin; i++)
                    {
                        firePosition = Vec2(spriteArray[playerOne.getWinningCombo()[i] - 1]->getPosition());
                        fireArray.push_back(firePosition);
                        //CCLOG("Postition is %f and %f", firePosition.x, firePosition.y);
                        this->schedule( schedule_selector(Game::setFire), 1.0f );
                        //CCLOG("%lu", playerOne.getWinningCombo()[i]);
                    }
                }
            }
            else if (playerMove == 2)
            {
                playerTwo.panelAdd(panel);
                setPanelMarker(panel, 2);
                CCLOG("%s", playerTwo.toString().c_str());
                if (playerTwo.didWin(panel))
                {
                    CCLOG("P2 WINS");
                    totalMoves = 99;
                    gameWon = 2;
                    showWinStatus();
                    for (int i = 0; i < matchesToWin; i++)
                    {
                        firePosition = Vec2(spriteArray[playerTwo.getWinningCombo()[i] - 1]->getPosition());
                        fireArray.push_back(firePosition);
                        //CCLOG("Postition is %f and %f", firePosition.x, firePosition.y);
                        this->schedule( schedule_selector(Game::setFire), 1.0f );
                        //CCLOG("%lu", playerTwo.getWinningCombo()[i]);
                    }
                }
            }

            if (totalMoves == mode * mode)
            {
                CCLOG("TIE");
                totalMoves = 99;
                slideIn();
            }
            else if (totalMoves < mode * mode)
            {
                
                // Animate panel
                changePanel(panel-1);
                
                switchTurns();
                setDisplayOpacity();
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
    else if(playerMove == 2)
    {
        labelOne->setOpacity(128);
        labelOneBackground->setOpacity(128);
        labelTwo->setOpacity(255);
        labelTwoBackground->setOpacity(255);
    }
}

void Game::changePanel(int panel)
{
    // creates orbit camera for flipping
    OrbitCamera* camera = cocos2d::OrbitCamera::create(1.0f, 1, 0, 0.0f, 720.0f, 0, 0);
    auto seq = Sequence::create(camera, nullptr);
    // add rotation to panel
    spriteArray[panel]->runAction(seq);
}

bool Game::checkGameOver()
{
    // if game is not over, return false
    if(gameWon == 0) return false;
    
    return true;
}


void Game::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::setPanelMarker(int panel, int player)
{
    std::string texture;
    switch (mode)
    {
    case 3:
        if (player == 1) texture = "tic-tac-toe_3x3_x.png";
        else texture = "tic-tac-toe_3x3_o.png";
        break;
    case 4:
        if (player == 1) texture = "tic-tac-toe_4x4_x.png";
        else texture = "tic-tac-toe_4x4_o.png";
        break;
    case 5:
        if (player == 1) texture = "tic-tac-toe_5x5_x.png";
        else texture = "tic-tac-toe_5x5_o.png";
        break;
    default:
        CCLOG("Invalid game mode %lu. Panel marker fail.", panel);
    }

    spriteArray[panel - 1]->setTexture(texture);
    spriteArray[panel - 1]->setOpacity(255);
}

void Game::setFire(float dt)
{
    //CCLOG("Fire! position is %f and %f", firePosition.x, firePosition.y);
    CCParticleFire* fire = CCParticleFire::create();
    fire->setLife(0.5);
    fire->setBlendFunc(BlendFunc::ALPHA_PREMULTIPLIED);
    fire->setStartColor(Color4F(1.0, 1.0, 0.76, 0.5));
    fire->setEndColor(Color4F(0.93, 0.27, 0.03, 0.4));

    fire->setPosition(fireArray[0]);
    fireArray.erase(fireArray.begin());
    if(fireArray.size() <= 0) this->unschedule( schedule_selector(Game::setFire));
    this->addChild(fire);
}

// Win Animation after someone Wins
void Game::showWinStatus()
{
    // Slide out the correct side first
    slideOut();
    
    // Set basic variables
    std::string gameName = "";
    Color3B color = Color3B(0,0,0);
    int topHeight = visibleSize.height*0.9f;
    float positionX = 0;
    float positionXBackground = 0;
    float positionXLabel = 0;
    float movePosition = 0;
    
    if(gameWon == 1)
    {
        gameName = "PLAYER 1 WINS";
        color = Color3B(0, 128, 0);
        positionXBackground = -(visibleSize.width - labelOne->getContentSize().width);
        
    }
    else if(gameWon == 2)
    {
        gameName = "PLAYER 2 WINS";
        color = Color3B(255, 0, 0);
        positionXBackground = visibleSize.width - labelTwo->getContentSize().width;
        
    }

    // reset the string
    winLabel = Label::createWithTTF(gameName, "fonts/Marker Felt.ttf",32);
    
    // create background color
    winLabelBackground = cocos2d::Sprite::create();
    winLabelBackground->setTextureRect(Rect(0.0, 0.0, visibleSize.width, visibleSize.height*0.1f));
    winLabelBackground->setAnchorPoint(Vec2(0,0));
    winLabelBackground->setPosition(positionXBackground, topHeight);
    winLabelBackground->setColor(color);
    this->addChild(winLabelBackground);
    
    // Move winLabel Background
    auto moveTo = MoveTo::create(2, Vec2(0, topHeight));
    winLabelBackground->runAction(moveTo);

    winLabel->setAnchorPoint(Vec2(0, 0));
    positionX = (visibleSize.width - winLabel->getContentSize().width)/2;
    
    // Set more variables after
    if(gameWon == 1)
    {
        // position of the label to start with
        positionXLabel = -positionX;
        
        // move it to the right
        movePosition = visibleSize.width - winLabel->getContentSize().width;
    }
    else if (gameWon == 2)
    {
        // position of the label to start with
        positionXLabel = positionX + visibleSize.width;
        
        // move it to the left
        movePosition = -visibleSize.width;
    }
    winLabel->setPosition(positionXLabel, topHeight);
    
    this->addChild(winLabel);
    
    auto moveToLabel = MoveBy::create(2, Vec2(movePosition, 0));
    winLabel->runAction(moveToLabel);
    
    // Ending Remove the previous displays
    removeChild(labelTwo);
    removeChild(labelTwoBackground);
    removeChild(labelOne);
    removeChild(labelOneBackground);
    
}

// Win Animation after someone Wins
void Game::slideOut()
{
    
    // slide depending on who won the game
    if(gameWon == 2)
    {
        // slide out the top labels
        auto moveToLabelLeft = MoveBy::create(2, Vec2(-visibleSize.width, 0));
        labelOne->runAction(moveToLabelLeft);
        auto moveToLabelLeftB = MoveBy::create(2, Vec2(-visibleSize.width, 0));
        labelOneBackground->runAction(moveToLabelLeftB);
    }
    else if(gameWon == 1)
    {
        auto moveToLabelRight = MoveBy::create(2, Vec2(visibleSize.width, 0));
        labelTwo->runAction(moveToLabelRight);
        auto moveToLabelRightB = MoveBy::create(2, Vec2(visibleSize.width, 0));
        labelTwoBackground->runAction(moveToLabelRightB);
    }
}

// This is for TIE
void Game::slideIn()
{
    // Reset all the opacity regardless who went last
    labelTwo->setOpacity(255);
    labelTwoBackground->setOpacity(255);
    labelOne->setOpacity(255);
    labelOneBackground->setOpacity(255);
    
    // reset new label to longer length
    labelOneBackground->setTextureRect(Rect(0.0, 0.0, visibleSize.width/2, visibleSize.height*0.9f));
    // Set the position a little back
    float positionX = labelOneBackground->getContentSize().width - labelOne->getContentSize().width;
    labelOneBackground->setPosition(Vec2(-positionX,visibleSize.height*0.9f));
    // Move it to the right
    auto moveToLabelRight = MoveTo::create(2, Vec2(0, visibleSize.height*0.9f));
    labelOneBackground->runAction(moveToLabelRight);
    
    // reset new label to longer length
    labelTwoBackground->setTextureRect(Rect(0.0, 0.0, visibleSize.width/2, visibleSize.height*0.9f));
    // Set the position a little back
    positionX = labelTwoBackground->getContentSize().width + labelTwo->getContentSize().width;
    labelTwoBackground->setPosition(Vec2(positionX,visibleSize.height*0.9f));
    // Move it to the right
    auto moveToLabelLeft = MoveTo::create(2, Vec2(visibleSize.width/2, visibleSize.height*0.9f));
    labelTwoBackground->runAction(moveToLabelLeft);
}

