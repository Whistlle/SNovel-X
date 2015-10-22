#include "TextBoxesManager.h"

#if defined(TEST_TEXTBOXES_MANAGER)

#include "cocos2d.h"
#include "ImageManager.h"
#include <string>

USING_NS_CC;

namespace SNovel
{

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
		/*
		//×¢²á¼àÌýÊÂ¼þ
		auto setTextEventListener = EventListenerCustom::create("EVENT_SETTEXT",
		std::bind(&TextBoxesManager::onSetText, this, std::placeholders::_1));

		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(setTextEventListener, 1);
		*/
	}

	
	void TextBoxesManager::add(TextBox* textbox, const char* name, TextBoxType type)
	{
		if (_textBoxes.find(name) != _textBoxes.end())
		{
			CCLOG("TextBox:%s has added, change a name", name);
		}
		_textBoxes[name] = textbox;
		switch (type)
		{
			case SNovel::TextBoxesManager::TextBoxType::MAIN:
				CurrentMainTextBox = textbox;
				break;
			case SNovel::TextBoxesManager::TextBoxType::NAME:
				CurrentNameTextBox = textbox;
				break;
			case SNovel::TextBoxesManager::TextBoxType::OTHER:
				break;
			default:
				break;
		}

		/*
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
		}*/
	}
	/*
	void TextBoxesManager::setText(unordered_map<string, string>& data)
	{
		CCLOG("[SetText]");
		string boxName = data["textbox"];
		if (_textBoxes.find(boxName) != _textBoxes.end())
		{
			string text = data["text"];
			auto textbox = _textBoxes[boxName];
			textbox->clearMessage();
			textbox->setText(text);
		}
	}
	*/
	void TextBoxesManager::setName(string text)
	{
		CCLOG("[SetName]:%s", text);
		if (CurrentNameTextBox)
		{
			CurrentNameTextBox->clearMessage();
			CurrentNameTextBox->setText(text);
		}
	}
	void TextBoxesManager::printText(string& text)
	{
		CCLOG("[Print Text]");
		//string text = data["text"];
		CurrentMainTextBox->setText(text);
	}

	void TextBoxesManager::current(ValueMap& data)
	{
		CCLOG("[Current]");
		string layer;

		if (data.find("layer") != data.end())
		{
			layer = data["layer"].asString();
			if (_textBoxes.find(layer) != _textBoxes.end())
			{
				CCLOG("change main textbox to :%s", layer);
				CurrentNameTextBox = _textBoxes[layer];
				//CurrentNameTextBox->setVisible(true);
			}
			else
			{
				CCLOG("can not change main textbox: %d", layer);
			}
		}
		else
		{
			CCLOG("message error!");
		}

	}

	void TextBoxesManager::hideMsgBox(ValueMap& data)
	{
		CCLOG("[Hide Msg Box]");
		string textboxName = data["name"].asString();

		TextBox* box;
		if (_textBoxes.find(textboxName) != _textBoxes.end())
		{
			box = _textBoxes[textboxName];
			box->hideTextBox();
		}
	}

	void TextBoxesManager::clearMessage()
	{
		CurrentMainTextBox->clearMessage();
	}
	void TextBoxesManager::reline()
	{
		CurrentMainTextBox->reline();
	}

	void TextBoxesManager::move(string name, Point& to)
	{
		if (_textBoxes.find(name) == _textBoxes.end())
		{
			CCLOG("can not find textbox: %d", name);
		}
		else
		{
			_textBoxes[name]->getUIText()->setPosition(to);
		}
	}
}
#endif