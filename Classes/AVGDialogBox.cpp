#include "TestMacro.h"


#if defined(TEST_AVG_DIALOGBOX) \
	|| defined(DEBUG_ALL)


#define TEST_AVG_DIALOGBOX
#include "AVGDialogBox.h"

//#define CALLBACK(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
bool AVGDialogBox::init()
{
	bool bRet = false;
	do
	{
		auto winSize = Director::getInstance()->getVisibleSize();
		
		CC_BREAK_IF(!TextBoxLayerColor::init(Color4B(230, 180, 80, 80),
			Size(winSize.width - 60, winSize.height / 3),
			Size(winSize.width, winSize.height / 3),
			TTFConfig("fonts/msyh.ttf", 38),
			true));
		setTextPosition(Point(30, winSize.height / 3 - 30));
		
		setVisible(false);
		
		auto touch = EventListenerTouchOneByOne::create();
		touch->onTouchBegan = CC_CALLBACK_2(AVGDialogBox::onTouchBegan, this);
		touch->onTouchEnded = CC_CALLBACK_2(AVGDialogBox::onTouchEnded, this);
		touch->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, _textboxBackground);

		//×¢²á¼àÌýÊÂ¼þ
		//auto textBoxEventListener = EventListenerCustom::create("EVENT_TEXT",
	//		std::bind(&AVGDialogBox::onNotifyTextBox, this, std::placeholders::_1));

	//	_eventDispatcher->addEventListenerWithSceneGraphPriority(textBoxEventListener, this);

		
		_isEnterScene = false;

		bRet = true;
	} while (0);
	return bRet;
}

void AVGDialogBox::hideBtnCallback()
{
	auto state = _hideBtn->getState();
	if (HideButton::State::STATE_ONE == state)
	{
		//Òþ²Ø
		hideTextBox();
	}
	else if (HideButton::State::STATE_TWO == state)
	{
		showTextBox();
	}
}
void AVGDialogBox::showTextBox()
{
	auto contentSize = getContentSize();
	auto move = MoveBy::create(0.3, Point(0, +1 * contentSize.height));
	auto action = Spawn::createWithTwoActions(move, FadeIn::create(0.3));
	if (this->isRunning())
		this->runAction(action);
	//_textboxBackground->setVisible(true);
}

void AVGDialogBox::hideTextBox()
{
	auto contentSize = getContentSize();
	auto move = MoveBy::create(0.3, Point(0, -1 * contentSize.height));
	auto action = Spawn::createWithTwoActions(move, FadeOut::create(0.3));
	if (this->isRunning())
		this->runAction(action);
	//_textboxBackground->setVisible(false);
}

void AVGDialogBox::nextText()
{
	if (_shownText.empty()) //for the first time
		_currentIndex = 0;

	if (_currentIndex < _textIndexMax){
		_shownText = _allText.at(_currentIndex++);
		updateText();
	}
}

void AVGDialogBox::onEnter()
{
	Node::onEnter();
	setContentSize(_textboxBackground->getContentSize());
	_hideBtn = dynamic_cast<HideButton*>(_parent->getChildByName("hideBtn"));
}


void AVGDialogBox::enterScene()
{
	_textboxBackground->setVisible(true);
	_textboxBackground->setOpacity(0);
	auto posTo = _textboxBackground->getPosition();
	_textboxBackground->setPosition(Point(0, posTo.y - 100));

	auto fadein = FadeTo::create(0.5, 80);
	auto move = MoveBy::create(0.5, Point(0, 100));
	auto enterAction = Spawn::create(fadein, move, NULL);
	_state = State::TEXTBOX_STATE_VISIBLE;
	auto action = Sequence::createWithTwoActions(enterAction,
		CCCallFunc::create(CC_CALLBACK_0(AVGDialogBox::nextText, this)));
	_textboxBackground->runAction(action);

	_isEnterScene = true;
}

bool AVGDialogBox::onTouchBegan(Touch* pTouch, Event* pEvent)
{

	Vec2 touchLocation = pTouch->getLocation();

	auto t = _textboxBackground;
	if (t && t->isVisible() && getTextBoxState() == State::TEXTBOX_STATE_VISIBLE)
	{
		Vec2 local = t->convertToNodeSpace(touchLocation);
		Rect r = getTextBoxRect();
		r.origin = Vec2::ZERO;

		if (r.containsPoint(local))
		{
			return true;
		}
	}
	return false;


}

void AVGDialogBox::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (_textDisplay->getDisplayState() == TextDisplay::State::STATE_RENDERING)
	{
		updateText();
	}
	else
	{
		EventCustom e("EVENT_SCRIPT_CONTINUE");
		e.setUserData(this);
		_eventDispatcher->dispatchEvent(&e);
	}
}

bool NameTextBox::init()
{
	bool bRet = false;
	do
	{
		//Ìí¼ÓÐÕÃûÀ¸
		auto winSize = Director::getInstance()->getVisibleSize();

		TTFConfig config("fonts/msyh.ttf", 37);
		CC_BREAK_IF(!TextBoxLayerColor::init(Color4B(230, 180, 80, 80),
			Size(300, 50),
			Size(300, 50),
			config,
			false));

		setVisible(false);
		setPosition(Point(2, winSize.height / 3));
		getTextDiaplay()->setAlignment(TextHAlignment::CENTER);
		bRet = true;
	} while (0);
	return bRet;
}
#endif