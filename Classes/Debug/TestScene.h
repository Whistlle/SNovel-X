#pragma once

#include "TestMacro.h"
#include "SNovel.h"
#ifdef TEST_SCENE

#include "cocos2d.h"

namespace SNovel
{
	class TestScene : public cocos2d::Layer
	{
	public:
		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static cocos2d::Scene* createScene();

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();


		virtual void onEnter();
		// a selector callback
		//	void menuCloseCallback(cocos2d::Ref* pSender);
		//	void menuChangeCallback(cocos2d::Ref* pSender);

		// implement the "static node()" method manually
		CREATE_FUNC(TestScene);

	private:
		cocos2d::RefPtr<Chapter> _chapter;
		//SceneCtrl* _sceneCtrl;
	};
}
#endif
