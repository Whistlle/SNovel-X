#ifdef TEST_DIALOG_ACTION_COMMAND \
	|| DEBUG_ALL

#define TEST_ACTION_COMMAND
#define TEST_DIALOG_ACTION_TYPE
#define TEST_DIALOG_ACTION_CENTER

#pragma once
#include "ActionCommand.h"
#include "DialogActionType.h"
#include "DialogActionCenter.h"

USING_NS_CC;

/*
* Action Command:
* Push Action Command to the Queue to action each action
* every action command contain an action
* for example: PlayBGM EnterScene Dialog MoveActor
* each DialogPartData contains several actions
*/

class DialogAC : public ActionCommand
{
public:
	DialogAC(DialogActionType type);

	virtual void setCommandType(DialogActionType type);

	//void addData(std::string dataName, const Value& value);
	DialogActionType getCommandType() { return _actionType; }

	void sendCommand();

private:
	DialogActionType _actionType;
	DialogActionCenter* _centerInstance;
};

#endif