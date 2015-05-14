#ifdef TEST_SCENE_CTRL \
	|| DEBUG_ALL


#include "SceneCtrl.h"

#include "DialogPartData.h"
#include "ActionQueue.h"

//TODO: 将命令封装成对象 实现命令模式 更改命令容器的数据结构
static SceneCtrl* _sharedSceneCtrl = nullptr;
SceneCtrl* SceneCtrl::getInstance()
{
	if (!_sharedSceneCtrl)
	{
		_sharedSceneCtrl = new SceneCtrl();
		_sharedSceneCtrl->init();
	}
	return _sharedSceneCtrl;
}

bool SceneCtrl::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());
		//注册动作结束回调事件
		auto actionFinishListener = EventListenerCustom::create("EVENT_ACTION_FINISH", 
			CC_CALLBACK_1(SceneCtrl::onActionFinish, this));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(actionFinishListener, this);
	
		auto messageEventListener = EventListenerCustom::create("EVENT_NEXT_ACTION",
			CC_CALLBACK_1(SceneCtrl::onNextAction, this));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(messageEventListener, this);

		_actorEventListener = new ActorEventListener(this);
		
		_actionQueue = new ActionQueue();
		
		loadScene();

		bRet = true;
	} while (0);
	return bRet;
}

void SceneCtrl::loadScene()
{
	_dialogPartNode = new DialogPartNode("text4.xml");
	_dialogPartNode->pharseToAction();

}
void SceneCtrl::Start()
{	
	_currentActionID = 0;
	_isActionFinish = false;

	auto action = getActionQueue()->pop();

	_isRunNextActionAfter = action->isRunNextActionAfter();
	action->executeAction();
};

void SceneCtrl::onActionFinish(EventCustom* pEvent)
{
	CCLOG("on Action Finish");
	_isActionFinish = true;
	if (_isRunNextActionAfter)
		onNextAction(nullptr);
}

//
void SceneCtrl::onNextAction(EventCustom* pEvent)
{
	if (_isActionFinish)
	{
		CCLOG("on Next Action");

		_isActionFinish = false;
		auto action = getActionQueue()->pop();
		if (action){
			_isRunNextActionAfter = action->isRunNextActionAfter();
			action->executeAction();
		}
	}
}

ActionQueue* SceneCtrl::getActionQueue()
{
	return _actionQueue;
}

#endif