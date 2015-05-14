/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppLive2DManager.h"


//Live2D Application
#include "LAppModel.h"
#include "PlatformManager.h"

#include "L2DStandardID.h"
#include "Live2DFramework.h"

#include "graphics/DrawProfileCocos2D.h"

#ifdef L2D_TARGET_ANDROID_ES2
	
	#include "graphics/DrawParam_OpenGLES2.h"
#endif

USING_NS_CC;

using namespace live2d;
using namespace live2d::framework;

static LAppLive2DManager* instance=NULL;



LAppLive2DManager* LAppLive2DManager::getInstance()
{

	if (instance==NULL)
	{
		instance=new LAppLive2DManager();
	}
	
	return instance;
}


void LAppLive2DManager::releaseInstance()
{
	if (instance)
	{
		delete instance;
		auto framework=live2d::framework::Live2DFramework::getPlatformManager();
		delete framework;
	}

	instance=NULL;
}


LAppLive2DManager::LAppLive2DManager()
:sceneIndex(0)
{
	
	if (LAppDefine::DEBUG_LOG) {
		log( "==============================================" ) ;
		log( "   Live2D SDK Sample App1") ;
		log( "==============================================" ) ;
	}
	
	
	
	
	
	//UtDebug::addMemoryDebugFlags( live2d::UtDebug::MEMORY_DEBUG_MEMORY_INFO_COUNT ) ;
	
	// Initialize Live2D
	//Live2D::init( &myAllocator );
	Live2D::init();

	#ifdef L2D_TARGET_ANDROID_ES2
	    char *exts = (char*)glGetString(GL_EXTENSIONS);
	    if(strstr(exts, "GL_NV_shader_framebuffer_fetch ")){
	        live2d::DrawParam_OpenGLES2::setExtShaderMode( true , true );
	    }
	#endif

	Live2DFramework::setPlatformManager(new PlatformManager());

//	dragMgr=new L2DTargetPoint();
	changeScene(SCENE_INDEX_HARU);
	
	//voice=new SimplePlayer();
	//voice->OnInitialize();
	viewMatrix=NULL;
}


LAppLive2DManager::~LAppLive2DManager()
{
	releaseModel();
	Live2D::dispose();
	
}


void LAppLive2DManager::releaseModel()
{
	for (int i=0; i<models.size(); i++)
	{
		delete models[i];
	}
    models.clear();
}


void LAppLive2DManager::onDrag(float x, float y)
{
	for (int i=0; i<models.size(); i++)
	{
		LAppModel* model = getModel(i);
		
		model->setDrag(x,y);
		
	}
}


void LAppLive2DManager::onTap(float x,float y)
{
    if(LAppDefine::DEBUG_LOG)log( "tapEvent");
	
	
	for (int i=0; i<models.size(); i++)
	{
		if(models[i]->hitTest(  HIT_AREA_NAME_HEAD,x, y ))
		{
			if(LAppDefine::DEBUG_LOG)log( "face");
			models[i]->setRandomExpression();
		}
		else if(models[i]->hitTest( HIT_AREA_NAME_BODY,x, y))
		{
			if(LAppDefine::DEBUG_LOG)log( "body");
			models[i]->startRandomMotion(MOTION_GROUP_TAP_BODY, PRIORITY_NORMAL );
		}
	}
}


void LAppLive2DManager::onUpdate()
{
	
	//live2d::DrawProfileCocos2D::preDraw() ;
	//live2d::DrawProfileCocos2D::postDraw() ;
	
	
	live2d::DrawProfileCocos2D::preDraw();

	L2DMatrix44 projection;
	Director* director=Director::getInstance();
	Size window=director->getWinSize();
	projection.scale(1, window.width/window.height);
	
	if (viewMatrix!=NULL) {
		projection.append(viewMatrix);
	}
	
	
	for (int i=0; i<models.size(); i++)
	{
		LAppModel* model = getModel(i);
		
		
		model->update();
		model->draw(projection);
	}
	
	live2d::DrawProfileCocos2D::postDraw() ;
}


void LAppLive2DManager::nextScene()
{
	int no = (sceneIndex+1) % 4;
	changeScene(no);
}


void LAppLive2DManager::changeScene(int index)
{
	sceneIndex=index;
	if(LAppDefine::DEBUG_LOG)log("model index : %d",sceneIndex );
	switch (sceneIndex)
	{
		case SCENE_INDEX_HARU:
			releaseModel();
			models.push_back(new LAppModel());
			models[0]->load(MODEL_HARU_DIR, MODEL_HARU) ;
			break;
		case SCENE_INDEX_SHIZUKU:
			releaseModel();
			models.push_back(new LAppModel());
			models[0]->load(MODEL_SHIZUKU_DIR, MODEL_SHIZUKU) ;
			break;
		case SCENE_INDEX_WANKO:
			releaseModel();
			models.push_back(new LAppModel());
			models[0]->load(MODEL_WANKO_DIR, MODEL_WANKO) ;
			break;
		case SCENE_INDEX_MULTI_MODEL:
			releaseModel();
			models.push_back(new LAppModel());
			models[0]->load(MODEL_HARU_DIR, MODEL_HARU_A) ;
			
			models.push_back(new LAppModel());
			models[1]->load(MODEL_HARU_DIR, MODEL_HARU_B) ;
			break;
		default:		
			break;
	}
	
	
}