#include "TestMacro.h"

#if defined(TEST_TEXTBOX) \
	|| defined(DEBUG_ALL)

#pragma once
#include "cocos2d.h"
#include "TextDisplay.h"
USING_NS_CC;

/* 
 * textbox
 * do not setposition
 */
class TextDisplay;

//TODO: set addtional op
class TextBox: public Node
{ 
public:
	virtual bool init(const Size& textSize, const TTFConfig& textConfig, bool useEffect = true);
	static TextBox* create(const Size& textSize, const TTFConfig& textConfig, bool useEffect = true);
	//CREATE_FUNC(TextBox);

	//void nextText();
	enum class SetTextMode
	{
		PAGE, //[P]
		RELINE   //[R]
	};
	//virtual void setText(const std::string& text);
	virtual void setText(const std::string& text, SetTextMode mode = SetTextMode::PAGE);

	void addText(const std::string& text);
	void setTextPosition(const Point& pos) { _textDisplay->setPosition(pos); }
	Label* getTextDiaplay() { return _textDisplay->getLabel();  }
	virtual void showTextBox();
    virtual void hideTextBox();

	virtual void onEnter() override;

	enum class State
	{
		TEXTBOX_STATE_VISIBLE,
		TEXTBOX_STATE_HIDE
	};

	std::string getCurrentText()  { return _shownText; }

	//显示文本的时候是否使用特效
	void useEffect(bool use) { _isUseEffect = use; };

	bool isEnterScene() const { return _isEnterScene;  }

	virtual void enterScene();
	//CC_SYNTHESIZE(int, _testBoxIndex, TextBoxIndex);
protected:
	Size _textSize;
	bool _isEnterScene;
	bool _isUseEffect = true;
	//缓存所有的文本
	//std::unordered_map<std::string, std::string> _mapAllText;
	std::vector<std::string> _allText;
	
	int _textIndexMax;
	int _currentIndex;

	//当前显示的文本
	std::string _shownText;

	//文本与背景图层顺序
	const short BK_Z_ORDER = 0;
	const short TEXT_Z_ORDER = 1;

	void loadAllText();

//	bool onTouchBegan(Touch* pTouch, Event* pEvent);
//	void onTouchEnded(Touch* pTouch, Event* pEvent);

	void updateText();

	//当前显示的文字
	//LabelTTF* _displayedText;

	State getTextBoxState()  { return _state; }
	State _state;

	TextDisplay* _textDisplay;
	
//	HideButton* hideBtn;
	
//	void onNotifyTextBox(EventCustom* pEvent);
	
};

class TextBoxSprite : public TextBox
{
public:
	static TextBoxSprite* create(const char* filePath,
		const Size& textSize,
		const Size& backgroundSize,
		const TTFConfig& textConfig,
		bool useEffect = true);

	virtual bool init(const char* filePath,
		const Size& textSize, 
		const Size& backgroundSize,
		const TTFConfig& textConfig,
		bool useEffect = true);

	virtual void setContentSize(const Size& size) override;
	Rect getTextBoxRect();

	virtual void onEnter() override;
protected:
	//TextBox背景 TODO：可做成一张透明图片
	Sprite* _textboxBackground;

};

class TextBoxLayerColor : public TextBox
{
public:
	static TextBoxLayerColor* create(const Color4B& color,
		const Size& textSize,
		const Size& backgroundSize,
		const TTFConfig& textConfig,
		bool useEffect = true);

	virtual bool init(const Color4B& color,
		const Size& textSize,
		const Size& backgroundSize,
		const TTFConfig& textConfig,
		bool useEffect = true);

	virtual void setContentSize(const Size& size) override;
	Rect getTextBoxRect();
	
	virtual void onEnter() override;
protected:
	LayerColor* _textboxBackground;

};

#endif