#pragma once
#include "TestMacro.h"

#if defined(TEST_SCRIPT_ENGINE) \
	|| defined(DEBUG_ALL)
#define TEST_SCRIPT_ENGINE


#include "OpCode.h"
#include "OpCommand.h"
#include <deque>
#include "cocos2d.h"
#include "KAGPhraser.h"
USING_NS_CC;

class ScriptEngine: public Node
{
public:
	virtual bool init();
	static ScriptEngine* getInstance();
	void addCommand(OpCommand op);
	void loadScript(const char* file);
	void RunScript();

	bool isWaitTouch() { return _waitTouch; }
private:
	ScriptEngine();
	void resetEngine();

	void nextLine();
	std::deque<OpCommand> _opLines;
	std::deque<OpCommand> _scenarioLines;

	int getLastedLineID();

	int _currentLine;
	int _currentScenario;
	
	bool _waitTouch = false;
	bool _hideTextBox = true;

	bool _hasTextBoxToHide = false;
	KAGPhraser* _phraser;
	void onContinue(EventCustom* pEvent);
	void onCommandFinish(EventCustom* pEvent);
	void onWaitTouch();
};
#endif