#ifdef TEST_DIALOG_ACTION_COMMAND \
	|| DEBUG_ALL
#include "DialogActionCommand.h"

DialogAC::DialogAC(DialogActionType type)
{
	setCommandType(type);
	_centerInstance = DialogActionCenter::getInstance();
}

void DialogAC::setCommandType(DialogActionType type)
{
	_actionType = type;
	switch (type)
	{
	case DialogActionType::ChangeMotion:
		_notifyActionName = "EVENT_ACTION_CHANGE_STATE";
		break;
	case DialogActionType::Dialog:
		_notifyActionName = "EVENT_ACTION_DIALOG";
		break;
	case DialogActionType::EnterActor:
		_notifyActionName = "EVENT_ACTION_ENTER_ACTOR";
		break;
	case DialogActionType::EnterScene:
		_notifyActionName = "EVENT_ACTION_ENTER_SCENE";
		break;
	case DialogActionType::ExitActor:
		_notifyActionName = "EVENT_ACTION_EXIT_ACTOR";
		break;
	case DialogActionType::ExitScene:
		_notifyActionName = "EVENT_ACTION_EXIT_SCENE";
		break;
	case DialogActionType::MoveActor:
		_notifyActionName = "EVENT_ACTION_MOVE_ACTOR";
		break;
	case DialogActionType::Shake:
		_notifyActionName = "EVENT_ACTION_SHAKE";
		break;
	}
}

void DialogAC::sendCommand()
{
	_centerInstance->addCommand(this);
}
#endif