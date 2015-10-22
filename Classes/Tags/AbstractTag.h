#pragma once

#include "Debug\TestMacro.h"

#ifdef TEST_ABS_TAG

#include <string>
#include <vector>
#include <unordered_map>

#include "cocos2d.h"

using std::vector;
using std::string;
using std::unordered_map;
using cocos2d::Ref;
using cocos2d::ValueMap;

namespace SNovel
{
    class Debug
	{
	public:
		static void logFormat(const char* str, ...)
		{
			//
		}
		static void log(string log)
		{
			CCLOG(log.c_str());
		}

		//assert 对的条件
		static void assertCond(bool cond, const char* msg)
		{
			CCASSERT(cond, msg);
		}
	};
	
	struct TagInfo
	{
		string TagName;
		ValueMap Params;
		TagInfo() = default;
		TagInfo(string name):
			TagName(name)
		{
			
		}
	};

	class ScriptEngine;

	class AbstractTag: public Ref
	{
	protected:
		ValueMap _defaultParams;
		vector<string> _vitalParams;

		
		TagInfo _tagInfo;
	public:
		AbstractTag() : Ref()
		{

		}

		ValueMap Params;

		void init(const TagInfo& info, int lineNo);

		int LineInScript;

		ScriptEngine* Engine = nullptr;

		void checkVital();

		string getName() const
		{
			return _tagInfo.TagName;
		}

	public:
		virtual void before()   {}
		virtual void excute()   {}
		virtual void complete() {}
		virtual void after();
		virtual void onFinishAnimation();
	};

}
#endif