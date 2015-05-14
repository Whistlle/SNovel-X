#include "TestMacro.h"

#if defined(TEST_KAG_PHRASER) \
	|| defined(DEBUG_ALL)
#define TEST_TOKENIZER
#define TEST_KAG_PHRASER
#pragma once

#include <string>
#include <list>
#include "cocos2d.h"
#include "Tokenizer.h"
#include "KAGTag.h"
#include "OpCode.h"
using namespace std;
/*
 * KAG Script Phraser
 * phrase the script to command
 */
class KAGPhraser
{
public:
	KAGPhraser(const string& stream);
	KAGPhraser();

	/* command list */
	list<string> ops;

	/* data list */
	cocos2d::ValueMap datum;

	void phrase();
	static vector<Opcode> phraseMessageTag(string& tag);
	void setStringStream(string& string) { scriptStream = string; }
private:
	void phraseALine(KAGWords& line);
	void phraseATag(int tagID, KAGWords& line);
	int phraseATagToID(string tag);

	void phraseScenario(KAGWords& line);
	void phraseText(KAGWords& line);

	
	/* the script file string stream*/
	string scriptStream;
	vector<KAGWords> phrasedLines;
	Tokenizer* _tokenizer;
	KAGTagManager* _tagManager;


};
#endif