#if defined TEST_DIALOG_PART_DATA \
	|| DEBUG_ALL

#define TEST_SCRIPTED_VALUE
#define TEST_DIALOG_TEXT_NODE
#define TEST_DIALOG_ACTION_TYPE
#define TEST_IXML_SCRIPTED_DATA

#pragma once
#include "cocos2d.h"
#include "ScriptedValue.h"
#include "DialogTextNode.h"
#include "DialogActionType.h"
#include "IXMLScriptedData.h"

USING_NS_CC;
using namespace std;



/*  for example  */
/*
 * <DialogPartData active="false" dialogID="0" show="true" isName="false" isBGM="false" 
 isSE="false" isVoice="false" isAnim="false" isClearMessageAfter="true" textBoxID="0" 
 actionID="EnterScene">
        <toggle>false</toggle>
        <nameText /><dialogText /><bgmAudioKey /><seAudioKey /><voiceAudioKey /><bgmAudioID>0</bgmAudioID><seAudioID>0</seAudioID><voiceAudioID>0</voiceAudioID>
        <scene>
            <sceneName>Schoolgate</sceneName>
            <withFade>true</withFade>
            <clearSceneAndLoad>true</clearSceneAndLoad>
        </scene><enterActorEntries /><exitActorEntries /><enterEventData /><exitEventData /><inputData><varName /><rect><x>0</x><y>0</y><position><x>0</x><y>0</y></position><center><x>0</x><y>0</y></center><min><x>0</x><y>0</y></min><max><x>0</x><y>0</y></max><width>0</width><height>0</height><size><x>0</x><y>0</y></size><xMin>0</xMin><yMin>0</yMin><xMax>0</xMax><yMax>0</yMax></rect></inputData>
    </DialogPartData>
 */

class DialogPartData :public IXMLScriptedData
{
public:
	DialogPartData();

	DeclAttr(active);
	DeclAttr(dialogID);
	DeclAttr(show);
	DeclAttr(isName);
	DeclAttr(isBGM);
	DeclAttr(isSE);
	DeclAttr(isVoice);
	DeclAttr(isAnim);
	DeclAttr(isClearMessageAfter);
	DeclAttr(textBoxID);
	DeclAttr(actionID);
	DeclAttr(isChangeMotion);

	class ActorEntry : public IXMLScriptedData
	{
	public:
		ActorEntry(const char *valueName, std::vector<IXMLScriptedData*>& params):
			IXMLScriptedData(valueName, params)
		{
		}
		
		DeclProp(actorName);
		DeclProp(motion);
		DeclProp(withFade);
		//ActorPosition
	};

	class SceneEntry : public IXMLScriptedData
	{
	public:
		SceneEntry(const char *valueName, std::vector<IXMLScriptedData*>& params):
			IXMLScriptedData(valueName, params)
		{
		}
		
		DeclProp(sceneName);
		DeclProp(withFade);
		DeclProp(clearSceneAndLoad);
	};

	DeclCustomProp(actorEntry, ActorEntry);
	DeclCustomProp(sceneEntry, SceneEntry);
	DeclProp(textID);

	DialogTextData* dialogTextData;
	const std::string& getActorName() { return dialogTextData->name; }
	const std::string& getDialogText()  { return dialogTextData->text; }
	 
	DialogActionType actionType;
	
	/*  **condition**
	public class DialogEventData : ViNoEventData{
		public string targetObjectName;
		public string methodName;

		// Parameter strings.
		public string[] attr = null;	// key,value,key,value,....

		[HideInInspector] public bool condition;	// if condition is true , then flagName == isFlagTrue => Execute SendEvent .
		[HideInInspector] public string flagName;
		[HideInInspector] public bool isFlagTrue;
		[HideInInspector] public float delaySeconds;
	}*/

	//void setAttribute(const char* name, const char* value);
//	virtual void setParam(const char* name, const char* value) override;
	~DialogPartData();

	//virtual IXMLScriptedData* FirstChildElement();
//	virtual IXMLScriptedData* NextSiblingElement();
};

#endif