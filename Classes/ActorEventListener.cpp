#ifdef TEST_ACTOREVENTLISTENER \
	|| DEBUG_ALL 

#include "ActorEventListener.h"
#include "cocos2d.h"
#include "L2DPart\LAppLive2DManager.h"
#include "L2DPart\LAppModel.h"
USING_NS_CC;

ActorEventListener::ActorEventListener(Node* eventListener)
{
	//×¢²á¼àÌýÊÂ¼þ
	auto changeStateEvent = EventListenerCustom::create("EVENT_ACTION_CHANGE_STATE",
		CC_CALLBACK_1(ActorEventListener::onActorChangeState, this));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(changeStateEvent, eventListener);

}

void ActorEventListener::onActorChangeState(EventCustom* pEvent)
{
	CCLOG("on Actor Change State");
	auto data = static_cast<ValueMap*>(pEvent->getUserData());
	//auto expression = (*data)["expression"].asString();
	auto model = LAppLive2DManager::getInstance()->getCurrentModel();
	//model->startRandomMotion(MOTION_GROUP_TAP_BODY, PRIORITY_NORMAL);
	auto name = (*data)["motionName"].asString();
	auto no = (*data)["motionNo"].asInt();
	model->startMotion(name.c_str(), no, 3);

	//model->setExpression(expression.c_str());
	CCLOG("Actor Change State Action Finish");
	EventCustom e("EVENT_ACTION_FINISH");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
}

#endif