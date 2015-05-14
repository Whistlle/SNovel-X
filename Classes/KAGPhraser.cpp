#include "TestMacro.h"

#if		defined(TEST_KAG_PHRASER) \
	||  defined(DEBUG_ALL)
#define TEST_STRING_UTIL
#define TEST_TOKENIZER


#include "KAGPhraser.h"
#include "StringUtil.h"
#include "Tokenizer.h"
#include "OpCommand.h"
#include "ScriptEngine.h"
#include "KAGTagPhraser.h"

KAGPhraser::KAGPhraser()
{
	_tokenizer = new Tokenizer();
	_tagManager = new KAGTagManager();
}

KAGPhraser::KAGPhraser(const string& stream):
KAGPhraser()
{
	scriptStream = stream;
}

void KAGPhraser::phrase()
{
	vector<string> list;
	StringUtil::split(scriptStream, "\n"[0], list);

	int pos = 0;
	for (auto& line : list)
	{
		auto str = StringUtil::trim(line);
		if (!str.empty()){
			auto l = _tokenizer->getToken(str);
			phraseALine(l);
		}
	}
}

void KAGPhraser::phraseALine(KAGWords& line)
{
	auto op = line.at(0);
	if (op.getType() == KAGWord::Type::TAG)
	{
		auto tagID = phraseATagToID(op.getValue().asString());
		if (tagID != -1)
		{
			//CCLOG("tagID = %d", tagID);
			KAGTagPhraser::Phrase(tagID, line);
		}
	}
	else if (op.getType() == KAGWord::Type::SCENARIO)
	{
		phraseScenario(line);
	}
	else if (op.getType() == KAGWord::Type::TEXT)
	{
		phraseText(line);
	}
}

int KAGPhraser::phraseATagToID(string Tag)
{
	for (auto tag : _tagManager->getRegisteredTags())
	{
		if (tag.getTagName().compare(Tag) == 0)
			return tag.getID();
	}
	return -1;
}

void KAGPhraser::phraseScenario(KAGWords& line)
{
	OpCommand command(Opcode::SCENARIO);

	for (auto& word : line)
	{
		auto name = word.getName();
		if (name.compare("scenario") == 0)
		{
			command.params["scenario"] = word.getValue().asString();
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

void KAGPhraser::phraseText(KAGWords& line)
{
	OpCommand command(Opcode::PRINT);
	for (auto& word : line)
	{
		auto name = word.getName();
		if (name.compare("text") == 0)
		{
			command.params["text"] = word.getValue().asString();
		}
		else if (name.compare("op") == 0)
		{

			command.additionalOp = phraseMessageTag(word.getValue().asString());
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

//TODO: only [p] [r] exist now
vector<Opcode> KAGPhraser::phraseMessageTag(string& tag)
{
	vector<Opcode> ops;
	if (tag.compare("s") == 0)
	{
	//	ops.push_back(Opcode::STOP);
		return ops;
	}
	else if (tag.compare("cm") == 0)
	{
	//	ops.push_back(Opcode::CM);
		return ops;
	}
	else if (tag.compare("er") == 0)
	{
		ops.push_back(Opcode::PAGE);
		return ops;
	}
	else if (tag.compare("l") == 0)
	{
		ops.push_back(Opcode::WAIT_TOUCH);
		return ops;
	}
	else if (tag.compare("p") == 0)
	{
		ops.push_back(Opcode::WAIT_TOUCH);
		ops.push_back(Opcode::PAGE);
		return ops;
	}
	else if (tag.compare("r") == 0)
	{
		ops.push_back(Opcode::RELINE);
		return ops;
	}
	else if (tag.compare("endlink") == 0)
	{
		return ops;
	}
	else if (tag.compare("hidemessage") == 0)
	{
		return ops;
	}
}
#endif