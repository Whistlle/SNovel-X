#ifdef TEST_DIALOG_PART_DATA \
	|| DEBUG_ALL

#define TEST_DIALOG_PART_NODE

#include "DialogPartData.h"
#include "DialogTextNode.h"

DialogPartData::DialogPartData() :IXMLScriptedData("DialogPartData")
{
}

DialogPartData::~DialogPartData()
{
	delete actorEntry;
	delete sceneEntry;
}

#endif

