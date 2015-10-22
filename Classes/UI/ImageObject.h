#pragma once

#include "cocos2d.h"
#include <string>
#include <functional>

using std::string;

using namespace cocos2d;

namespace SNovel
{
	class ImageInfo
	{
	public:
		string Name = "";
		string Path = "";
		bool   Show = false;
		bool   Fade = false;
		float  Fadetime = 0.0f;
		string Root = "";
		float  Scale = 1;
		Point Position = { 0, 0 };
		Point AnchorPos = { 0, 0 };

		ImageInfo(ValueMap& param);
	};

	class ImageObject
	{
	public:
		ImageObject(ImageInfo&);
		~ImageObject();
		Sprite* getNode() { return _image; }

		void fadeIn(float fadeTime);
		void fadeOut(float fadeTime);

		void move(Point& to, float duration);
		void setOpacity(GLubyte g) { _image->setOpacity(g); }
		
		void setPosition(const Point& pos);
		void setOnAnimFinishCallback(std::function<void()> f) { _onAnimationFinish = f; }
		 
		const string& getName() const { return _name; }
	private:
		std::function<void()> _onAnimationFinish;
		string _name;
		Sprite* _image;
		ImageInfo _info;
	};
}