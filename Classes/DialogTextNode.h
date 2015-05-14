#ifdef TEST_DIALOG_TEXT_NODE \
	|| DEBUG_ALL

#pragma once
#include "cocos2d.h"

USING_NS_CC;

struct DialogTextData
{
public:


	DialogTextData();
	std::string text;
	std::string name;
	int textNo; 
	int scenarioNo;
	int selectionNo;
};

class DialogTextNode:public Ref
{
public:
	static DialogTextNode* getInstance();
//	
	std::vector<DialogTextData*> _dialogTextDatum;
	
	//场景数
	int scenarioCount;
	
	int selectionNo;
	DialogTextData* getDialogTextData(const std::string& scnarioID);

private:
	DialogTextNode();

	int _dataCount;

	//章节开始的偏移量
	std::vector<int> _selectionBegin;

	//载入场景编号中的所有对话进入缓存
	void loadDatum(int SceneNo);

	//当前场景编号
	int _currentScenario;
};

#endif