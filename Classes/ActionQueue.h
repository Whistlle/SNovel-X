#ifdef TEST_ACTION_QUEUE \
	|| DEBUG_ALL
#pragma once
#include "ActionCommand.h"
#include <queue>

class ActionQueue
{
public:
//	static ActionQueue* getInstance();
	ActionQueue();
	~ActionQueue();
	virtual void addCommand(ActionCommand* command);
	ActionCommand* pop();
private:

	std::queue<ActionCommand*> _commandQueue;
};
#endif