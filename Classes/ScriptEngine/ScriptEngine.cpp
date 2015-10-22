#include "ScriptEngine.h"
#include "KAGPhraser.h"

#if defined(TEST_SCRIPT_ENGINE) \
||  defined(DEBUG_ALL)

#define TEST_SCRIPTED_ENGINE

USING_NS_CC;

namespace SNovel
{
	static ScriptEngine* _sharedEngine = nullptr;

	ScriptEngine::ScriptEngine()
	{
		//init gameNode
		_gameNode = Node::create();
		_gameNode->retain();

		auto listener = EventListenerCustom::create("EVENT_SCRIPT_CONTINUE",
													CC_CALLBACK_1(ScriptEngine::onClickContinue, this));

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	}

	ScriptEngine::~ScriptEngine()
	{
		//delete _phraser;
	}

	ScriptEngine* ScriptEngine::getInstance()
	{
		if (!_sharedEngine)
		{
			_sharedEngine = new ScriptEngine();
		}
		return _sharedEngine;
	}

	void ScriptEngine::jumpToScenario(string scenarioName)
	{
		auto& dict = _currentChapter->getScenarioDict();
		if (dict.find(scenarioName) != dict.end())
		{
			Debug::logFormat("JumpTo line:%d:%s", dict.find(scenarioName), scenarioName);
			int line = dict.find(scenarioName)->second;
			_currentChapter->CurrentLine = line;
			_currentChapter->Status.EnableClickContinue = true;
			_currentChapter->Status.EnableNextCommand = true;
		}
		else
		{
			Debug::logFormat("Do not have scenario:%s", scenarioName);
		}
	}

	void ScriptEngine::run(RefPtr<Chapter> scene)
	{
		_currentChapter = scene;
		Debug::log("Run Script");
		onRun();
	}

	//每帧执行: 改成事件驱动
	void ScriptEngine::onRun()
	{
		auto& tags = _currentChapter->getTags();
		if (_currentChapter->CurrentLine < tags.size())
		{
			if (_currentChapter->Status.EnableNextCommand)
				excuteCommand();
		}
	}

	void ScriptEngine::nextCommand()
	{
		_currentChapter->CurrentLine++; 
		onRun();
	}
	/*
	void ScriptEngine::onContinue(EventCustom* pEvent)
	{
		if (_hideTextBox && _hasTextBoxToHide)
		{
			_hideTextBox = true;
			_hasTextBoxToHide = false;
			EventCustom e("EVENT_HIDE_TEXTBOX");
			e.setUserData("TextBox_Name");
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		}
		_hasTextBoxToHide = false;
		nextLine();

	}*/
	void ScriptEngine::excuteCommand()
	{
		_currentChapter->Status.SkipThisTag = false;

		int currentLine = _currentChapter->CurrentLine;
		auto& tags = _currentChapter->getTags();

		if (currentLine < tags.size())
		{
			tags.at(currentLine)->before();
			if (!_currentChapter->Status.SkipThisTag)
			{
				_currentChapter->Status.EnableNextCommand = true;
				tags.at(currentLine)->excute();
				tags.at(currentLine)->after();
			}
		}
	}
	/*
	void ScriptEngine::onWaitTouch()
	{
		_waitTouch = true;
	}*/

	void ScriptEngine::onClickContinue(EventCustom* pEvent)
	{
		if (_currentChapter->Status.EnableClickContinue)
		{
			//_currentChapter->CurrentLine++;
			_currentChapter->Status.EnableNextCommand = true;
			nextCommand();
		}
	}

}
#endif