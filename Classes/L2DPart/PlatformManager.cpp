/**
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "PlatformManager.h"
#include "cocos2d.h"

#include "Live2DModelOpenGL.h"
#include "util/UtDebug.h"

using namespace live2d;
using namespace live2d::framework;
USING_NS_CC;

PlatformManager::PlatformManager(void)
{
}


PlatformManager::~PlatformManager(void)
{
}


unsigned char* PlatformManager::loadBytes(const char* path,size_t* size)
{
	unsigned char* buf = CCFileUtils::getInstance()->getFileData(path,"rb", (ssize_t*)size);
	return buf;
}

void PlatformManager::releaseBytes(void* data)
{
	free(data);
//	delete[] (unsigned char*)data;
}

ALive2DModel* PlatformManager::loadLive2DModel(const char* path)
{
	size_t size;
	unsigned char* buf = loadBytes(path,&size);
	
	//Create Live2D Model Instance
	ALive2DModel* live2DModel = Live2DModelOpenGL::loadModel(buf,(int)size);
	this->releaseBytes(buf);
    return live2DModel;
}

L2DTextureDesc* PlatformManager::loadTexture(live2d::ALive2DModel* model, int no, const char* path)
{
	auto texture =Director::getInstance()->getTextureCache()->addImage(std::string(path));

	int glTexNo = texture->getName() ;
	texture->generateMipmap();
	const Texture2D::TexParams texParams = { GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE };
	
	texture->setTexParameters(texParams);
	texture->generateMipmap();

	((Live2DModelOpenGL*)model)->setTexture( no , glTexNo ) ;

	auto textureDesc=new LAppTextureDesc(texture,std::string(path));

	return textureDesc;
}

void PlatformManager::log(const char* txt)
{
	UtDebug::print(txt);
}
