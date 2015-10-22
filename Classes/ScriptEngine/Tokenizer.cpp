//#include "TestMacro.h"
#include "Tokenizer.h"
#if defined(TEST_TOKENIZER) \
	|| defined(DEBUG_ALL)

#define TEST_STRING_UTIL

 

#include "Util\StringUtil.h"

namespace SNovel
{
	Tokenizer::Tokenizer()
	{
	}

	void Tokenizer::init(const string& str)
	{
		_pos = 0;
		_mode = Mode::GLOBAL;
		_line = str;
		_words.clear();
	}

	KAGWords Tokenizer::getToken(const string& str)
	{
		init(str);

		_pos = 0;

		//phrase scenario previously
		if (_line[_pos] == '*')
		{
			readScenario();
			return _words;
		}
		else if (_line[_pos] == '#')
		{
			readName();
			return _words;
		}
		else if (_line[0] == '/' && _line[1] == '/')
		{
			//commit
			return _words;
		}


		while (true)
		{
			if (_pos >= _line.size())
			{
				break;
			}
			else if (_line[_pos] == '[')
			{
				changeReadMode(Mode::TAG);
				++_pos;
			}
			else if (_line[_pos] == ']') //ignore '['
			{
				changeReadMode(Mode::GLOBAL);
				++_pos;
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

		return _words;
	}

	string Tokenizer::nextString(int* npos)
	{
		string s = StringUtil::nextString(_line, _pos, npos);
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

				KAGWord attr(op, value);
				_words.push_back(attr);
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
			KAGWord tag(KAGWord::Type::TAG, op);
			//KAGWord attri("tag", op);
			_words.push_back(tag);
			//_words.push_back(attri);
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
			KAGWord tag(KAGWord::Type::TEXT, "print");
			KAGWord attri("text", str);
			_words.push_back(tag);
			_words.push_back(attri);
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
		KAGWord tag(KAGWord::Type::TAG, "scenario");
		KAGWord attri("scenario", str);
		_words.push_back(tag);
		_words.push_back(attri);
	}

	void Tokenizer::readName()
	{
		int npos = 0;
		KAGWord tag1(KAGWord::Type::NAME, "setname");

		_words.push_back(tag1);

		if (_line == "#")
		{
			//tag1 = KAGWord(KAGWord::Type::NAME);
		}
		else
		{	
			string str = StringUtil::nextStringStopUntil(_line, "[\n", _pos + 1, &npos);
			KAGWord tag2("text", str);
			_words.push_back(tag2);
		}

		
	}
	void Tokenizer::ignoreBlanks()
	{
		while (_line[_pos] == ' '
			   || _line[_pos] == '\t')
		{
			++_pos;
		}
	}
}
#endif