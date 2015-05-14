#include "TestMacro.h"
#if defined(TEST_KAG_TAG) \
	|| defined(DEBUG_ALL)
#define TEST_KAG_TAG
#pragma once
#include <string>
#include <vector>
#include <functional>
#include "KAGWord.h"

/*
 * a tag command of the script
 */
typedef std::function<void(KAGWords)>  TagCallback;

class aKAGTag
{
public:
	aKAGTag(const char* name, int ID, std::vector<aKAGTag>& tags)
	{
		_tagName = name;
		_id = ID;
		tags.push_back(*this);
	}
	
	int getID() { return _id; }
	const string& getTagName() const { return _tagName; }
private:
	std::string _tagName;
	int _id;
	//TagCallback _onTagCallback;
};	

class aKAGCustomTag : public aKAGTag
{
public:
	aKAGCustomTag(const char* name, int ID, std::vector<aKAGTag>& tags);
	void setTagCallback(const TagCallback& _callback)
	{
		_onTagCallback = _callback;
	}
	TagCallback& getTagCallback() { return _onTagCallback; }
private:
	TagCallback _onTagCallback;
};


class KAGTagManager
{
#define DeclTag(name, i) \
	aKAGTag name = aKAGTag{ #name, i, _tagHolder}; \
	static const int tag_##name = i;

private:
	std::vector<aKAGTag> _tagHolder;
	int getNextTagId();
public:
	KAGTagManager();
	DeclTag(wait,		2);
	DeclTag(link,		3);	
	DeclTag(jump,		4);
	DeclTag(layopt,		5);
	DeclTag(loadscene,	6);
	DeclTag(current,	7);
	DeclTag(anim,		8);
	DeclTag(object,		9);
	DeclTag(instantiate,10);
	DeclTag(loadlevel,	11);
	DeclTag(sendevent,	12);
	DeclTag(image,		13);
	DeclTag(condition,	14);
	DeclTag(setflag,	15);
	DeclTag(destroy,	16);
	DeclTag(getuserinput,17);
	DeclTag(definescene,18);
	DeclTag(defineactor,19);
	DeclTag(font,		20);
	DeclTag(eval,		21);
	DeclTag(if_,		22);
	DeclTag(endif,		23);
	DeclTag(setpropactor,24);
	DeclTag(enterscene,	25);
	DeclTag(enteractor,	26);
	DeclTag(addstate,	27);
	DeclTag(moveactor,	28);
	DeclTag(exitactor,	29);
	DeclTag(exitscene,	30);
	DeclTag(settext,	31);
	DeclTag(showsystemui,32);
	DeclTag(hidesystemui,33);
	DeclTag(changestate,34);
	DeclTag(stopbgm,	35);
	DeclTag(shake,		36);
	DeclTag(playbgm,	37);
	DeclTag(playse,		38);
	DeclTag(playvoice,	39);
	DeclTag(xchgbgm,	40);
	DeclTag(fadoutbgm,	41);
	DeclTag(trans,		42);


	void registerCustomTag(const char* TagName, std::function<void(KAGWords)> tagCallback);
	const std::vector<aKAGTag>& getRegisteredTags() const { return _tagHolder; }

};
/* 
 * a kag command
 */
/*
class KAGCommand
{
public:
	KAGCommand();

	void execute();

	int getCommandNO() const { return _commandNO;  }
	void setCommandNO(int NO) { _commandNO = NO;  }

protected:
	std::vector<ScriptedValue> datum;
	// number of the command in the command list
	int _commandNO;
};*/
#endif // defined(TEST_KAG_COMMAND) 