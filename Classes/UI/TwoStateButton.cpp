#include "TwoStateButton.h"

#if defined(TEST_TWO_STATE_BUTTON) \
	|| defined(DEBUG_ALL)


// C++ includes
#include <functional>

TwoStateButton* TwoStateButton::create(Sprite* one, Sprite* two, const std::function<void ()>& callback)
{
	auto pRet = new TwoStateButton();
	if (pRet && pRet->init(one, two, callback))
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
bool TwoStateButton::init(Sprite* one, Sprite* two, const std::function<void ()>& callback)
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		
		
		auto imageSize = one->getContentSize(); 
		_stateOneImage = one;
		_stateOneImage->setPosition(imageSize/2);
		this->addChild(_stateOneImage);

		_stateTwoImage = two;
		//_stateTwoImage->setAnchorPoint(Point::ZERO);
		_stateTwoImage->setPosition(imageSize/2);
		_stateTwoImage->setVisible(false);
		this->addChild(_stateTwoImage);

		_callback = callback;

		setButtonContentSize();

		auto touch = EventListenerTouchOneByOne::create();
		touch->onTouchBegan = CC_CALLBACK_2(TwoStateButton::onTouchBegan, this);
		touch->onTouchEnded = CC_CALLBACK_2(TwoStateButton::onTouchEnded, this);
		touch->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touch, this);

		_state = State::STATE_ONE;
		_currentStateImage = one;
		bRet = true;
	} while (0);
	return bRet;
}


void TwoStateButton::setButtonContentSize()
{
	auto c1 = _stateOneImage->getContentSize();
	auto c2 = _stateTwoImage->getContentSize();
	
	CC_ASSERT(!c1.equals(Size::ZERO) && !c2.equals(Size::ZERO));
	this->setContentSize(c1.height * c1.width > c2.height * c1.width ? c1 : c2);

}


bool TwoStateButton::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	auto localPos = this->convertToNodeSpace(pTouch->getLocation());
	auto size = this->getContentSize();
	auto rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(localPos))
	{
		selected();
		return true;
	}
	return false;
}

void TwoStateButton::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	unselected();
	changeState();
}

void TwoStateButton::changeState()
{
	_callback();

	if (_state == State::STATE_ONE){
		_stateOneImage->setVisible(false);
		_stateTwoImage->setVisible(true);
		_currentStateImage = _stateTwoImage;
		_state = State::STATE_TWO;
	}
	else if (_state == State::STATE_TWO){
		_stateTwoImage->setVisible(false);
		_stateOneImage->setVisible(true);
		_currentStateImage = _stateOneImage;
		_state = State::STATE_ONE;
	}
}

void TwoStateButton::selected()
{
	_selected = true;
}

void TwoStateButton::unselected()
{
	_selected = false;
}

HideButton* HideButton::create(const std::function<void()>& callback)
{
	auto pRet = new HideButton();
	if (pRet && pRet->init(callback))
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

bool HideButton::init(const std::function<void()>& callback)
{
	bool bRet = false;
	do
	{
		auto one = Sprite::create("downarrow.png");
		auto two = Sprite::create("downarrow.png");
		two->setRotation(180);

		CC_BREAK_IF(!TwoStateButton::init(one, two, callback));
		_imagePosition = one->getPosition();
		bRet = true;
	} while (0);
	return bRet;
}
void HideButton::selected()
{
	TwoStateButton::selected();
	
	_currentStateImage->stopAllActions();
	_currentStateImage->setPosition(_imagePosition);
}


void HideButton::unselected()
{
	TwoStateButton::unselected();
}

void HideButton::changeState()
{
	TwoStateButton::changeState();

	startActon();
}

void HideButton::startActon()
{
	auto move = MoveBy::create(0.5f, Point(0, 10));
	auto action = Sequence::create(move, move->reverse(), NULL);
	_currentStateImage->runAction(RepeatForever::create(action));
}

void HideButton::onEnter()
{
	TwoStateButton::onEnter();
	startActon();
}

#endif