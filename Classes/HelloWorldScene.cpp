#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// background sprite
	auto background_sprite = Sprite::create("tic-tac-toe_background.png");
	background_sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background_sprite, 0);

	// title sprite
	auto title_sprite = Sprite::create("tic-tac-toe_title.png");
	title_sprite->setPosition(Vec2(origin.x, origin.y + (visibleSize.height / 6) * 5));
	this->addChild(title_sprite, 0);

	// title action
	auto title_action = MoveBy::create(0.5, Vec2(visibleSize.width / 2, 0));
	title_sprite->runAction(title_action);

	// menu items
	auto menu_item_1 = MenuItemFont::create("play 3x3 game", CC_CALLBACK_1(HelloWorld::play_3x3, this));
	auto menu_item_2 = MenuItemFont::create("play 4x4 game", CC_CALLBACK_1(HelloWorld::play_4x4, this));
	auto menu_item_3 = MenuItemFont::create("play 5x5 game", CC_CALLBACK_1(HelloWorld::play_5x5, this));
	auto menu_item_4 = MenuItemFont::create("quit game", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	menu_item_1->setColor(Color3B(0, 0, 0));
	menu_item_2->setColor(Color3B(0, 0, 0));
	menu_item_3->setColor(Color3B(0, 0, 0));
	menu_item_4->setColor(Color3B(0, 0, 0));

	menu_item_1->setFontNameObj("8514oem");
	menu_item_2->setFontNameObj("8514oem");
	menu_item_3->setFontNameObj("8514oem");
	menu_item_4->setFontNameObj("8514oem");

	// create menu, it's an autorelease object
	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, NULL);
	menu->setPositionY(origin.y + (visibleSize.height / 2.25));
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::play_3x3(Ref* pSender)
{
    CCLOG("play_3x3");
    auto scene = Game::createScene();
    Director::getInstance( )->replaceScene(scene);
}

void HelloWorld::play_4x4(Ref* pSender)
{
	CCLOG("play_4x4");
}

void HelloWorld::play_5x5(Ref* pSender)
{
	CCLOG("play_5x5");
}