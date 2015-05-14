#ifdef TEST_DIALOG_TEXT_NODE \
	|| DEBUG_ALL

#include "DialogTextNode.h"
#include "json\rapidjson.h"
#include "json\document.h"

using namespace rapidjson;


DialogTextData::DialogTextData() :
textNo(-1),
scenarioNo(-1),
selectionNo(-1)
{
}

DialogTextNode::DialogTextNode():
scenarioCount(-1),
_currentScenario(-1)
{
}

//eg: SceneNo:1.1.1
//SceneNo.SelctionNo.TextNo

RefPtr<DialogTextNode>  _sharedDialogPartNode = nullptr;

DialogTextNode* DialogTextNode::getInstance()
{
	if (_sharedDialogPartNode == nullptr)
	{
		_sharedDialogPartNode = new DialogTextNode();
	}
	return _sharedDialogPartNode;
}

void DialogTextNode::loadDatum(int ScenarioNo)
{
	_currentScenario = ScenarioNo;
	char path[100];
	sprintf(path, "dialogText/%d.json", ScenarioNo);
	auto filePath = FileUtils::getInstance()->fullPathForFilename(path);
	CCLOG("filepath = %s", filePath.c_str());
	auto file = FileUtils::getInstance()->getStringFromFile(filePath);
	Document d;
	d.Parse<0>(file.c_str());
	
	if (d.HasParseError())
	{
		CCLOG("GetParseError%s\n", d.GetParseError());
	}
	if (!d.IsObject())
		return;

	selectionNo = 1;
	int textIndex = 0;
	_selectionBegin.push_back(textIndex);
	char str[5];
	sprintf(str, "%d", selectionNo);

	rapidjson::Value& selection = d[str];
	do
	{
		if (selection.IsArray())
		{
			for (int i = 0; i < selection.Capacity(); ++i)
			{
				auto dialogTextData = new DialogTextData();
				rapidjson::Value& textData = selection[i];
				if (textData.HasMember("No"))
				{
					dialogTextData->textNo = textData["No"].GetInt();
				}
				if (textData.HasMember("name"))
				{
					dialogTextData->name = textData["name"].GetString();
				}
				if (textData.HasMember("dialogText"))
				{
					dialogTextData->text = textData["dialogText"].GetString();
				}
				_dialogTextDatum.push_back(dialogTextData);
				dialogTextData->scenarioNo = ScenarioNo;
				dialogTextData->selectionNo = selectionNo;

				CCLOG("[textNo:%d, name:%s, text:%s]", dialogTextData->textNo,
					dialogTextData->name.c_str(), dialogTextData->text.c_str());
				textIndex++;
			}
		}
		++selectionNo;
		sprintf(str, "%d", selectionNo);
		selection = d[str];
		_selectionBegin.push_back(textIndex);
		CCLOG("Current Selection:%d, Text Index: %d", selectionNo, textIndex);
		if (!selection.IsArray())
			break;	
	} while (1);
}

DialogTextData* DialogTextNode::getDialogTextData(const std::string& textID)
{
	int text, scenario, selection;
	sscanf(textID.c_str(), "%d.%d.%d", &scenario, &selection, &text);
	if (_currentScenario == -1)
	{
		loadDatum(scenario);
	}
	//TODO
	CCASSERT(scenario == _currentScenario, "scenario error! get text failed");

	auto selectionStart = _selectionBegin.at(selection - 1);

	auto index = selectionStart + text - 1;
	if (index < _dialogTextDatum.size())
		return _dialogTextDatum.at(index);
}

#endif