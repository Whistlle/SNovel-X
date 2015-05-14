#ifdef TEST_BASE_ACTION_COMMAND \
	|| DEBUG_ALL
#include "BaseActionCommand.h"

BaseAC::BaseAC(Type type)
{
	setCommandType(type);
}

void BaseAC::addData(std::string dataName, const Value& value)
{
	CC_ASSERT(!dataName.empty());

	_data.insert(std::pair<std::string, Value>(dataName, value));

}

void BaseAC::setCommandType(Type type)
{
	_actionType = type;
	_isRunNextActionAfter = false;
	switch (type)
	{
	case Type::ChangeState: 
		_notifyActionName = "EVENT_ACTION_CHANGE_STATE";
		break;
	case Type::Dialog:
		_notifyActionName = "EVENT_ACTION_DIALOG";
		break;
	case Type::EnterActor:
		_notifyActionName = "EVENT_ACTION_ENTER_ACTOR";
		break;
	case Type::EnterScene:
		_notifyActionName = "EVENT_ACTION_ENTER_SCENE";
		break;
	case Type::ExitActor:
		_notifyActionName = "EVENT_ACTION_EXIT_ACTOR";
		break;
	case Type::ExitScene:
		_notifyActionName = "EVENT_ACTION_EXIT_SCENE";
		break;
	case Type::MoveActor:
		_notifyActionName = "EVENT_ACTION_MOVE_ACTOR";
		break;
	case Type::Shake:
		_notifyActionName = "EVENT_ACTION_SHAKE";
		break;
	case Type::PlayMusic:
		_notifyActionName = "EVENT_ACTION_PLAY_MUSIC";
		_isRunNextActionAfter = true;
		break;
	}
}

#endif