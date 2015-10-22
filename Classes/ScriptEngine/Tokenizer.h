//#include "TestMacro.h"
#define TEST_TOKENIZER
#if  defined(TEST_TOKENIZER) \
	|| defined(DEBUG_ALL)

#define TEST_KAGWORD
#define TEST_TOKENIZER
#pragma once

#include <string>
#include <vector>

#include "ScriptEngine\KAGWord.h"

namespace SNovel
{

	/*
	* phrase the string into words
	* return words
	*
	* there are three kind of lines
	* Scenario: *Demonstration(English)
	* Tag:		[enterscene name=Schoolgate destroy=true fade=true]
	* Text:		Nice to meet you.[p]
	*
	* see [p][r] as a tag
	*
	* add:
	* ¡¤ use '@' to set tag. Now you can use @ or [] to set tag
	*   e.g. @enterscene name=Schoolgate destroy=true fade=true
	* ¡¤ use '//' to set commit
	* ¡¤ use '#' to print name text conveniently. instead of [settext]
	*   e.g. #Sachi
	*/

	class Tokenizer
	{
	public:

		Tokenizer();

		KAGWords getToken(const string& str);

		void ignoreBlanks();

	private:
		void init(const string& str);
		enum class Mode
		{
			GLOBAL,
			TAG,
			ATTRIBUTE
		};
		
		void changeReadMode(Mode mode) { _mode = mode; }

		Mode _mode;
		size_t _pos;
		string _line;
		KAGWords _words;
		string _command;

		void readTag();
		void readAttribute();
		void readText();
		void readScenario();
		void readName();

		string nextString(int* npos);
		string nextString(const char* notes, int* npos);
	};
}
#endif