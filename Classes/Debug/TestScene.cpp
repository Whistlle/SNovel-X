#include "TestScene.h"

#ifdef TEST_SCENE



USING_NS_CC;

namespace SNovel
{
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


			Size winSize = Director::getInstance()->getWinSize();
			Point origin = Director::getInstance()->getVisibleOrigin();

			//color layer
			auto layercolor = LayerColor::create(Color4B::BLACK);
			layercolor->setOpacity(40);
			layercolor->setContentSize(winSize);
			layercolor->setPosition(winSize / 2);
			this->addChild(layercolor);

			//ui textbox
			auto text = ui::Text::create("", "font/msjh.ttc", 30);
			text->setPosition(Point(winSize.width / 2.0, winSize.height * 3.0 / 4 + 40));
			text->setColor(Color3B::WHITE);
			auto textbox = new TextBox(text, true);

			//ui name box
			auto name = ui::Text::create("", "font/msjh.ttc", 10);
			name->setPosition(Point(winSize.width / 2.0, winSize.height * 4));
			name->setColor(Color3B::WHITE);
			auto namebox = new TextBox(text, true);
			
			this->addChild(text);
			this->addChild(name);

			//TODO: 加入场景的方式？
			TextBoxesManager::getInstance()->add(textbox, "main", TextBoxesManager::TextBoxType::MAIN);
			TextBoxesManager::getInstance()->add(namebox, "name", TextBoxesManager::TextBoxType::OTHER);

			//一堆chapter并行编译？
			_chapter = new Chapter("NovelPart/ChapterScripts/test2.sov");
			_chapter->phraseScript();

			ImageManager::getInstance()->BgRoot = this;
			bRet = true;
		} while (0);
		return bRet;
	}

	void TestScene::onEnter()
	{
		Layer::onEnter();

		ScriptEngine::getInstance()->run(_chapter);
	}
}
#endif