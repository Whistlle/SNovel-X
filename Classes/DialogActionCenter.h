#ifdef TEST_DIALOG_ACTION_CENTER \
	|| DEBUG_ALL

#pragma once
#include "ActionQueue.h"
#include "DialogActionCommand.h"
#include "DialogPartNode.h"
class DialogActionCenter
{
public:
	static DialogActionCenter* getInstance();

	void loadDialogPartDatum(const char *fileName);
private:
	DialogActionCenter();
	
	//处理容器中第一个命令
	void pharseAction(DialogPartData* data);

	void onNextMessage(EventCustom* pEvent);

	EventListener* _listener;

	DialogPartNode* _node;
};
#endif