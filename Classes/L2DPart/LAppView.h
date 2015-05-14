/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once


//Live2D framework
#include "L2DMatrix44.h"
#include "L2DViewMatrix.h"

#include "TouchManager.h"

#include "2d/CCSprite.h"
#include "cocos2d.h"

#include <vector>

class LAppView :public cocos2d::DrawNode
{    
public:
	LAppView();
	virtual ~LAppView(){}
	//virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
	
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
	
	void updateViewMatrix(float dx ,float dy ,float cx ,float cy ,float scale);
	float transformViewX(float deviceX);
	float transformViewY(float deviceY);
	float transformScreenX(float deviceX);
	float transformScreenY(float deviceY);
	
	static LAppView* createDrawNode();

private:
	TouchManager* touchMgr;
	live2d::framework::L2DMatrix44* deviceToScreen;
    live2d::framework::L2DViewMatrix* viewMatrix;
	
protected:
	cocos2d::CustomCommand _customCommand;
};
