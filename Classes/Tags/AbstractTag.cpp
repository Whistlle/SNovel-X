#include "AbstractTag.h"

#include "ScriptEngine\ScriptEngine.h"

#ifdef TEST_ABS_TAG

namespace SNovel
{
	void AbstractTag::init(const TagInfo& info, int lineNo)
	{
		_tagInfo = info;
		LineInScript = lineNo;
		Params = _defaultParams;

		for (auto i : info.Params)
		{
			Params[i.first] = i.second;
		}
	}

	void AbstractTag::checkVital()
	{
		bool hasError = false;
		vector<string> errorParams;
		for (auto key : _vitalParams)
		{
			if (Params.find(key) == Params.end())
			{
				errorParams.push_back(key);
				hasError = true;
			}
		}
		if (!hasError)
		{
			return;
		}
		string line("[");
		line.append(_tagInfo.TagName);

		for (auto i : _tagInfo.Params)
		{
			line.append(" ");
			line.append(i.first + string("=") + i.second.asString());
		}
		Debug::logFormat("line:%d %s\nERROR: Do not contain vital param", LineInScript, line);
		for (string p : errorParams)
		{
			Debug::logFormat("Miss Param:%s", p);
		}
	}

	void AbstractTag::after()
	{
		Engine->nextCommand();
	}

	void AbstractTag::onFinishAnimation()
	{
		CCLOG("Finish Animation!");
		Engine->getStatus().EnableNextCommand = true;
		Engine->nextCommand();
	}
}

#endif