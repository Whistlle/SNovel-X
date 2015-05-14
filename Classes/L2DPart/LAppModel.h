/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include "cocos2d.h"


//Live2D Framework
#include "L2DBaseModel.h"
#include "L2DTargetPoint.h"
#include "L2DStandardID.h"

//Live2D Lib
#include "Live2DModelOpenGL.h"

//utils
#include "ModelSetting.h"


class LAppModel : public live2d::framework::L2DBaseModel
{
private:
    ModelSetting* modelSetting;
	const char* modelHomeDir;
	
public:
    LAppModel();
    virtual ~LAppModel(void);
	//Initialize
	void init(ModelSetting* setting);
	
	//Load
    void load(const char dir[],const char path[]);
	void preloadMotionGroup(const char name[]);
	void releaseMotionGroup(const char name[]);
	
	//Update
    void update();
    void draw();
	void draw(live2d::framework::L2DMatrix44& matrix);
	void setViewMatrix(float matrix[16]);
	
	
	//Animation
    int startMotion(const char group[],int no,int priority);
	int startRandomMotion(const char name[],int priority);
	void setExpression(const char name[]);
	void setRandomExpression();
    
	//Other
	virtual bool hitTest(const char pid[],float testX,float testY);
};



