#ifdef TEST_DIALOG_PART_NODE \
	|| DEBUG_ALL
#define TEXT_DIALOG_PART_DATA


#pragma once
#include "cocos2d.h"
#include "DialogPartData.h"
#include "tinyxml2\tinyxml2.h"
USING_NS_CC;

/*
 *  读取脚本，加载人物场景信息并保存在类中
*/
class DialogPartNode:public Ref
{
public:
	DialogPartNode(const char* fileName);
	
	int getActionNumber() const { return _actionCounter; }
	
	/*
	 * 获取相应的DATA编号  
	 */
	DialogPartData* getAction(int actionNumber);

	void loadDialogPartDatum(const char *fileName);

	std::deque<DialogPartData*>& getDatum() { return _loadedDatum; }

	/*
	 * 将data拆解成相应的action并加入动作队列
	 */
	void pharseToAction();
private:
	std::deque<DialogPartData*> _loadedDatum;
	void readChildElement(tinyxml2::XMLElement* data);
	void readChildElement(tinyxml2::XMLElement* data, IXMLScriptedData* scriptedData);
	DialogPartData* partdata;
	int _actionCounter = 0;

	void pharseTextID(DialogPartData* data);
};

#endif