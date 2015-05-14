#include "KAGTagPhraser.h"


#if defined(TEST_KAG_TAG_PHRASER) \
	|| defined(DEBUG_ALL)

#include "KAGPhraser.h"

void KAGTagPhraser::Phrase(int tagID, KAGWords& line)
{
	switch (tagID){
	case KAGTagManager::tag_wait:			OnWaitTag(line);	break;
	case KAGTagManager::tag_link:			OnLinkTag(line);	break;
	case KAGTagManager::tag_jump:
	case KAGTagManager::tag_layopt:
	case KAGTagManager::tag_loadscene:
	case KAGTagManager::tag_current:		OnCurrentTag(line); break;
	case KAGTagManager::tag_anim:
	case KAGTagManager::tag_object:
	case KAGTagManager::tag_instantiate:
	case KAGTagManager::tag_loadlevel:

	case KAGTagManager::tag_sendevent:
	case KAGTagManager::tag_image:
	case KAGTagManager::tag_condition:
	case KAGTagManager::tag_setflag:
	case KAGTagManager::tag_destroy:
	case KAGTagManager::tag_getuserinput:
	case KAGTagManager::tag_definescene:
	case KAGTagManager::tag_defineactor:
	case KAGTagManager::tag_font:
	case KAGTagManager::tag_eval:
	case KAGTagManager::tag_if_:
	case KAGTagManager::tag_endif:
	case KAGTagManager::tag_setpropactor:
	case KAGTagManager::tag_enterscene:
	case KAGTagManager::tag_enteractor:
	case KAGTagManager::tag_addstate:
	case KAGTagManager::tag_moveactor:
	case KAGTagManager::tag_exitactor:
	case KAGTagManager::tag_exitscene:
	
	case KAGTagManager::tag_showsystemui:
	case KAGTagManager::tag_hidesystemui:
	case KAGTagManager::tag_changestate:
	case KAGTagManager::tag_stopbgm:
	case KAGTagManager::tag_shake:
	case KAGTagManager::tag_playbgm:
	case KAGTagManager::tag_playse:
	case KAGTagManager::tag_playvoice:
	case KAGTagManager::tag_xchgbgm:
	case KAGTagManager::tag_fadoutbgm:
	case KAGTagManager::tag_trans:
			OnTriggerEventWithArgsTag(line);
			break;
	case KAGTagManager::tag_settext:
		OnSetTextTag(line);
		break;
	default: //custom tag
		break;
	}
}

//milliSec
void KAGTagPhraser::OnWaitTag(KAGWords& line)
{
	OpCommand command(Opcode::WAIT);

	for (auto& word : line)
	{
		if (word.getName().compare("time") == 0)
		{
			auto milliSec = word.getValue().asFloat();
			float sec = (float)milliSec / 1000;
			command.params["time"] = sec;
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

void KAGTagPhraser::OnLinkTag(KAGWords& line)
{
	OpCommand command(Opcode::LINK);
	for (auto& word : line)
	{
		if (word.getName().compare("target") == 0)
		{
			command.params["target"] = word.getValue();
		}
		else if (word.getName().compare("text") == 0)
		{
			command.params["text"] = word.getValue();
		}
		else if (word.getName().compare("op") == 0)
		{
			if (word.getValue().asString().compare("endlink") != 0
				 && word.getValue().asString().compare("link") != 0) //ignore endlink
			{
				auto tag = KAGPhraser::phraseMessageTag(word.getValue().asString());
				command.additionalOp = tag;
			}
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

void KAGTagPhraser::OnCurrentTag(KAGWords& line)
{
	OpCommand command(Opcode::CURRENT);
	for (auto& word : line)
	{
		if (word.getName().compare("layer") == 0)
		{
			command.params["layer"] = word.getValue();
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

void KAGTagPhraser::OnTriggerEventWithArgsTag(KAGWords& line)
{
	OpCommand command(Opcode::MESSAGING);
	for (auto& word : line)
	{
		if (word.getName().compare("op") == 0)
		{
			string eventType = "EVENT_";
			for (auto& c : word.getValue().asString())
			{
				eventType.push_back(toupper(c));
			}

			command.params["eventType"] = eventType;
		}
		else
		{
			command.params[word.getName()] = word.getValue();
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}

void KAGTagPhraser::OnSetTextTag(KAGWords& line)
{
	OpCommand command(Opcode::SET_TEXT);
	for (auto& word : line)
	{
		if (word.getName().compare("text") == 0)
		{
			command.params["text"] = word.getValue().asString();

		}
		else if (word.getName().compare("textbox") == 0)
		{
			command.params["textbox"] = word.getValue().asString();
		}
		else if (word.getName().compare("op") == 0)
		{
			if (word.getValue().asString().compare("r") == 0)
				command.additionalOp = vector < Opcode > {Opcode::RELINE};
		}
	}
	ScriptEngine::getInstance()->addCommand(command);
}






#endif
