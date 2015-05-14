#ifdef TEST_BASE_ACTION_COMMAND \
	|| DEBUG_ALL
#define TEST_ACTION_COMMAND

#pragma once
#include "ActionCommand.h"

USING_NS_CC;

/*
* Action Command:
* Push Action Command to the Queue to action each action
* every action command contain an action
* for example: PlayBGM EnterScene Dialog MoveActor
* each DialogPartData contains several actions
*/

class BaseAC : public ActionCommand
{
public:
	
	enum class Type
	{
	Dialog,
	EnterActor,
	ExitActor,
	ChangeState,
	Shake,
	MoveActor,
	EnterScene,
	ExitScene,
	PlayMusic
	};


	BaseAC(Type type);

	virtual void setCommandType(Type type);

	void addData(std::string dataName, const Value& value);
	Type getCommandType() { return _actionType; }
	bool isRunNextActionAfter() { return _isRunNextActionAfter; }
private:
	std::string _notifyActionName;

	ValueMap _data;

	Type _actionType;

	bool _isRunNextActionAfter;
};
#endif