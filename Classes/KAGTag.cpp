#include "KAGTag.h"

#if defined(TEST_KAG_TAG) \
	|| defined(DEBUG_ALL)


aKAGCustomTag::aKAGCustomTag(const char* name, int ID, std::vector<aKAGTag>& tags):
aKAGTag(name, ID, tags)
{

}
KAGTagManager::KAGTagManager()
{

}

void KAGTagManager::registerCustomTag(const char* TagName, std::function<void(KAGWords)> tagCallback)
{
	auto id = getNextTagId();
	aKAGCustomTag tag(TagName, id, _tagHolder);  
	tag.setTagCallback(tagCallback);
}

int KAGTagManager::getNextTagId()
{
	int id = _tagHolder.at(_tagHolder.size()-1).getID();
	return id + 1;
}
#endif
