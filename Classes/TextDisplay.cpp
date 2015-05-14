#include "TextDisplay.h"

#if defined(TEST_TEXT_DISPLAY) \
	|| defined(DEBUG_ALL)



TextDisplay* TextDisplay::create(bool useEffect, const TTFConfig& textConfig)
{
	auto pRet = new TextDisplay();
	if (pRet && pRet->init(useEffect, textConfig)){
		pRet->autorelease();
	}
	else{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

TextDisplay* TextDisplay::create(bool useEffect, const TTFConfig& textConfig, const Size& size)
{
	auto pRet = new TextDisplay();
	if (pRet && pRet->init(useEffect, textConfig, size)){
		pRet->autorelease();
	}
	else{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}
bool TextDisplay::init(bool useEffect, const TTFConfig& config)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		_isUseEffect = useEffect;

		//_textBox = textBox;
	
		auto winSize = Director::getInstance()->getVisibleSize();

		//textConfig = TTFConfig("fonts/msyh.ttf", 38);
		textConfig = config;
		//_displayedText = Label::createWithTTF(c, "");
		_displayedText = Label::createWithTTF(textConfig, "");
		CC_ASSERT(_displayedText != nullptr);

		_displayedText->setAnchorPoint(Point(0, 1));
		_displayedText->setTextColor(Color4B::BLACK);
		_displayedText->setPosition(Point::ZERO);
	//	resetTextSize();
		this->addChild(_displayedText);
		
		_state = State::STATE_WAIT;
		_progress = 0;
		bRet = true;
	} while (0);
	return bRet;
}

bool TextDisplay::init(bool useEffect, const TTFConfig& textConfig, const Size& dimensionSize)
{
	bool bRet = init(useEffect, textConfig);
	_displayedText->setDimensions(dimensionSize.width, dimensionSize.height);
	return bRet;
}
void TextDisplay::onEnter()
{
	Node::onEnter();
}
/*
void TextDisplay::onDisplayText()
{
	_text = _textBox->getCurrentText();
	onDisplayText(_text);
}*/
void TextDisplay::onDisplayText(std::string text)
{
	_text = text;


	if (_isUseEffect)
	{
		if (State::STATE_WAIT == _state){
			startEffect();
		}
		else if (State::STATE_RENDERING == _state){
			displayTextRemain();
		}
	}
	else
	{
		_displayedText->setString(_text);
		displayFinish();
		//int i = 0;
		//auto letter = _displayedText->getLetter(19);
		//CCLOG("the 24th letter: (%f, %f)", letter->getPosition().x, letter->getPosition().y);
	}
}

void TextDisplay::onDisplayAddedText(std::string text)
{
	_text.push_back('\n');
	_text += text;

	_displayedText->setString(_text);

	for (int i = _lastTextLength ; i < _displayedText->getStringLength(); ++i)
	{
		auto ch = _displayedText->getLetter(i);

	}
	if (_isUseEffect)
	{
		if (State::STATE_WAIT == _state){
			startEffect(_lastTextLength);
		}
		else if (State::STATE_RENDERING == _state){
			displayTextRemain();
		}
	}
	else
	{
		_displayedText->setString(_text);
		displayFinish();
		//int i = 0;
		//auto letter = _displayedText->getLetter(19);
		//CCLOG("the 24th letter: (%f, %f)", letter->getPosition().x, letter->getPosition().y);
	}
}
void TextDisplay::startEffect()
{
	_displayedText->setOpacity(0);
	_state = State::STATE_RENDERING;
	
	//TODO 效率不高 需要重置所有的TTFConfig 还将一个方法改成public
	_displayedText->reset();
	//_displayedText->resetAllLetter();
	_displayedText->setTTFConfig(textConfig);
	_displayedText->setTextColor(Color4B::BLACK);
	//show letter
	_displayedText->setString(_text);
	_progress = 0;
	schedule(schedule_selector(TextDisplay::doingEffect), 0.05f);
	
}

void TextDisplay::startEffect(int startPosition)
{
	_displayedText->setOpacity(0);
	_state = State::STATE_RENDERING;

	//TODO 效率不高 需要重置所有的TTFConfig 还将一个方法改成public
	_displayedText->reset();
	//_displayedText->resetAllLetter();
	_displayedText->setTTFConfig(textConfig);
	_displayedText->setTextColor(Color4B::BLACK);
	//show letter
	_displayedText->setString(_text);
	_progress = startPosition;
	schedule(schedule_selector(TextDisplay::doingEffect), 0.05f);

}
//TODO 淡入效果 文字太长换行
void TextDisplay::doingEffect(float dt)
{
	auto action = FadeIn::create(0.2);
	if (_progress <= _displayedText->getStringLength())
	{
		auto letter = _displayedText->getLetter(_progress);
		//for (int i = 0; i < 2; ++i){
			if (letter){
				letter->runAction(action->clone());
				//CCLOG("the %fth letter: (%f, %f)",_progress,  letter->getPosition().x, letter->getPosition().y);
			}
		//	_progress += 1;
		//}
	}
	else
	{
		unschedule(schedule_selector(TextDisplay::doingEffect));
		displayFinish();
	}
	_progress += 1;
}

void TextDisplay::displayTextRemain()
{
	unschedule(schedule_selector(TextDisplay::doingEffect));
	auto letter = _displayedText->getLetter(_progress);
	auto action = FadeIn::create(0.1);
	while (_progress <= _displayedText->getStringLength())
	{
		auto letter = _displayedText->getLetter(_progress);
		if (letter){
			letter->runAction(action->clone());
		}
		_progress += 1;
	}
	displayFinish();
}

void TextDisplay::displayFinish()
{
	_lastTextLength = (int)_progress;
	_state = State::STATE_WAIT;
	EventCustom e("EVENT_SCRIPT_COMMAND_FINISH");
	CCLOG("Text Display finish");
	_eventDispatcher->dispatchEvent(&e);
}
void TextDisplay::resetTextSize(const Size& size)
{
	_displayedText->setDimensions(size.width, size.height);
}
/*
void TextDisplay::resetTextSize()
{
	auto size = _textBox->getContentSize();
	_displayedText->setDimensions(size.width - 60, size.height - 60);
}*/



#endif