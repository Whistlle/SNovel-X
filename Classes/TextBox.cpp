#include "TextBox.h"

#if defined(TEST_TEXTBOX) \
	|| defined(DEBUG_ALL)




//#define CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
bool TextBox::init(const Size& textSize, const TTFConfig& textConfig, bool useEffect)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init()); 

	//	loadAllText();
		
		auto winSize = Director::getInstance()->getVisibleSize();

		_shownText = "";
		_isUseEffect = useEffect;
		_textDisplay = TextDisplay::create(useEffect, textConfig, textSize);
		this->addChild(_textDisplay);
		//_textDisplay->setPosition(Point(0 + 30, winSize.height / 3 - 30));
		_textDisplay->setPosition(Point(0, textSize.height));
		_state = State::TEXTBOX_STATE_HIDE;
		
		_isEnterScene = false;
		bRet = true;
	} while (0);
	return bRet;
}

void TextBox::showTextBox()
{
	this->setVisible(true);
}

void TextBox::hideTextBox()
{

	this->setVisible(false);
}

/*
void TextBox::setText(const std::string& text)
{
	_shownText = text;
	updateText();
}
*/
void TextBox::setText(const std::string& text, SetTextMode mode)
{
	switch (mode)
	{
	case SetTextMode::PAGE:
		_shownText = text;
		updateText();
		break;
	case SetTextMode::RELINE:
		_shownText.push_back('\n');
		_shownText += text;
		_textDisplay->onDisplayAddedText(text);
		break;
	}
}
void TextBox::onEnter()
{
	Node::onEnter();
}

void TextBox::enterScene()
{
	this->setVisible(true);
	
	_isEnterScene = true;
}

void TextBox::updateText()
{
	_textDisplay->onDisplayText(_shownText);
	//_displayedText->setString(_shownText);

}


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
}

#endif