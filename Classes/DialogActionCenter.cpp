#ifdef TEST_DIALOG_ACTION_CENTER \
	|| DEBUG_ALL
#include "DialogActionCenter.h"

static DialogActionCenter* _sharedDialogActionCenter = nullptr;

DialogActionCenter* DialogActionCenter::getInstance()
{
	if (!_sharedDialogActionCenter)
	{
		_sharedDialogActionCenter = new DialogActionCenter();
	}
	return _sharedDialogActionCenter;
}

DialogActionCenter::DialogActionCenter()
{
	_listener = Director::getInstance()->getEventDispatcher()->addCustomEventListener("EVENT_NEXT_MESSAGE"
		, CC_CALLBACK_1(DialogActionCenter::onNextMessage, this));
	
//	_node = new DialogPartNode();

}

void DialogActionCenter::onNextMessage(EventCustom* pEvent)
{
	auto action = this->_node->getDatum().front();
	pharseAction(action);
	this->_node->getDatum().pop_front();
}

void DialogActionCenter::pharseAction(DialogPartData* data)
{
	auto action = data->actionID->asString();
	if (action.compare("Dialog") == 0)
	{
	 auto command = new DialogAC(DialogActionType::Dialog);
	 //	if (data->isName->asBool())
	 //	{
	 //		auto name = data->getActorName();
	 //		command->addData("actorName", Value(name));
	 //	}
	 auto name = data->getActorName();
	 command->addData("actorName", Value(name));
	 command->addData("dialogText", Value(data->getDialogText()));
	 //	command->sendCommand();
	 if (data->isBGM->asBool())
	 {

	 }

	 if (data->isSE->asBool())
	 {

	 }

	 if (data->isVoice->asBool())
	 {

	 }
	 if (data->isChangeMotion->asBool())
	 {
	 //auto command = new DialogAC(DialogActionType::ChangeMotion);
	 auto motion = data->actorEntry->motion->getValue().asString();
	 char name[20], num[20];
	 sscanf(motion.c_str(), "%s_%s", name, num);
	 command->addData("motionName", Value(name));
	 command->addData("motionNo", Value(num));
	 command->addData("actorName", Value(data->actorEntry->getValue().asString()));
	 command->sendCommand();
	 }

	 }
	 else if (action.compare("EnterActor"))
	 {

	 }
}

void DialogActionCenter::loadDialogPartDatum(const char *fileName)
{
	_node = new DialogPartNode(fileName);
}

#endif