#include "TagFactory.h"


namespace SNovel
{
	static TagFactory* _sharedTagFactory = nullptr;

	TagFactory* TagFactory::getInstance()
	{
		if (_sharedTagFactory == nullptr)
		{
			_sharedTagFactory = new TagFactory();
		}
		return _sharedTagFactory;
	}

	void TagFactory::regCreateFn(const string& name, BaseCreateFn func)
	{
		std::cout << "regCreateFn" << name << std::endl;
		//registry[name] = func;
		registry[name] = func;
	}

	AbstractTag* TagFactory::create(TagInfo& info, int lineNo) 
	{
		/*
		* tagName: 全小写  e.g. settext
		* ClassName 首字母大写 e.g. SettextTag
		*/

		string tagName = info.TagName;
		//tagName[0] = std::toupper(tagName.at(0));
		//tagName.append("Tag");

		AbstractTag* tag = nullptr;

		if (registry.find(tagName) != registry.end())
		{
			auto f = registry[tagName];
			//tag = std::make_shared<AbstractTag>(f()); 
			tag = f();
		}
		if (tag != nullptr)
		{
			tag->init(info, lineNo);
			tag->checkVital();
		}

		return tag;
	}
}