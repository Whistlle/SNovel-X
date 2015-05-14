/**
*
*  You can modify and use this source freely
*  only for the development of application related Live2D.
*
*  (c) Live2D Inc. All rights reserved.
*/
#include "TestScene.h"
#include "ScriptEngine.h"
#include "L2DPart\LAppView.h"
#include "L2DPart\LAppLive2DManager.h"
#include "L2DPart\LAppDefine.h"
#include "AVGDialogBox.h"
#include "TwoStateButton.h"
#include "TextBoxesManager.h"

USING_NS_CC;

Scene* TestScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
	bool bRet = false;
	do
	{

		//////////////////////////////
		// 1. super init first
		CC_BREAK_IF(!Layer::init());


		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();


		//background
		Sprite* pSprite = Sprite::create("back_class_normal.png");

		pSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		pSprite->setScale(2);

		this->addChild(pSprite, 0);

		// L2dModell
		auto pLive2DSprite = LAppView::createDrawNode();
		this->addChild(pLive2DSprite);
		
		auto textbox = AVGDialogBox::create();
		textbox->setPosition(Point::ZERO);
		this->addChild(textbox,1);

		auto namebox = NameTextBox::create();
		textbox->setPosition(Point::ZERO);
		textbox->addChild(namebox, 1);

		TextBoxesManager::getInstance()->add(textbox, "TextBox", TextBoxType::MAIN);
		TextBoxesManager::getInstance()->add(namebox, "TextBox_Name", TextBoxType::OTHER);

		auto winSize = Director::getInstance()->getWinSize();
		//Òþ²Ø°´Å¥
		auto hideBtn = HideButton::create(std::bind(&AVGDialogBox::hideBtnCallback, textbox));
		hideBtn->setPosition(Point(winSize.width - 60, 60));
		hideBtn->setName("hideBtn");
		this->addChild(hideBtn, 2);

		ScriptEngine::getInstance()->loadScript("text1.sov");
		bRet = true;
	} while (0);
	return bRet;
}

void TestScene::onEnter()
{
	Layer::onEnter();
	
	ScriptEngine::getInstance()->RunScript();
}

