#include "TestMacro.h"
#if defined(TEST_TEXT_DISPLAY) \
	|| defined(DEBUG_ALL)

#define TEST_TEXT_DISPLAY
#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
 * TextDisplay
 * 文本渲染
 * 支持特效
 */

class TextDisplay : public Node
{
public:
	enum class State
	{
		STATE_RENDERING,
		STATE_WAIT
	};

	virtual bool init(bool useEffect, const TTFConfig& textConfig);
	virtual bool init(bool useEffect, const TTFConfig& textConfig, const Size& dimensionSize);
	static TextDisplay* create(bool useEffect, const TTFConfig& textConfig);
	static TextDisplay* create(bool useEffect, const TTFConfig& textConfig, const Size& dimensionSize);
	//void onDisplayText();
	void onDisplayText(std::string text);

	//@param  text: the text that wants to add after the current text
	void onDisplayAddedText(std::string text);
	void doingEffect(float dt);
	void useEffect(bool b) { _isUseEffect = b; }

	//调整文本框大小
	void resetTextSize();
	void resetTextSize(const Size& size);

	State getDisplayState() { return _state; }

	Label* getLabel() { return _displayedText;  }
private:
	bool _isUseEffect;
	Label* _displayedText;
	//TextBox* _textBox;
	TTFConfig textConfig;

	State _state;
	//开始动画到现在的进度
	float _progress;
	//void displayTextRemain();
	std::string _text;

	void startEffect();
	void startEffect(int progress);
//	void reset();
	//显示剩余所有文本
	void displayTextRemain();
	virtual void onEnter() override;

	void displayFinish();

	//record the length of last text
	int _lastTextLength;
};


#endif