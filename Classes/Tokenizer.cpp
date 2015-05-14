#include "TestMacro.h"
#if defined(TEST_TOKENIZER) \
	|| defined(DEBUG_ALL)

#define TEST_STRING_UTIL

#include "Tokenizer.h"
#include "StringUtil.h"

Tokenizer::Tokenizer()
{
}

void Tokenizer::init(const string& str)
{
	_pos = 0;
	_mode = Mode::GLOBAL;
	_line = str;
	words.clear();
}
KAGWords Tokenizer::getToken(const string& str)
{
	init(str);

	_pos = 0;

	//phrase scenario previously
	if (_line[_pos] == '*')
	{
		readScenario();
		return words;
	}

	
	while (1)
	{
		if (_line[_pos] == '[')
		{
			changeReadMode(Mode::TAG);
			++_pos;
		}
		else if (_line[_pos] == ']') //ignore '['
		{
			changeReadMode(Mode::GLOBAL);
			++_pos;
		}
		else if (_pos >= _line.size())
		{
			break;
		}

		switch (_mode)
		{
		case Tokenizer::Mode::GLOBAL:
			readText();
			break;
		case Tokenizer::Mode::TAG:
			readTag();
			break;
		case Tokenizer::Mode::ATTRIBUTE:
			readAttribute();
			break;
		default:
			CCLOG("WTF! another read mode?");
			break;
		}
		ignoreBlanks();
	}

	return words;
}

string Tokenizer::nextString(int* npos)
{
    string s =  StringUtil::nextString(_line, _pos, npos);
	_pos = *npos;
	return s;
}

string Tokenizer::nextString(const char* notes, int* npos)
{
	string s = StringUtil::nextStringStopUntil(_line, notes, _pos, npos);
	_pos = *npos;
	return s;
}
void Tokenizer::readAttribute()
{
//	CCLOG("read attribute");
	int npos = 0;
	auto op = nextString(" =", &npos);

	//if (op)
	{
		ignoreBlanks();
		if (_line[_pos] == '=')
		{
			++_pos;
			ignoreBlanks();
			auto value = nextString(" ]", &npos);
		//	auto value = StringUtil::nextStringStopUntil(_line, " ]", _pos, &npos);
		//	_pos = npos;
			
			KAGWord attr(KAGWord::Type::ATTRIBUTE, op, value);
			words.push_back(attr);
		}
		else
		{
			CCLOG("read attribute wrong! op = %s", op);
		}
	}
	//else
	//{
	//	CCLOG("read attribute wrong! no attribute name");
//	}
}

void Tokenizer::readTag()
{
//	CCLOG("read Tag!");
	int npos = 0;
	auto op = nextString(" ]", &npos);
	//if (op)
	{
		KAGWord tag(KAGWord::Type::TAG, "op", op);
		words.push_back(tag);
	}
	//else
	//{
//		CCLOG("read Tag wrong!");
//	}
	changeReadMode(Mode::ATTRIBUTE);
}

void Tokenizer::readText()
{
	int npos = 0;
//	CCLOG("read Text!");
	auto str = StringUtil::nextStringStopUntil(_line, "[\n", _pos, &npos);
	
	//auto str = nextString("[\n", &npos);
	//if (str)
	//{
	if (_pos < npos)
	{
		KAGWord tag(KAGWord::Type::TEXT, "text",  str);
		words.push_back(tag);
	}
	//}
	_pos = npos;
	changeReadMode(Mode::TAG);
}

void Tokenizer::readScenario()
{
	int npos;
	//auto str = StringUtil::nextStringStopUntil(_line, '[', _pos, &npos);
	auto str = nextString("[\n", &npos);
	KAGWord tag(KAGWord::Type::SCENARIO, "scenario", str);
	words.push_back(tag);
}
void Tokenizer::ignoreBlanks()
{
	while (_line[_pos] == ' '
		|| _line[_pos] == '\t')
	{
		++_pos;
	}
}

#endif