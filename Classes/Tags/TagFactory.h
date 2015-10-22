#pragma once

#include <unordered_map>
//#include <memory>
#include <functional>
#include <cctype>
#include <iostream>

#include "base\CCVector.h"
#include "AbstractTag.h"
using std::unordered_map;
using std::function;

using cocos2d::Vector;

namespace SNovel
{
	//对Tag的内存管理使用cocos的Ref形式
	//因为直接投入Vector中，其他地方无需保持强引用，故不用RefPtr
	class TagFactory
	{
		typedef function<AbstractTag*()> BaseCreateFn;
		typedef unordered_map<string, BaseCreateFn> FnRegistry;
		FnRegistry registry;
		

	public:
		
		static TagFactory* getInstance();

		void regCreateFn(const string& name, BaseCreateFn func);

		AbstractTag* create(TagInfo& info, int lineNo);
	};

	template<class DevTag>
	class TagRegitser
	{
	public:
		static AbstractTag* createInstance()
		{
			std::cout << " createInstance" << std::endl;
			//check type
			//Debug::assertCond(dynamic_cast<AbstractTag*>(DevTag*) != nullptr);
			auto d = new DevTag();
			return d;
		}

		TagRegitser(const string& str)
		{
			TagFactory::getInstance()->regCreateFn(str, []()
			{
				return TagRegitser::createInstance();
			});
		}
	};
}