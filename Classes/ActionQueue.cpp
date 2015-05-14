#ifdef TEST_ACTION_QUEUE \
	|| DEBUG_ALL

#include "ActionQueue.h"
/*
static ActionQueue* _sharedActionQueue = nullptr;

ActionQueue* ActionQueue::getInstance()
{
	if (!_sharedActionQueue)
	{
		_sharedActionQueue = new ActionQueue();
	}
	return _sharedActionQueue;
}
*/

ActionQueue::ActionQueue()
{
	 
}
ActionQueue::~ActionQueue()
{
	if (!_commandQueue.empty())
	{
		auto p = _commandQueue.front();
		_commandQueue.pop();
		delete p;
	}
}


void ActionQueue::addCommand(ActionCommand* command)
{
	CC_ASSERT(command != nullptr);
	if (command)
		_commandQueue.push(command);
}

ActionCommand* ActionQueue::pop()
{
	auto command = _commandQueue.front();
	_commandQueue.pop();
	return command;
}

#endif