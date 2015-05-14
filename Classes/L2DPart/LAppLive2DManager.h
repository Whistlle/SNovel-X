/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once
#include <vector>
#include "LAppDefine.h"
#include "L2DTargetPoint.h"
#include "L2DMatrix44.h"
#include "cocos2d.h"

class LAppModel;

class LAppLive2DManager{
private :
	std::vector<LAppModel*> models;
	//L2DTargetPoint* dragMgr;
	int sceneIndex;
	
	//MyLive2DAllocator	myAllocator ;
	live2d::framework::L2DMatrix44* viewMatrix;
	//SimplePlayer* voice;
public:
    static LAppLive2DManager* getInstance();
    static void releaseInstance();
    
	
	void onDrag(float x,float y);
	void onTap(float x,float y);
	void onUpdate();
	
//	void playVoice(int index);
	
	void setViewMatrix(live2d::framework::L2DMatrix44* m){viewMatrix=m;}
	void releaseModel();
    LAppModel* getModel(int no){ return models[no]; }
	LAppModel* getCurrentModel() { return models.at(0); }
    size_t getModelNum(){return models.size();}
	
	//Live2D Scene
	void changeScene(int index);
	void nextScene();
private:
    LAppLive2DManager() ;
    virtual ~LAppLive2DManager() ;
};
 