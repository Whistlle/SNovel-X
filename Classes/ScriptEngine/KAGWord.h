//#include "TestMacro.h"

#define TEST_KAGWORD
#if defined(TEST_KAGWORD) \
	|| defined(DEBUG_ALL)
#define TEST_KAGWORD

#pragma once

#include <string>
#include "base\CCValue.h"

using namespace std;




/*
 * a list of KAGWord
 * consist of:
 * 1. type of this line: TAG/ATTRIBUTE/TEXT/SCENARIO/NAME
 * 2. attribute of this line contains: 
 *    e.g. type: attribute  name: fade  value : true
 */


/*
 * KAGWord
 * a word contains a type, value(for attribute and name for command)
 */

namespace SNovel
{
	class KAGWord;
	typedef vector<KAGWord>  KAGWords;

	class KAGWord
	{
	public:
		enum class Type
		{
			TAG,
			TEXT,
			SCENARIO,
			NAME,
			ATTRIBUTE
		};

		//init for command and string
		//KAGWord(Type type, const string& name);

		//create an attribute
		KAGWord(const string& attribute, const string& value):
			_type(Type::ATTRIBUTE),
			_name(attribute),
			_value(value)
		{ }

		//create an type
		KAGWord(Type type, const string& tagname) :
			_type(type),
			_name("tag"),
			_value(tagname)
		{ }

		CC_SYNTHESIZE_READONLY(Type, _type, Type);
		CC_SYNTHESIZE_READONLY(string, _name, Name);
		CC_SYNTHESIZE_READONLY(cocos2d::Value, _value, Value);
	};
}
#endif