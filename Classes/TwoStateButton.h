#include "TestMacro.h"
#if defined(TEST_TWO_STATE_BUTTON) \
	|| defined(DEBUG_ALL)

#define TEST_TWO_STATE_BUTTON
#pragma once
#include "cocos2d.h"
USING_NS_CC;


class TwoStateButton : public Node
{
public:
	virtual bool init(Sprite* one, Sprite* two, const std::function<void ()>& callback);
	static TwoStateButton* create(Sprite* one, Sprite* two, const std::function<void ()>& callback);

	Sprite* getStateOneImage() { return _stateOneImage; }
	Sprite* getStateTwoImage() { return _stateTwoImage; }
	Sprite* getSelectedImage() { return _selectedImage; }
	
	enum class State
	{
		STATE_ONE,
		STATE_TWO,
	};
	State getState() { return _state; }

private:

	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);
	Sprite* _stateOneImage;
	Sprite* _stateTwoImage;

	Sprite* _selectedImage;
	Rect rect();

	void setButtonContentSize();
 
//	void setTarget(Ref* target, void (Ref::*callback)());
protected:
	std::function<void()> _callback;
	
	virtual void selected();
	virtual void unselected();
	bool _selected;

	virtual void changeState();

	State _state;
	Sprite* _currentStateImage;
};

class HideButton : public TwoStateButton
{
public:
	virtual bool init(const std::function<void()>& callback);
	static HideButton* create(const std::function<void()>& callback);
private:
	virtual void selected() override;
	virtual void unselected() override;
	virtual void changeState() override;
	Point _imagePosition;
	Sprite* _background;
	void startActon();
	virtual void onEnter() override;
	
};

#endif