/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppView.h"

//Live2D Application
#include "LAppLive2DManager.h"
#include "LAppDefine.h"


using namespace live2d;
using namespace live2d::framework;

USING_NS_CC;

LAppView::LAppView():Sprite()
{
	log("hello");
}

//bool LAppView::init()
//{
//    if ( !Sprite::init() )
//    {
//        return false;
//    }
//	
//    
//    auto listener = EventListenerTouchAllAtOnce::create();
//	
//    
//    listener->onTouchesBegan = CC_CALLBACK_2(LAppView::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(LAppView::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(LAppView::onTouchesEnded, this);
//   
//	
//    
//    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
//	
//    return true;
//}


void LAppView::onEnter()
{
	Sprite::onEnter();
	
	
	touchMgr=new TouchManager();
	
	
	deviceToScreen=new L2DMatrix44();
	
	
	viewMatrix=new L2DViewMatrix();

	Size size=Director::getInstance()->getWinSize();
	
	float width=size.width;
	float height=size.height;
	float ratio=(float)height/width;
	float left = VIEW_LOGICAL_LEFT;
	float right = VIEW_LOGICAL_RIGHT;
	float bottom = -ratio;
	float top = ratio;
	
	viewMatrix->setScreenRect(left,right,bottom,top);
	//viewMatrix->setScreenRect(left, right, 1, 1);
	
	float screenW=abs(left-right);
	//deviceToScreen->multTranslate(-width/2.0f,-height/2.0f );
	deviceToScreen->multTranslate(-width / 2.0f, -height / 2.0f);
	//deviceToScreen->multScale( screenW/width , -screenW/width );
	deviceToScreen->multScale(screenW / width, -screenW / width);
	
	viewMatrix->setMaxScale( VIEW_MAX_SCALE );
	viewMatrix->setMinScale( VIEW_MIN_SCALE );
	
	
	viewMatrix->setMaxScreenRect(
								 VIEW_LOGICAL_MAX_LEFT,
								 VIEW_LOGICAL_MAX_RIGHT,
								 VIEW_LOGICAL_MAX_BOTTOM,
								 VIEW_LOGICAL_MAX_TOP
								 );

	
    auto listener = EventListenerTouchAllAtOnce::create();
	
    
    listener->onTouchesBegan = CC_CALLBACK_2(LAppView::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(LAppView::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(LAppView::onTouchesEnded, this);
   
	
    
    this->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 100);
	
}


void LAppView::onExit()
{
	CCSprite::onExit();
	
	delete touchMgr;
	delete deviceToScreen;
	delete viewMatrix;
	
}


void LAppView::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	Sprite::draw(renderer, transform, flags);
	
	
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(LAppView::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}


void LAppView::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	kmGLPushMatrix();
    kmGLLoadMatrix(&transform);
	
	LAppLive2DManager* Live2DMgr=LAppLive2DManager::getInstance();
	Live2DMgr->onUpdate();
	
	
	kmGLPopMatrix();
}


void LAppView::onTouchesBegan(const std::vector<Touch*>& touches, Event *event) {
    
	size_t touchNum = touches.size() ;
		
	if( touchNum == 1 )
	{
		Point pt =  touches[0]->getLocationInView();
        if(LAppDefine::DEBUG_TOUCH_LOG)log( "touchesBegan x:%.0f y:%.0f",pt.x,pt.y);
        touchMgr->touchesBegan(pt.x,pt.y);
	}
}

void LAppView::onTouchesMoved(const std::vector<Touch*>& touches, Event *event) {
    
	size_t touchNum = touches.size() ;
	
	float screenX=this->transformScreenX(touchMgr->getX());
	float screenY=this->transformScreenY(touchMgr->getY());
	float viewX=this->transformViewX(touchMgr->getX());
	float viewY=this->transformViewY(touchMgr->getY());
	
	if( touchNum == 1 )
	{
		Point pt = touches[0]->getLocationInView();
		
		if(LAppDefine::DEBUG_TOUCH_LOG)log( "touchesMoved device{x:%.0f y:%.0f} screen{x:%.2f y:%.2f} view{x:%.2f y:%.2f}",pt.x,pt.y,screenX,screenY,viewX,viewY);
        touchMgr->touchesMoved(pt.x,pt.y);
	}
	LAppLive2DManager* live2DMgr=LAppLive2DManager::getInstance();
	live2DMgr->onDrag(viewX, viewY);
}

void LAppView::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event) {
    
    LAppLive2DManager* live2DMgr=LAppLive2DManager::getInstance();
	live2DMgr->onDrag(0, 0);
    
    if( touches.size() == 1 )
    {
        
        float x = deviceToScreen->transformX( touchMgr->getX() );
        float y = deviceToScreen->transformY( touchMgr->getY() );
        if (LAppDefine::DEBUG_LOG) log( "touchesEnded x:%.2f y:%.2f",x,y);
		live2DMgr->onTap(x,y);
    }
}


void LAppView::updateViewMatrix(float dx ,float dy ,float cx ,float cy ,float scale)
{
	LAppLive2DManager* live2DMgr=LAppLive2DManager::getInstance();
	
	
	viewMatrix->adjustScale(cx, cy, scale);
	
	
	viewMatrix->adjustTranslate(dx, dy) ;
	
	live2DMgr->setViewMatrix(viewMatrix);
}


float LAppView::transformViewX(float deviceX)
{
	float screenX = deviceToScreen->transformX( deviceX );
	return  viewMatrix->invertTransformX(screenX);
}


float LAppView::transformViewY(float deviceY)
{
	float screenY = deviceToScreen->transformY( deviceY );
	return  viewMatrix->invertTransformY(screenY);
}


float LAppView::transformScreenX(float deviceX)
{
	return  deviceToScreen->transformX( deviceX );
}


float LAppView::transformScreenY(float deviceY)
{
	return  deviceToScreen->transformY( deviceY );
}

