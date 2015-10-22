#include "Debug\TestMacro.h"

#if		defined(TEST_KAG_PHRASER) \
	||  defined(DEBUG_ALL)

#include <string>
#include "KAGPhraser.h"
#include "Util\StringUtil.h"
#include "Tags\TagFactory.h"
#include "Core\Chapter.h"

namespace SNovel
{
	static KAGPhraser* _sharedKAGPhraser = nullptr;

	KAGPhraser* KAGPhraser::getInstance()
	{
		if (_sharedKAGPhraser == nullptr)
		{
			_sharedKAGPhraser = new KAGPhraser();
		}
		return _sharedKAGPhraser;
	}

	KAGPhraser::KAGPhraser()
	{
		_tokenizer = new Tokenizer();
	}
	 
	KAGPhraser::~KAGPhraser()
	{
		delete _tokenizer;
	}
	
	/*
	KAGPhraser::KAGPhraser(const string& stream) :
		KAGPhraser()
	{
		_scriptStream = stream;
	}
	*/
	void KAGPhraser::reset()
	{
		_scene.reset();
		_currentPhraseLineNo = 0;
		_uploadTags.clear();
	}

	Vector<AbstractTag*> KAGPhraser::phrase(RefPtr<Chapter> c)
	{
		reset();

		_scriptStream = c->getScriptContent();

		_scene = c;

		phrase();

		return _uploadTags;
	}

	void KAGPhraser::phrase()
	{
		vector<string> list;
		StringUtil::split(_scriptStream, '\n', list);
		for (auto& line : list)
		{
			string str = StringUtil::trim(line);
			if (str == "")
			{
				_currentPhraseLineNo++;
				continue;
			}
			KAGWords l = _tokenizer->getToken(str);
			if (!l.empty())
			{
				phraseALine(l);
			}
			_currentPhraseLineNo++;
		}
	}

	void KAGPhraser::phraseALine(const KAGWords& line)
	{
		auto op = line.at(0);
		
		if (op.getType() == KAGWord::Type::TEXT)
		{
			phraseText(line);
		}
		else if (op.getType() == KAGWord::Type::NAME)
		{
			phraseName(line);
		}
		else
		{
			//Tag
			//strlwr:ansi version unicode may wrong
			TagInfo info(StringUtil::tolower(op.getValue().asString()));
			for (auto& param : line)
			{
				if (&op != &param)
				{
					info.Params[param.getName()] = param.getValue().asString();
				}
				
			}
			CreateAndSendTagToEngine(info);
		}
	}


	void KAGPhraser::phraseText(const KAGWords& line)
	{
		TagInfo info("print");

		for (auto& word : line)
		{
			auto& name = word.getName();
			if (name == "text")
			{
				info.Params["text"] = word.getValue().asString();
				CreateAndSendTagToEngine(info);
			}
			else if (name == "tag" && word.getValue().asString() != "print")
			{
				TagInfo info1(StringUtil::tolower(word.getValue().asString()));
				CreateAndSendTagToEngine(info1);
			}
		}
	}

	void KAGPhraser::phraseName(const KAGWords& line)
	{
		TagInfo info("setname");
		for (auto& word : line)
		{
			auto& name = word.getName();
			if (name == "text")
			{
				info.Params["text"] = word.getValue().asString();
				CreateAndSendTagToEngine(info);
			}
		}
	}
	void KAGPhraser::CreateAndSendTagToEngine(TagInfo& tagInfo)
	{
		auto tag = TagFactory::getInstance()->create(tagInfo, _currentPhraseLineNo);
		if (tag != nullptr)
		{
			_scene->addCommand(tag);
		}
		else
			Debug::logFormat("Tag:%s is not implemented!", tagInfo.TagName);
	}
}
#endif