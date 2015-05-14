#include "TestMacro.h"
#if defined(TEST_KAGWORD) \
	|| defined(DEBUG_ALL)
#define TEST_KAGWORD

#pragma once

#include <string>
#include "cocos2d.h"
using namespace std;

class KAGWord;
typedef vector<KAGWord>  KAGWords;

/*
 * KAGWord
 * a word contains a type, value(for attribute and name for command)
 */

class KAGWord
{
public:
	enum class Type
	{
		TAG,
		ATTRIBUTE,
		TEXT,
		SCENARIO
	};

	//init for command and string
	//KAGWord(Type type, const string& name);

	//init for attribute command and string
	KAGWord(Type type, const string& attribute, const string& value);
	//void setType(Type type);
	//Type getType() { return _type; }

//	string getName() { return _name; }
	
	CC_SYNTHESIZE(Type, _type, Type);
	CC_SYNTHESIZE(string, _name, Name);
	CC_SYNTHESIZE(cocos2d::Value, _value, Value);
private:
	//Type _type;
	//string _name;
	//cocos2d::Value _value;
};
#endif