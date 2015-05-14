#pragma once
#include "TestMacro.h"

#if defined(TEST_KAG_TAG_PHRASER) \
	|| defined(DEBUG_ALL)

#define TEST_KAG_TAG_PHRASER
#include "OpCommand.h"
#include "ScriptEngine.h"
#include "KAGWord.h"
#include "KAGTag.h"



class KAGTagPhraser
{
public:
	static void Phrase(int tagID, KAGWords& line);
private:

	static void OnWaitTag(KAGWords& line);
	static void OnLinkTag(KAGWords& line);
	static void OnCurrentTag(KAGWords& line);
	static void OnTriggerEventWithArgsTag(KAGWords& line);
	static void OnSetTextTag(KAGWords& line);
};
#endif
