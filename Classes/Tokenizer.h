#include "TestMacro.h"
#if  defined(TEST_TOKENIZER) \
	|| defined(DEBUG_ALL)

#define TEST_KAGWORD
#define TEST_TOKENIZER
#pragma once

#include <string>
#include <vector>
#include "KAGWord.h"


/*
 * phrase the string into words
 * return words
 *
 * there are three kind of lines
 * Scenario: *Demonstration(English)
 * Tag:		 [enterscene name=Schoolgate destroy=true fade=true]
 * Text:	 Nice to meet you.[p]
 */



class Tokenizer
{
public:
	/*
	enum class LineType
	{
		/* scenario note
		 * e.g. *start
		 */
//		SCENARIO,

		/* command
		 * e.g. [settext]
		 */
	//	COMMAND,

		 /* text
		  * e.g. Let's change her face.[p]
		  */

	//	TEXT
//	};


	//Tokenizer(std::string& str);
	//Tokenizer(const char* str);
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
	int _pos;
	string _line;
	KAGWords words;
	string _command;

	void readTag();
	void readAttribute();
	void readText();
	void readScenario();

	string nextString(int* npos);
	string nextString(const char* notes, int* npos);
};

#endif