#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "base\CCVector.h"
#include "base\CCRef.h"
#include "Tags\AbstractTag.h"
//#include "ScriptEngine\ScriptEngine.h"

using std::string;

using std::unordered_map;

using cocos2d::Vector;

namespace SNovel
{
	class ScriptEngine;
	/*
	* 一个场景类
	* 一个游戏中可以有多个场景但是运行中的只有一个
	* 压栈
	*/
	class Chapter: public cocos2d::Ref
	{
	public:
		struct ChapterStatus
		{
		private:
			
			
		public:
			ChapterStatus() = default;
			bool SkipThisTag = false;
			bool EnableClickContinue = true;
			bool EnableNextCommand = true;
			//bool skipThisTag() const			{ return _skipThisTag; }
			//bool enableClickContinue() const	{ return _enableClickContinue; }
			//bool enableNextCommand() const		{ return _enableNextCommand; }
			void reset()
			{
				SkipThisTag = false;
				EnableClickContinue = true;
				EnableNextCommand = true;
			}
		};

	public:
		Chapter(const string& scriptPath);
		
		void phraseScript();

		void addCommand(AbstractTag* tag);

		const string&  getName() const { return _name; }
		const Vector<AbstractTag*>& getTags() const { return _tags; }
		const string& getCurrentScenario() const { return _currentScenario; }
		const string& getScriptContent() const { return _scriptContent; }
		const unordered_map<string, int>& getScenarioDict()  const { return _scenarioDict; }
		
		ChapterStatus Status;
		string ScriptFilePath;
		bool IsPhraseFinish;
		int CurrentLine;		
	private:
		string _name;
		
		string _currentScenario;

		string _scriptContent;

		ScriptEngine* _engine;
		unordered_map<string, int> _scenarioDict;
		Vector<AbstractTag*> _tags;

		Chapter();

		void phraseFinish()
		{
			IsPhraseFinish = true;
		}

		void loadScript();

		void loadScriptAsync();

		void addScenario(AbstractTag* tag);

		int getLastedTagLineNo();
	};
}