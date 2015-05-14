#ifdef TEST_DIALOG_PART_NODE \
	|| DEBUG_ALL

#define TEST_DIALOG_ACTION_COMMAND
#define TEST_ACTION_QUEUE
#define TEST_SCENE_CTRL
#define TEST_DIALOG_TEXT_NODE

#include "DialogPartNode.h"
#include "tinyxml2\tinyxml2.h"
#include "DialogActionCommand.h"
#include "ActionQueue.h"
#include "SceneCtrl.h"
#include "DialogTextNode.h"


DialogPartNode::DialogPartNode(const char* fileName)
{
	loadDialogPartDatum(fileName);
}
void DialogPartNode::loadDialogPartDatum(const char *fileName)
{
	std::string path = FileUtils::getInstance()->fullPathForFilename(fileName);
	auto doc = new tinyxml2::XMLDocument();
	auto errorid = doc->LoadFile(path.c_str());
	CC_ASSERT(errorid == 0);
	
	auto root = doc->RootElement();
	auto data = root->FirstChildElement();
	_loadedDatum.clear();

	do
	{
		partdata = new DialogPartData();
		readChildElement(data, partdata);
		pharseTextID(partdata);
		_loadedDatum.push_back(partdata);
		_actionCounter++;
		data = data->NextSiblingElement();
	}while (data);
}

void DialogPartNode::readChildElement(tinyxml2::XMLElement* data)
{
	if (data)
	{
		auto attribute = data->FirstAttribute();
		CCLOG("%s, %s", data->Name(), data->GetText());
		while (attribute)
		{
			partdata->setAttribute(attribute->Name(), attribute->Value());
			CCLOG("%s, %s", attribute->Name(), attribute->Value());
			attribute = attribute->Next();
		}
		auto param = data->FirstChildElement();
		
		while (param)
		{
			//若有子元素，递归设置子元素
			if (partdata->hasChildElement())
			{
				readChildElement(param, partdata->FirstChildElement());
			}
			else
			{
				partdata->setValue(param->Name(), param->GetText());
			}
			param = param->NextSiblingElement();
		}
	}
}

void DialogPartNode::readChildElement(tinyxml2::XMLElement* data, IXMLScriptedData* scriptedata)
{
	if (data)
	{
		auto attribute = data->FirstAttribute();
		//CCLOG("%s, %s", data->Name(), data->GetText());
		while (attribute)
		{
			scriptedata->setAttribute(attribute->Name(), attribute->Value());
		//	CCLOG("%s, %s", attribute->Name(), attribute->Value());
			attribute = attribute->Next();
		}
		auto param = data->FirstChildElement();

		while (param)
		{
			//若有子元素，递归设置子元素
			if (scriptedata->hasChildElement(param->Name()))
			{
				CCLOG("    [set %s]    ", param->Name());
				readChildElement(param, scriptedata->getChildElement(param->Name()));
			}
			else
			{
				scriptedata->setValue(param->Name(), param->GetText());
			}
			param = param->NextSiblingElement();
		}
	}
}

DialogPartData* DialogPartNode::getAction(int actionNumber)
{
	if (actionNumber < _actionCounter)
		return _loadedDatum.at(actionNumber);
	else
		return nullptr;
}

void DialogPartNode::pharseToAction()
{
	for (auto data : _loadedDatum)
	{
	}
}

void DialogPartNode::pharseTextID(DialogPartData* data)
{
	auto textID = data->textID->getValue().asString();
	data->dialogTextData = DialogTextNode::getInstance()->getDialogTextData(textID);
}

#endif