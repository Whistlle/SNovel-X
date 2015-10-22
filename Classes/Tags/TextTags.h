#pragma once
#include "Debug\TestMacro.h"

#include "AbstractTag.h"
#include "ScriptEngine\ScriptEngine.h"
#include "TagFactory.h"
#include "Core\TextBoxesManager.h"
#ifdef TEST_TEXT_TAGS
/*
* tag lists:
* print
* settext
* setname
* current
* reg_textbox
* [l]
* [cm]
* [p]
* [r]
*/
namespace SNovel
{
	/*
	* tag = print
	*
	* <desc>
	* 设置主文本框中的语句
	*
	* <param>
	* @text:   待显示的文本
	*
	* <sample>
	* Hello,World[p]
	*/
	class PrintTag : public AbstractTag
	{
	public:
		PrintTag()
		{
			_vitalParams = {
				"text"
			};

			_defaultParams.insert(
				{ "text", Value("") }
			);
		}

		void excute() override
		{
			TextBoxesManager::getInstance()->printText(Params["text"].asString());
			AbstractTag::excute();
		}
		void after() override
		{
			//AbstractTag::after();
		}
	};
	extern TagRegitser<PrintTag> _printTag;
	

	/*
	* tag = settext
	*
	* <desc>
	* 设置文本框内的语句
	*
	* <param>
	* @text:       待显示的文本
	* @textbox:    文本框名称
	*
	* <sample>
	* [settext text=Sachi textbox=TextBox_Name]
	*/
	/*
	class SettextTag : public AbstractTag
	{
	public:
		SettextTag()
		{
			_vitalParams = {
				"text"
			};

			_defaultParams = {
				{ "text", ""},
				{ "textbox", "" }
			};

		}

		void excute() override
		{
			TextBoxesManager.Instance.SetText(Params);
			AbstractTag::excute();
		}
	};
	TagRegitser<SettextTag> _settextTag("settext");
	*/
	/*
	* tag = setname
	*
	* <desc>
	* 显示人名
	*
	* <sample>
	* #Sachi
	*/
	class SetnameTag : public AbstractTag
	{
	public:
		SetnameTag()
		{
			_vitalParams = {
				"text"
			};

			_defaultParams = decltype(_defaultParams){
				{ "text", Value("") }
			};
		}

		void excute() override
		{
			TextBoxesManager::getInstance()->setName(Params["text"].asString());
			AbstractTag::excute();
		}
	};
	extern TagRegitser<SetnameTag> _setnameTag;

	/*
	* tag = current
	*
	* <desc>
	* 切换当前显示的主文本框
	*
	* <param>
	* @layer:  主文本框名称
	*
	* <sample>
	* [current layer=TextBox]
	*
	*/
	class CurrentTag : public AbstractTag
	{
	public:
		CurrentTag()
		{
			_vitalParams = {
				"layer"
			};

			_defaultParams = decltype(_defaultParams){
				{ "layer", Value("TextBox")}
			};
		}

		void excute() override
		{
			TextBoxesManager::getInstance()->current(Params);

			AbstractTag::excute();
		}
	};
	extern TagRegitser<CurrentTag> _currentTag;

	/*
	* tag = reg_textbox
	*
	* <desc>
	* 绑定textbox
	*
	* <param>
	* @objname:
	* @type:
	*
	* <sample>
	* [reg_textbox objname=TextBox_Name type=name]
	*
	*/
	//TODO: 真的需要这货嘛
	/*
    class Reg_textboxTag : public AbstractTag
	{
	public:
		Reg_textboxTag()
		{
			_defaultParams = {
				{ "objname", "" },
				{ "type", "main" }
			};
			_vitalParams = {
				"objname"
			};
		}

		void excute() override
		{
			Debug::logFormat("[Register TextBox]");
			AbstractTag::excute();
			TextBox t = TextBoxesManager.Instance.GetTextBoxInScene(Params["name"]);
			if (t == nullptr)
			{
				Debug::logFormat("Can not find TestBox:{0}", Params["name"]);
				return;
			}
			if (Params["type"] == "main")
			{
				TextBoxesManager.Instance.CurrentMainTextBox = t;
			}
			else if (Params["type"] == "name")
			{
				TextBoxesManager.Instance.CurrentNameTextBox = t;
			}
		}
	};

	TagRegitser<Reg_textboxTag> _currentTag("reg_textbox");
	*/

	/* ********************* Message Tag ******************* */
	/*
	* tag = l
	*
	* <desc>
	* 暂停等待继续
	*
	* <sample>
	* Hi,World.[l]
	*/
	class LTag : public AbstractTag
	{
	public:
		LTag()
		{
			_vitalParams = {};
			//_defaultParams = {};
		}

		void excute() override
		{
			//Do Nothing
			Debug::log("[l]");
			AbstractTag::excute();
		}
		void after() override 
		{
			Engine->getStatus().EnableNextCommand = false;
		}
	};
	extern TagRegitser<LTag> _lTag;
	

	/*
	* tag = cm
	*
	* <desc>
	* 清除主文本框中的文字
	*
	* <sample>
	* [cm]
	*
	*/
	class CmTag : public  AbstractTag
	{
	public:
		CmTag()
		{
			_vitalParams = {};
			//_defaultParams = {};
		}

		void excute() override
		{
			TextBoxesManager::getInstance()->clearMessage();

			AbstractTag::excute();
		}
	};
	extern TagRegitser<CmTag> _cmTag;
	
	/*
	* tag = p
	*
	* <desc>
	* 清除当前文本框内容并显示新的文本
	*
	* <sample>
	* Hello,World[p]
	*
	*/
	class PTag : public AbstractTag
	{
	public:
		PTag()
		{
			_vitalParams = {};
			//_defaultParams = {};
		}

		void before() override
		{
			AbstractTag::before();
			//    AbstractTag tag = TagFactory.CreateEmptyParamsTag("LTag", LineInScript);
			//   Engine.InsertCommandBefore(tag);
			//    Engine.SkipThisTag = true;
		}

		void excute() override
		{
			Debug::log("[p]");
			TextBoxesManager::getInstance()->clearMessage();
			AbstractTag::excute();
		}

		void after() override
		{
			Engine->getStatus().EnableNextCommand = false;
		}
	};
	extern TagRegitser<PTag> _pTag;
	

	/*
	* tag = r
	*
	* <desc>
	* 在当前文本框显示基础上换行显示新文本
	* 默认为[r]
	*
	* <sample>
	* Hello,World[r]
	*
	*/
	class RTag : public AbstractTag
	{
	public: 
		RTag()
		{
			_vitalParams = {};
			//_defaultParams = {};
		}

		void before() override
		{
			AbstractTag::before();
			//    AbstractTag tag = TagFactory.CreateEmptyParamsTag("LTag", LineInScript);
			//    Engine.InsertCommandBefore(tag);
			//    Engine.SkipThisTag = true;
		}

		void excute() override
		{
			//CCLOG("[r]");
			Debug::log("[r]");
			TextBoxesManager::getInstance()->reline();
			AbstractTag::excute();
		}

		//void after() override
		//{
			//Engine->getStatus().EnableNextCommand = true;
		//}
	};
	extern TagRegitser<RTag> _rTag;

	/* ********************* Message Tag ******************* */
}
#endif
