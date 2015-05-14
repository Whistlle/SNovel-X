#ifdef TEST_ACTION_COMMAND \
	|| DEBUG_ALL

#include "ActionCommand.h"

ActionCommand::ActionCommand():
_notifyActionName("")
{

}
void ActionCommand::executeAction()
{
	EventCustom e(_notifyActionName);
	e.setUserData(&_data);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
}

void ActionCommand::addData(std::string dataName, const Value& value)
{
	CC_ASSERT(!dataName.empty());

	_data.insert(std::pair<std::string, Value>(dataName, value));

}
#endif