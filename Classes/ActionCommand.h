#ifdef TEST_ACTION_COMMAND \
	|| DEBUG_ALL

#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*
* Action Command:
* Push Action Command to the Queue to action each action
* every action command contain an action
* for example: PlayBGM EnterScene Dialog MoveActor
* each DialogPartData contains several actions
*/


#define DECL_ACTION_TYPE(type) Type type = Type(#type);
#define DECL_ACTION_TYPES(...)\
	const Type types[]{ \
		__VA_ARGS__\
	}

class ActionCommand
{
public:
	ActionCommand();
	
	virtual void executeAction();
//	virtual void setCommandType(Type type) { };
	void addData(std::string dataName, const Value& value);
//	Type getCommandType() { return _actionType; }

protected:
	std::string _notifyActionName;

	ValueMap _data;
};
#endif