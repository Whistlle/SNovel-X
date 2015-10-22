#include "Debug\TestMacro.h"
#if defined(TEST_AVG_DIALOGBOX) \
	|| defined(DEBUG_ALL)

#define TEST_AVG_DIALOGBOX

#include "TextBox.h"
#include "TwoStateButton.h"


class AVGDialogBox : public TextBoxLayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(AVGDialogBox);

	void nextText();

	virtual void showTextBox();
	virtual void hideTextBox();

	virtual void onEnter() override;

	void hideBtnCallback();

	virtual void enterScene();
private:
	//Œƒ±æ”Î±≥æ∞Õº≤„À≥–Ú
	const short BK_Z_ORDER = 0;
	const short TEXT_Z_ORDER = 1;

	void loadAllText();

	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	void onTouchEnded(Touch* pTouch, Event* pEvent);

	//TextBoxLayerColor* _nameBox;
	HideButton* _hideBtn;

	void onNotifyTextBox(EventCustom* pEvent);

	
};

class NameTextBox : public TextBoxLayerColor
{
public:
	CREATE_FUNC(NameTextBox);
	virtual bool init();

};
#endif