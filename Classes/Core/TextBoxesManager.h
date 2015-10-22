#include "Debug\TestMacro.h"

#if defined(TEST_TEXTBOXES_MANAGER) 

#pragma once


#include "UI/TextBox.h"
#include "cocos2d.h"

#include <string>

using std::string;
using cocos2d::ValueMap;

namespace SNovel
{
	

	class TextBoxesManager
	{
	public:
		enum class TextBoxType
		{
			MAIN,
			NAME,
			OTHER
		};

		static TextBoxesManager* getInstance();
		
		void add(TextBox* textbox, const char* textBoxName, TextBoxType type);

	//	void createTextBox(const string& type);

		void setSetTextCallback();

		TextBox* getTextBoxInScene(const std::string& name);// { return _currentMainTextBox; }

		//change current main text box
		void current(ValueMap& data);
		//tag: settext
		//void setText(unordered_map<string, string>& data);

		//tag: print
		void printText(string& text);

		//tag: setname
		void setName(string text);
		//hide messagebox
		void hideMsgBox(ValueMap& data);

		//void regTextBox(TextBox* textbox, const string& objName, const string& type);

		void clearMessage();

		void reline();
		
		void move(string name, Point& to);
		TextBox* CurrentMainTextBox;
		TextBox* CurrentNameTextBox;
	private:
		TextBoxesManager();

		//the main textBoxes to print text
		//change by command [layer] 
		std::unordered_map<std::string, TextBox*> _textBoxes;



	};

}
#endif