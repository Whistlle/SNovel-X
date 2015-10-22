//#include "Debug\TestMacro.h"
#define TEST_TEXTBOX
#if defined(TEST_TEXTBOX)

#pragma once
#include "cocos2d.h"
#include "TextDisplay.h"

USING_NS_CC;

namespace SNovel
{
	/*
	 * textbox
	 * best practice
	 * 创建ui::text, Textbox， 设置text在投进box中
	 * or: 创建TextBox, get uiText
	 */
	class TextDisplay;

	//TODO: set addtional op
	class TextBox
	{
	public:
		TextBox(ui::Text*, bool useEffect = true);
		TextBox(bool useEffect);
	    //static TextBox* create(ui::Text*, bool useEffect = true);
		//static TextBox* create(bool useEffect = true);
		~TextBox();

		//CREATE_FUNC(TextBox);

		//virtual void setText(const std::string& text);
		virtual void setText(const std::string& text);

		//	Label* getTextDiaplay() { return _textDisplay->ui }

		virtual void showTextBox();
		virtual void hideTextBox();

		virtual void clearMessage();
		virtual void reline();

		std::string getCurrentText()  { return _shownText; }

		//显示文本的时候是否使用特效
		bool UseEffect = true;
		float EffectDuration = 0.03;

		bool isEnterScene() const { return _isEnterScene; }

		virtual void enterScene();
		//std::function<void(std::string)> OnSetText;
		void onClick();
		void bindUIText(ui::Text* uiText) { _uiText = uiText; }
		ui::Text* getUIText() { return _uiText; }
	protected:
		
		
		Size _textSize;
		bool _isEnterScene;

		

		TextDisplay* _textDisplay;

		ui::Text* _uiText;
		//缓存所有的文本
		std::vector<std::string> _allText;

		//当前显示的文本
		std::string _shownText;

		//即将显示的文本
		std::string _newText;

		//文本与背景图层顺序
		const short BK_Z_ORDER = 0;
		const short TEXT_Z_ORDER = 1;

		void loadAllText();

		//	bool onTouchBegan(Touch* pTouch, Event* pEvent);
		//	void onTouchEnded(Touch* pTouch, Event* pEvent);

		void updateText();
		void displayText();

		//当前显示的文字
		//LabelTTF* _displayedText;

		//State getTextBoxState()  { return _state; }
		//State _state;



		//	HideButton* hideBtn;

		//	void onNotifyTextBox(EventCustom* pEvent);

	};
	/*
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
	}*/
}
#endif