/**
 *
 *  You can modify and use this source freely
 *  only for the development of application related Live2D.
 *
 *  (c) Live2D Inc. All rights reserved.
 */
#pragma once

#include "L2DTextureDesc.h"
#include "cocos2d.h"

class LAppTextureDesc : public live2d::framework::L2DTextureDesc
{
public:
	LAppTextureDesc(cocos2d::Texture2D* tex);
	virtual ~LAppTextureDesc();

private:
	cocos2d::Texture2D* data;
};
