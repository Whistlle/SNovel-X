#include "TestMacro.h"

#if defined(TEST_TEXTBOXES_MANAGER) \
	|| defined(DEBUG_ALL)

#pragma once
#define TEST_TEXTBOXES_MANAGER

#include "TextBox.h"
#include <unordered_map>

enum class TextBoxType
{
	MAIN,
	OTHER
};

class TextBoxesManager
{
public:
	
	static TextBoxesManager* getInstance();
	void add(TextBox* textbox, const char* textBoxName, TextBoxType type);

	TextBox* getCurrentMainTextBox() { return _currentMainTextBox; }
	
	//change current main text box
	void onCurrent(EventCustom* pEventCustom);

private:
	TextBoxesManager();

	//textBoxs to print name, backlog and so on
	std::unordered_map<std::string, TextBox*> _otherTextBoxes;
	
	//the main textBoxes to print text
	//change by command [layer] 
	std::unordered_map<std::string, TextBox*> _mainTextBoxes;
	TextBox* _currentMainTextBox;

	//tag: settext
	void onSetText(EventCustom* pEvent);
	
	//tag: print
	void onPrintText(EventCustom* pEvent);

	//hide messagebox
	void onHideMsgBox(EventCustom* pEvent);
};


#endif