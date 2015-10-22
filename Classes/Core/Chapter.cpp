#include "Chapter.h"
#include "ScriptEngine\KAGPhraser.h"
#include "ScriptEngine\ScriptEngine.h"
#include "CCFileUtils.h"

using cocos2d::FileUtils;

namespace SNovel
{
	Chapter::Chapter()
	{
		ScriptFilePath = "";
		_scriptContent = "";
		CurrentLine = 0;

		_engine = ScriptEngine::getInstance();
		IsPhraseFinish = false;
	}

	Chapter::Chapter(const string& scriptPath) : Chapter()
	{
		ScriptFilePath = scriptPath;
		_name = scriptPath;
	}
	
	void Chapter::phraseScript()
	{
		loadScript();
		KAGPhraser::getInstance()->phrase(this);
	}
	void Chapter::addCommand(AbstractTag* tag)
	{
		tag->Engine = _engine;
		if (tag->getName() == "scenario")
		{
			addScenario(tag);
		}
		else
		{
			_tags.pushBack(tag);
		}
	}

	void Chapter::loadScript()
	{
#if CC_PLATFORM_WIN32
		
#endif // WINDOWS
#if CC_PLATFORM_ANDROID
		
#endif // ANDROID
#if CC_PLATFORM_IOS

#endif // IOS
		_scriptContent = FileUtils::getInstance()->getStringFromFile(ScriptFilePath);
		if (_scriptContent.empty())
		{
			CCLOG("can not find script file:%s", ScriptFilePath);
		}
	}

	void Chapter::loadScriptAsync()
	{

	}

	void Chapter::addScenario(AbstractTag* tag)
	{
		string scenarioName = tag->Params["scenario"].asString();
		if (_scenarioDict.find(scenarioName) != _scenarioDict.end())
		{
			Debug::logFormat("Scenario: %s.Is Already Exist", scenarioName);
			return;
		}
		else
		{
			_scenarioDict[scenarioName] = getLastedTagLineNo();
			Debug::logFormat("[Add Scenario]%d:%s", getLastedTagLineNo(), scenarioName);
			_currentScenario = scenarioName;
		}
	}

	int Chapter::getLastedTagLineNo()
	{
		return _tags.size();
	}
}