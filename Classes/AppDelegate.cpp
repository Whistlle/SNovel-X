/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "AppDelegate.h"
#include "TestScene.h"

#include "L2DPart\LAppLive2DManager.h"

using namespace live2d;

USING_NS_CC;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() 
{
	LAppLive2DManager* Live2DMgr=LAppLive2DManager::getInstance();
	Live2DMgr->releaseInstance();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("Galgame Demo");
		//glview->setFrameSize(960,640);
        director->setOpenGLView(glview);
    }
	
	glview->setDesignResolutionSize(750, 1134, ResolutionPolicy::SHOW_ALL);
    // turn on display FPS
    director->setDisplayStats(true);
	
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//set resource search path
	this->setResourcePath();

	//Live2D
	LAppLive2DManager* Live2DMgr=LAppLive2DManager::getInstance();
	
    // create a scene. it's an autorelease object
   // auto scene = SampleScene::createScene();
	
	//for engine test
	auto scene = TestScene::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::setResourcePath()
{
	std::vector<std::string> path;
	path.push_back("image");
	path.push_back("sounds");
	path.push_back("font");
	path.push_back("scripts");
	path.push_back("live2d");
	FileUtils::getInstance()->setSearchPaths(path);
}