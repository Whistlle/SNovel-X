#include "TextBox.h"


#if defined(TEST_TEXTBOX) \

namespace SNovel
{
	TextBox::TextBox(bool useEffect)
	{
		auto text = ui::Text::create();
		text->retain();
		TextBox(text, useEffect);
	}

	TextBox::TextBox(ui::Text* text, bool useEffect)
		: _uiText(text)
		, UseEffect(useEffect)
	{
		_textDisplay = new TextDisplay(text);

	}

	TextBox::~TextBox()
	{
		_uiText->release();
	}

	void TextBox::showTextBox()
	{
		_uiText->setVisible(true);
	}

	void TextBox::hideTextBox()
	{

		_uiText->setVisible(false);
	}

	void TextBox::setText(const std::string& text)
	{
		_newText = text;
		updateText();
	}


	void TextBox::enterScene()
	{
		_uiText->setVisible(true);

		_isEnterScene = true;
	}

	void TextBox::updateText()
	{
		if (UseEffect)
		{
			displayText();
		}
		else
		{
			_shownText += _newText;
			_uiText->setText(_shownText);
		}
	}

	void TextBox::displayText()
	{
		if (_textDisplay->isWaiting())
		{
			_textDisplay->startEffect(_shownText, _newText, EffectDuration);
			_shownText += _newText;
		}
		else
		{
			CCLOG("Display Text Error");
		}
	}
	void TextBox::onClick()
	{
		if (_textDisplay->isWaiting())
		{
			EventCustom e("EVENT_SCRIPT_CONTINUE");
			CCLOG("On Continiue");
			Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
		}
		else if (_textDisplay->isRendering())
		{
			_uiText->setText(_shownText + _newText);
		}
	}

	void TextBox::clearMessage()
	{
		_shownText.clear();
	}

	void TextBox::reline()
	{
		_shownText.push_back('\n');
		_uiText->setString(_shownText);
	}
	/*
	TextBoxLayerColor* TextBoxLayerColor::create(const Color4B& color,
												 const Size& textSize,
												 const Size& backgroundSize,
												 const TTFConfig& textConfig,
												 bool useEffect)
	{
		auto pRet = new TextBoxLayerColor();
		if (pRet && pRet->init(color, textSize, backgroundSize, textConfig, useEffect))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = nullptr;
		}
		return pRet;
	}
	bool TextBoxLayerColor::init(const Color4B& color,
								 const Size& textSize,
								 const Size& backgroundSize,
								 const TTFConfig& textConfig,
								 bool useEffect)
	{
		bool bRet = false;
		do
		{
			CC_BREAK_IF(!TextBox::init(textSize, textConfig, useEffect));

			_textboxBackground = LayerColor::create(color);
			_textboxBackground->setContentSize(backgroundSize);
			_textboxBackground->setAnchorPoint(Point(0, 0));
			_textboxBackground->setPosition(Point(0, 0));
			_textboxBackground->setVisible(true);
			this->addChild(_textboxBackground, -1);

			//setContentSize() 在创建textDiaplay之前
			setContentSize(backgroundSize);
			bRet = true;
		} while (0);
		return bRet;
	}

	Rect TextBoxLayerColor::getTextBoxRect()
	{
		auto pos = _textboxBackground->convertToWorldSpace(_textboxBackground->getPosition());
		auto size = _textboxBackground->getContentSize();
		auto anthor = _textboxBackground->getAnchorPoint();

		return Rect(pos.x - size.width * anthor.x,
					pos.y - size.height * anthor.y,
					size.width,
					size.height);
	}

	void TextBoxLayerColor::setContentSize(const Size& size)
	{
		TextBox::setContentSize(size);
		//_textboxBackground->setContentSize(size);
	}

	void TextBoxLayerColor::onEnter()
	{
		TextBox::onEnter();
		//setContentSize(_textboxBackground->getContentSize());
	}

	TextBoxSprite* TextBoxSprite::create(const char* filePath,
										 const Size& textSize,
										 const Size& backgroundSize,
										 const TTFConfig& textConfig,
										 bool useEffect)
	{
		auto pRet = new TextBoxSprite();
		if (pRet && pRet->init(filePath, textSize, backgroundSize, textConfig, true))
		{
			pRet->autorelease();
		}
		else
		{
			delete pRet;
			pRet = nullptr;
		}
		return pRet;
	}

	bool TextBoxSprite::init(const char* filePath,
							 const Size& textSize,
							 const Size& backgroundSize,
							 const TTFConfig& textConfig,
							 bool useEffect)
	{
		bool bRet = false;
		do
		{
			CC_BREAK_IF(!TextBox::init(textSize, textConfig, useEffect));

			_textboxBackground = Sprite::create(filePath);
			_textboxBackground->setContentSize(backgroundSize);
			_textboxBackground->setAnchorPoint(Point(0, 0));
			_textboxBackground->setPosition(Point(0, 0));
			_textboxBackground->setVisible(false);
			this->addChild(_textboxBackground);

			//setContentSize() 在创建textDiaplay之前
			setContentSize(_textboxBackground->getContentSize());
			bRet = true;
		} while (0);
		return bRet;
	}

	Rect TextBoxSprite::getTextBoxRect()
	{
		auto pos = _textboxBackground->convertToWorldSpace(_textboxBackground->getPosition());
		auto size = _textboxBackground->getContentSize();
		auto anthor = _textboxBackground->getAnchorPoint();

		return Rect(pos.x - size.width * anthor.x,
					pos.y - size.height * anthor.y,
					size.width,
					size.height);
	}

	void TextBoxSprite::setContentSize(const Size& size)
	{
		TextBox::setContentSize(size);
		_textboxBackground->setContentSize(size);
	}

	void TextBoxSprite::onEnter()
	{
		TextBox::onEnter();
		setContentSize(_textboxBackground->getContentSize());
	}*/
}
#endif