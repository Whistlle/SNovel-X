#ifdef TEST_SCENE_CTRL \
	|| DEBUG_ALL

#pragma once
#include "cocos2d.h"
#include "DialogPartNode.h"
#include "ActorEventListener.h"
#include "ActionQueue.h"
USING_NS_CC;

//TODO: ÄÚ´æ¹ÜÀí
class SceneCtrl:public Node
{
public:
	//CREATE_FUNC(SceneCtrl);
	static SceneCtrl* getInstance();
	virtual bool init();
	void Start();
	ActionQueue* getActionQueue();
private:
	int _currentActionID = 0;
	bool _isActionFinish = false;
	void onActionFinish(EventCustom* pEvent);
	void onNextAction(EventCustom* pEvent);
	void onNextMessage(EventCustom* pEvent);
	DialogPartNode* _dialogPartNode;
	void loadScene();
	ActorEventListener* _actorEventListener;
	ActionQueue* _actionQueue;
	bool _isRunNextActionAfter;
};


#endif