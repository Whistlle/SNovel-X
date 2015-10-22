#include "TextDisplay.h"
#include "ScriptEngine\ScriptEngine.h"

#if defined(TEST_TEXT_DISPLAY) 

namespace SNovel
{
	TextDisplay::TextDisplay(ui::Text* uiText)
		: _uiText(uiText)
	{
		_uiText->retain();
		_state = State::Waiting;
	}

	TextDisplay::~TextDisplay()
	{
		_uiText->release();
	}

	void TextDisplay::startEffect(std::string& oldText, std::string& appendText, float showSpeed)
	{
		if (oldText.empty())
		{
			//init
			_renderingText.clear();
			_appendText = appendText;
			_currentShowCharIter = _appendText.begin();
		}
		else
		{
			_renderingText = oldText;
			_appendText = appendText;
			_currentShowCharIter = _appendText.begin();
		}
		_allText = oldText + appendText;
		_state = State::Rendering;
		_uiText->schedule(std::bind(&TextDisplay::doingEffect, this, std::placeholders::_1), showSpeed, "textRendering");
	}
	
	void TextDisplay::displayTextRemain()
	{
		_uiText->unschedule("textRendering");
		_renderingText = _allText;
		_uiText->setText(_allText);
		displayFinish();
	}

	//run per showSpeed seconds
	void TextDisplay::doingEffect(float dt)
	{
		//一次显示1个字 汉字占2个字符
		int showCharOnce = 1;
		if (_currentShowCharIter != _appendText.end())
		{
			_renderingText.append(_currentShowCharIter, _currentShowCharIter + 1);
			_uiText->setText(_renderingText);
			++_currentShowCharIter;
		}
		else
		{
			displayFinish();
		}
	}

	void TextDisplay::displayFinish()
	{
		_state = State::Waiting;
		_uiText->unschedule("textRendering");
		//消息传递?
		ScriptEngine::getInstance()->nextCommand();
	}
}

#endif