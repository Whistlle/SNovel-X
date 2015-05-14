/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#include "LAppTextureDesc.h"


LAppTextureDesc::LAppTextureDesc(cocos2d::Texture2D* tex)
{
	data=tex;
}

LAppTextureDesc::~LAppTextureDesc()
{
	delete data;
}
