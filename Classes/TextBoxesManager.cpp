#include "TextBoxesManager.h"
#if defined(TEST_TEXTBOXES_MANAGER) \
	|| defined(DEBUG_ALL)

#include "cocos2d.h"
#include "OpCommand.h"
#include <string>
USING_NS_CC;

static TextBoxesManager* _sharedTextBoxesManager = nullptr;

TextBoxesManager* TextBoxesManager::getInstance()
{
	if (!_sharedTextBoxesManager)
	{
		_sharedTextBoxesManager = new TextBoxesManager();
	}
	return _sharedTextBoxesManager;
}

TextBoxesManager::TextBoxesManager()
{
	//×¢²á¼àÌýÊÂ¼þ
	auto setTextEventListener = EventListenerCustom::create("EVENT_SETTEXT",
		std::bind(&TextBoxesManager::onSetText, this, std::placeholders::_1));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(setTextEventListener, 1);

	auto printEventListener = EventListenerCustom::create("EVENT_PRINT",
		std::bind(&TextBoxesManager::onPrintText, this, std::placeholders::_1));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(printEventListener, 1);

	auto currentEventListener = EventListenerCustom::create("EVENT_CURRENT",
		std::bind(&TextBoxesManager::onCurrent, this, std::placeholders::_1));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(currentEventListener, 1);

	auto hideMsgbox = EventListenerCustom::create("EVENT_HIDE_TEXTBOX",
		std::bind(&TextBoxesManager::onHideMsgBox, this, std::placeholders::_1));

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(hideMsgbox, 1);
}


void TextBoxesManager::add(TextBox* textBox, const char* textBoxName, TextBoxType type)
{
	switch (type)
	{
	case TextBoxType::MAIN:
		_mainTextBoxes[textBoxName] = textBox;
		break;
	case TextBoxType::OTHER:
		_otherTextBoxes[textBoxName] = textBox;
		break;
	default:
		CCLOG("add TextBox:%s error! wrong type", textBoxName);
	}
}

void TextBoxesManager::onSetText(EventCustom* pEvent)
{
	CCLOG("on Set Text");
	auto data = static_cast<OpCommand*>(pEvent->getUserData());

	auto boxName = data->params["textbox"].asString();
	if (_otherTextBoxes.find(boxName) != _otherTextBoxes.end())
	{
		auto text = data->params["text"].asString();
		auto textbox = _otherTextBoxes[boxName];
		textbox->showTextBox();
		textbox->setText(text);
	}

}

void TextBoxesManager::onPrintText(EventCustom* pEvent)
{
	CCLOG("on Print Text");
	auto data = static_cast<OpCommand*>(pEvent->getUserData());

	if (_currentMainTextBox->isEnterScene() == false)
	{
		_currentMainTextBox->enterScene();
	}
	auto additionalTag = data->additionalOp;
	Opcode tag;
	if (additionalTag.empty() != true)
	{
		tag = additionalTag.at(0);
		
	}
	
	auto text = data->params["text"].asString();
	TextBox::SetTextMode mode;
	switch (tag)
	{
	case Opcode::RELINE:
		CCLOG("TextMode [r]");
		mode = TextBox::SetTextMode::RELINE;
		break;
	case Opcode::PAGE:
		CCLOG("TextMode [p]");
		mode = TextBox::SetTextMode::PAGE;
		break;
	default:
		mode = TextBox::SetTextMode::RELINE;
		CCLOG("message tag set wrong! set default mode: [p]");
	}
	_currentMainTextBox->setText(text, mode);
}

void TextBoxesManager::onCurrent(EventCustom* pEvent)
{
	CCLOG("on Current");
	auto data = static_cast<OpCommand*>(pEvent->getUserData());

	auto layer = data->params["layer"].asString();

	if (_mainTextBoxes.find(layer) != _mainTextBoxes.end())
	{
		CCLOG("change main textbox to: %s", layer.c_str());
		_currentMainTextBox = _mainTextBoxes[layer];
		_currentMainTextBox->setVisible(true);
	}
	EventCustom e("EVENT_SCRIPT_COMMAND_FINISH");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
	
}

void TextBoxesManager::onHideMsgBox(EventCustom* pEvent)
{
	CCLOG("hide msg box");
	auto textbx = static_cast<char*>(pEvent->getUserData());

	TextBox* box;
	if (_otherTextBoxes.find(textbx) != _otherTextBoxes.end())
	{
		box = _otherTextBoxes[textbx];
	}
	else if (_mainTextBoxes.find(textbx) != _mainTextBoxes.end())
	{
		box = _mainTextBoxes[textbx];
	}
	
	box->hideTextBox();
}
#endif