/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppTextureDesc.h"
#include "cocos2d.h"

USING_NS_CC;
LAppTextureDesc::LAppTextureDesc(cocos2d::Texture2D* tex,std::string fileName)
{
	data=tex;
	textureFileName=fileName;
}

LAppTextureDesc::~LAppTextureDesc()
{
	Director::getInstance()->getTextureCache()->removeTextureForKey(textureFileName);

}
