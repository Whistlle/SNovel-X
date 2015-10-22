#pragma once

#include "Debug\TestMacro.h"

#ifdef TEST_SYS_TAGS

#include <vector>

#include "Tags\AbstractTag.h"
#include "Tags\TagFactory.h"
#include "ScriptEngine\ScriptEngine.h"

#include "base\CCValue.h"
using cocos2d::Value;

/*
 * tag lists:
 * [scenario]
 * [s]
 * [select_new]
 * [select_show]
 * [jump] 
 * [wait]
*/

namespace SNovel
{
	/*
	* tag = scenario
	*
	* <desc>
	*  记录以下内容为一个新片段，供跳转等实现
	*
	* <sample>
	* *Demonstration(English)/START/1_Dialog
	*
	*/
	class ScenarioTag : public AbstractTag
	{
	public:
		ScenarioTag()
		{
			_vitalParams =  {
				"scenario"
			};
			/*  error C2593: 'operator =' is ambiguous?
			_defaultParams =  {
				{ "scenario", Value("") }
			};
			*/
			_defaultParams.insert({ "scenario", Value("") });
		}

		virtual void excute() override
		{
			Debug::logFormat("[Scenario]: {0}", Params["scenario"]);
			//Done By ScriptEngine
			/*
			if(Params.ContainsKey("scenario"))
			{
			string scenarioName = Params["scenario"];
			Engine.AddScenario(scenarioName);
			}*/

			AbstractTag::excute();
		}
	};
	extern TagRegitser<ScenarioTag> _scenarioTag;

	/*
	* tag = select_show
	*
	* <desc>
	* 显示脚本前面[select_show]的选择肢
	*
	* <sample>
	* [select_show]
	*
	*/
	/*
	class Select_showTag : public AbstractTag
	{
	public:
		Select_showTag()
		{
			//_defaultParams = {
			//};

			//_vitalParams = {
			//};
		}

	    virtual void excute() override
		{
			UIManager.Instance.ShowSelects();
			AbstractTag::excute();
		}
	};
	TagRegitser<Select_showTag> _select_showTag("select_show");
	*/
	/*
	* tag = select_new
	*
	* <desc>
	* 创建新的选择肢
	*
	* <param>
	* @target: 点击后跳转的Scenario标签
	* @text:   标签上显示的文字
	*
	* <sample>
	* [select_new  target=*select_a1]Nico~[end]
	*
	*/
	/*
	class Select_newTag : public AbstractTag
	{
	public:
		Select_newTag()
		{
			_defaultParams = {
				{ "target", "" },
				{ "text", "" }
			};

			_vitalParams = {
				"target"
			};
		}

		virtual void excute() override
		{
			string target = Params["target"];
			UIManager.Instance.AddSelect("button", Params["text"]
										 , () = >
			{
				Engine.JumpToScenario(target);
				UIManager.Instance.ClearSelects();
			}
			);
			AbstractTag::excute();
		}

	};
	TagRegitser<Select_newTag> _select_newTag("select_new");
	*/
	/*
	* tag = jump
	*
	* <desc>
	* 跳转到Param["target"]的Scenario处
	*
	* <param>
	* @target: Target scenario to jump
	*
	* <sample>
	* *select_niko
	* [jump target=*select_niko]
	*
	*/

	class JumpTag : public AbstractTag
	{
		public:
		JumpTag()
		{
			_defaultParams.insert(
				{ "target", Value("") }
			);
				
			_vitalParams = {
				"target"
			};
		}
		virtual void excute() override
		{
			AbstractTag::excute();
		}
		virtual void after() override
		{
			Engine->jumpToScenario(Params["target"].asString());
			//Do Not CurrentLine + 1
			//base.After();
		}
	};
	extern TagRegitser<JumpTag> _jumpTag;

	/*
	* tag = wait
	*
	* <desc>
	* 暂停指定时间后继续
	*
	* <param>
	* @time:   需要等待的时间，单位为秒
	*
	* <sample>
	* [wait time=1000]
	*
	*/
    class WaitTag : public AbstractTag
	{
	public:
		WaitTag()
		{
			_defaultParams.insert(
				{ "time", Value(0) }
			);

			_vitalParams = {
				"time"
			};
		}

		virtual void excute() override
		{
			Debug::logFormat("Wait: {0}ms", Params["time"]);
			Engine->getStatus().EnableNextCommand = false;

			/* TODO: DelayToInvoke */
			//Engine->StartCoroutine(Util.DelayToInvoke(this.OnFinishAnimation, int.Parse(Params["time"]) / 1000f));
		}

		virtual void after() override
		{
			//Do Nothing
		}

		virtual void onFinishAnimation() override
		{
			Debug::log("Wait Finish!");
			Engine->getStatus().EnableNextCommand = true;
			Engine->nextCommand();
		}
	};
	extern TagRegitser<WaitTag> _waitTag;


	/*
	* tag = s
	*
	* <desc>
	* 脚本运行到此处时停止
	*
	* <sample>
	*
	* [select num = 2]
	* [select_new  target=*select_a1]View from the beginning.[end]
	* [select_new  target=*select_a2]Finish this demo.[end]
	* [s]
	*
	*/
	class STag : public AbstractTag
	{
	public:
		STag()
		{
		}

		virtual void excute() override
		{
			AbstractTag::excute();

			Engine->getStatus().EnableClickContinue = false;
			Engine->getStatus().EnableNextCommand = false;
		}
	};	
	extern TagRegitser<STag> _sTag;
}

#endif