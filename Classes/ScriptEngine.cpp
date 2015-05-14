#include "ScriptEngine.h"

#if defined(TEST_SCRIPT_ENGINE) \
||  defined(DEBUG_ALL)

#define TEST_SCRIPTED_ENGINE


static ScriptEngine* _sharedEngine = nullptr;

ScriptEngine::ScriptEngine():
_currentLine(0),
_currentScenario(0)
{
	init();
}

bool ScriptEngine::init()
{
	Node::init(); 

	_phraser = new KAGPhraser();
	//event_continue:
	//click mouse to continue game 
	auto listener = EventListenerCustom::create("EVENT_SCRIPT_CONTINUE",
		CC_CALLBACK_1(ScriptEngine::onContinue, this));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);


	auto listener1 = EventListenerCustom::create("EVENT_SCRIPT_COMMAND_FINISH",
		CC_CALLBACK_1(ScriptEngine::onCommandFinish, this));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener1, 1); 

	_waitTouch = false;
	return true;
}
ScriptEngine* ScriptEngine::getInstance()
{
	if (!_sharedEngine)
	{
		_sharedEngine = new ScriptEngine();
	}
	return _sharedEngine;
}	

void ScriptEngine::addCommand(OpCommand op)
{
	op.lineID = getLastedLineID();
	
	if (op.op == Opcode::SCENARIO)
		_scenarioLines.push_back(op);

	_opLines.push_back(op);
}

int ScriptEngine::getLastedLineID()
{
	return _opLines.size();
}

void ScriptEngine::loadScript(const char* file)
{
	auto str = FileUtils::getInstance()->getStringFromFile("test1.sov");
	_phraser->setStringStream(str);
	_phraser->phrase();
}
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
	
}
void ScriptEngine::nextLine()
{
	auto command = _opLines.at(_currentLine);
	switch (command.op)
	{
	case Opcode::SCENARIO:
		_currentLine++;
		onContinue(nullptr);
		break;
	case Opcode::MESSAGING://triggerEvent
	{
		auto addiOp = command.additionalOp;
		for (auto it = addiOp.begin(); it != addiOp.end(); ++it)
		{
			if (*it == Opcode::WAIT_TOUCH)
			{
				onWaitTouch();
				command.additionalOp.erase(it);
				break;
			}
		}
		EventCustom e(command.params["eventType"].asString());
		e.setUserData(&command);
		auto success = Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		if (!success)
		{
			CCLOG("event: %s send error! cannot find this tag", command.params["eventType"].asString().c_str());
			++_currentLine;
			onContinue(nullptr);
		}
		break;
	}
	case Opcode::PRINT:
	{
		auto& addiOp = command.additionalOp;
		for (auto& it = addiOp.begin(); it != addiOp.end(); ++it)
		{
			if (*it == Opcode::WAIT_TOUCH)
			{
				addiOp.erase(it);
				onWaitTouch();
				break;
			}
		}
		EventCustom e("EVENT_PRINT");
		e.setUserData(&command);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		break;
	}
	case Opcode::CURRENT:
	{
		EventCustom e("EVENT_CURRENT");
		e.setUserData(&command);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		//	++_currentLine;
		break;
	}
	case Opcode::SET_TEXT:
	{
		auto& addiOp = command.additionalOp;
		_hasTextBoxToHide = true;
		_hideTextBox = true;
		for (auto it = addiOp.begin(); it != addiOp.end(); ++it)
		{
			if (*it == Opcode::RELINE)
			{
				_hideTextBox = false;
				
				addiOp.erase(it);
				break;
			}
		}
			
		EventCustom e("EVENT_SETTEXT");
		e.setUserData(&command);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		break;

	}
	default:
		_currentLine++;
		onContinue(nullptr);
	}

}

void ScriptEngine::onWaitTouch()
{
	_waitTouch = true;
}

void ScriptEngine::onCommandFinish(EventCustom* pEvent)
{
	++_currentLine;
	if (_waitTouch)
	{
		CCLOG("wait touch! Click to continue!");
		_waitTouch = false;
	}
	else
	{
		nextLine();
	}
}

void ScriptEngine::resetEngine()
{
	_currentLine = 0;
	_currentScenario = 0;
	_opLines.clear();
	_scenarioLines.clear();
}

void ScriptEngine::RunScript()
{
	onContinue(nullptr);
}
#endif