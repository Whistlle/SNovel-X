#ifdef TEST_ACTOREVENTLISTENER \
	|| DEBUG_ALL 

#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ActorEventListener
{
public:
	ActorEventListener(Node* eventListener);
private:
	void onActorChangeState(EventCustom* pEvent);
};

#endif