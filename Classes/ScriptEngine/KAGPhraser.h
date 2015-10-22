#pragma once
#include "Debug\TestMacro.h"


#if defined(TEST_KAG_PHRASER) \
	|| defined(DEBUG_ALL)
#define TEST_TOKENIZER
#define TEST_KAG_PHRASER


#include <string>
#include <list>

//#include "cocos2d.h"
#include "base\CCVector.h" 
#include "base\CCRefPtr.h"

#include "ScriptEngine\Tokenizer.h"
#include "Core\Chapter.h"
#include "Tags\AbstractTag.h"

using namespace std;
using cocos2d::RefPtr;
/*
 * KAG Script Phraser
 * phrase the script to command
 */

namespace SNovel
{
	/*
	 * 单例, 给Chapter::phrase使用
	 */
	class KAGPhraser
	{
	public:
		static KAGPhraser* getInstance();

		//sharedptr 在cocos中有RTTI
		//直接拷贝vector?
		Vector<AbstractTag*> phrase(RefPtr<Chapter> s);

	private:
		KAGPhraser();
		~KAGPhraser();
		void phrase();
		void phraseALine(const KAGWords& line);
		void phraseText(const KAGWords& line);
		void phraseName(const KAGWords&  line);
		void CreateAndSendTagToEngine(TagInfo& tagInfo);
		//void phraseATag(int tagID, KAGWords& line);
		
		void reset();
		//void phraseScenario(KAGWords& line);
		

		//int phraseATagToID(string tag);
		/* the script file string stream*/
		//vector<KAGWords> phrasedLines;
		string				 _scriptStream;
		int					 _currentPhraseLineNo;
		Tokenizer*			 _tokenizer;
		RefPtr<Chapter>		 _scene;
		Vector<AbstractTag*> _uploadTags;
	};
}
#endif