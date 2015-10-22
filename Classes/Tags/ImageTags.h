#pragma once
#include "AbstractTag.h"
#include "TagFactory.h"
#include "ScriptEngine\ScriptEngine.h"
#include "Core\ImageManager.h"
#include "UI\ImageObject.h"

using cocos2d::Value;
using cocos2d::Point;

namespace SNovel
{
	/*
	* tag = image_new
	*
	* <desc>
	* 预创建新的图片
	*
	* <param>
	* @objname:    GameObject Name
	* @name:       File name
	* @path:       Relative Path To the "/Resources/"
	*
	* <sample>
	* [image_new name=sachi path=actor/]
	*/
	class Image_newTag : public AbstractTag
	{
	public:
		Image_newTag()
		{
			_defaultParams = decltype(_defaultParams){
				{ "name",		Value("")  },
				{ "path",		Value("")  },
				{ "x",			Value("0") },
				{ "y",			Value("0") },
				{ "scale",		Value("1") }
			};

			_vitalParams = {
				"name",
				"path"
			};
		}

		void excute() override
		{
			ImageInfo info = ImageInfo(Params);
			ImageObject* io = ImageManager::getInstance()->createNode<ImageObject>(info);
			AbstractTag::excute();
		}
	};
	extern TagRegitser<Image_newTag> _imagenewTag;

	/*
	 * tag = image_show
	 *
	 * <desc>
	 * 加入某个节点并显示图片
	 *
	 * <param>
	 * @name:       被替换的图片名称
	 * @pos:        图片的位置 提供几个预制的位置{center, top, buttom, left, right, custom},若有预制的位置则用下面的坐标
	 * @x:		    横坐标
	 * @y:          纵坐标
	 * @scale:      缩放
	 * @root:		加入的图层， {bg, actor, text}, bg在底部, 依次向上
	 * @zorder:     显示的图片名称
	 * @fade:       是否淡入
	 * @fadetime:   渐变时间
	 * 
	 * <sample>
	 * [image_show name=background x=222 y=111 fade=true]
	 */
	enum class PosEnum
	{
		Center,
		Top,
		Buttom,
		Left,
		Right,
		Custom
	};

	class Image_showTag : public AbstractTag
	{
	public:
		Image_showTag()
		{
			_defaultParams = decltype(_defaultParams){
				{ "name",	   Value("")    },
				{ "pos",	   Value("custom") },
				{ "x",		   Value(0)		},
				{ "y",		   Value(0)		},
				{ "scale",	   Value(1)		},
				{ "layer",     Value("")    },
				{ "zorder",    Value(0)     },
				{ "fadetime",  Value(0)     },
			};

			_vitalParams = {
				"name",
				"layer",
			};
		}

		void excute() override
		{
			AbstractTag::excute();
			string name = Params["name"].asString();
			auto io = ImageManager::getInstance()->getCreatedNode<ImageObject>(name);
			auto layer = Params["layer"].asString();

			if (layer == "bg")
			{
				ImageManager::getInstance()->addToBgLayer(io, Params["zorder"].asInt());
			}
			else if (layer == "actor")
			{
				ImageManager::getInstance()->addToActorLayer(io, Params["zorder"].asInt());
			}
			else if (layer == "text")
			{
				ImageManager::getInstance()->addToTextLayer(io, Params["zorder"].asInt());
			}

			//set possition
			if (Params["pos"].asString() != "custom")
			{
				Point pos = getPosFromEnum(Params["pos"].asString());
				io->setPosition(pos);
			}
			else
			{
				float x = Params["x"].asFloat();
				float y = Params["y"].asFloat();
				io->setPosition(Point(x, y));
			}
			
			float time = Params["fadetime"].asFloat();
			io->setOpacity(0);
			Engine->getStatus().EnableNextCommand = false;
			io->setOnAnimFinishCallback([this]()
			{
				this->onFinishAnimation();
			});
			io->fadeIn(time);
		}

		void after() override
		{

		}
	private:
		Point getPosFromEnum(string& posEnum)
		{
			auto winSize = Director::getInstance()->getWinSize();
			Point p;
			if (posEnum == "center")
				p = Point(winSize / 2);
			else if (posEnum == "top")
				p = Point(winSize.width / 2.0, winSize.height * 3.0 / 4);
			else if (posEnum == "buttom")
				p = Point(winSize.width / 2.0, winSize.height / 4);
			else if (posEnum == "left")
				p = Point(winSize.width / 4.0, winSize.height / 2);
			else if (posEnum == "right")
				p = Point(winSize.width * 3.0 / 4.0, winSize.height / 4);
			else
				p = Point::ZERO;
			return p; 
		}
		
	};
	extern TagRegitser<Image_showTag> _imageshowTag;
	/*
	 * tag = fadeout
	 *
	 * <desc>
	 * 淡出场景中的指定图片
	 *
	 * <param>
	 * @name:   图片名称
	 * @time:   渐变时间
	 *
	 * <sample>
	 * [fadeout name=background time=1]
	 */
	class FadeoutTag : public AbstractTag
	{
	public:
		FadeoutTag()
		{
			_defaultParams = decltype(_defaultParams){
				{ "name", Value("") },
				{ "time", Value(0) },
			};

			_vitalParams = {
				"name",
			};
		}

		void excute() override
		{
			AbstractTag::excute();
			auto name = Params["name"].asString();
			ImageObject* io = ImageManager::getInstance()->getCreatedNode<ImageObject>(name);
			Engine->getStatus().EnableNextCommand = false;
			io->setOnAnimFinishCallback([this]()
			{
				this->onFinishAnimation();
			});
			io->fadeOut(Params["time"].asFloat());
			
		}
	};
	extern TagRegitser<FadeoutTag> _fadeoutTag;
	/*
	 * tag = fadein
	 *
	 * <desc>
	 * 淡入场景中的指定图片
	 *
	 * <param>
	 * @name:   被替换的图片名称
	 * @time:   渐变时间
	 *
	 * <sample>
	 * [fadein name=background time=1]
	 */
	class FadeinTag : public AbstractTag
	{
	public:
		FadeinTag()
		{
			_defaultParams = decltype(_defaultParams){
				{ "name", Value("") },
				{ "time", Value(0) },
			};

			_vitalParams = {
				"name",
			};
		}

		void excute() override
		{
			AbstractTag::excute();
			auto name = Params["name"].asString();
			ImageObject* io = ImageManager::getInstance()->getCreatedNode<ImageObject>(name);
			Engine->getStatus().EnableNextCommand = false;
			io->setOnAnimFinishCallback([this]()
			{
				this->onFinishAnimation();
			});
			io->fadeOut(Params["time"].asFloat());

		}
	};
	extern TagRegitser<FadeinTag> _fadeinTag;

	/*
	 * tag = move
	 *
	 * <desc>
	 * 移动场景中的指定图片
	 *
	 * <param>
	 * @name:   被替换的图片名称
	 * @x:		目标x坐标	
	 * @y:		目标y坐标
	 * @time:	移动动画时间
	 *
	 * <sample>
	 * [Move name=background x=1 y=2]
	 */
	class MoveTag : public AbstractTag
	{
	public:
		MoveTag()
		{
			_defaultParams = decltype(_defaultParams){
				{ "name", Value("") },
				{ "x",    Value(0) },
				{ "y",    Value(0) },
				{ "time", Value(0) }
			};

			_vitalParams = {
				"name",
				"x",
				"y"
			};
		}

		void excute() override
		{
			AbstractTag::excute();
			auto name = Params["name"].asString();
			ImageObject* io = ImageManager::getInstance()->getCreatedNode<ImageObject>(name);
			auto to = Point(Params["x"].asFloat(), Params["y"].asFloat());
			io->setOnAnimFinishCallback([this]()
			{
				this->onFinishAnimation();
			});
			io->move(to, Params["time"].asFloat());

		}
	};
	extern TagRegitser<MoveTag> _moveTag;
	/*
	 * tag = image_remove
	 *
	 * <desc>
	 * 移除场景中的指定图片
	 *
	 * <param>
	 * @name:   被替换的图片名称	
	 *
	 * <sample>
	 * [fadein name=background]
	 */
	class RemoveTag : public AbstractTag
	{
	public:
		RemoveTag()
		{
			_defaultParams.insert(
				{ "name",  Value("") }
			);

			_vitalParams = {
				"name",
				"x",
				"y"
			};
		}

		void excute() override
		{
			AbstractTag::excute();
			auto name = Params["name"].asString();
			//ImageObject* io = ImageManager::getInstance()->getCreatedNode<ImageObject>(name);
			ImageManager::getInstance()->removeFromScene(name);

		}
	};
	extern TagRegitser<RemoveTag> _removeTag;
	/*
	 * tag = image_change
	 *
	 * <desc>
	 * 更换GameObject的图片
	 *
	 * <param>
	 * @from:       被替换的图片名称
	 * @to:         显示的图片名称
	 * @fade:       是否渐变显示
	 * @fadetime:   渐变时间
	 *
	 * <sample>
	 * [image_change from=background to=room_tall fade=true]
	 */

	/*
	class Image_changeTag : AbstractTag
	{ 
	public:
		Image_changeTag()
		{
			_defaultParams = {
				{ "from",	 Value("")},
				{ "to",    Value("") },
				{ "fade",    Value("false") },
				{ "fadetime",Value("0.5") }
			};
			_vitalParams = {
				"from",
				"to"
			};
		}

		void excute() override
		{
			string from = Params["name"].asString();
			string to = Params["to"].asString();
			//string path = Params["path"].asString() + Params["name"].asString();
			Engine->getStatus().EnableNextCommand = false;

			//ImageObject io = ImageManager.Instance.GetImageObjectInScene(objName);
			//ImageObject io = ImageManager.Instance.GetObjectInScene<ImageObject>(objName);
			ImageObject* fromIO = ImageManager::getInstance()->getCreatedNode<ImageObject>(from);
			ImageObject* toIO = ImageManager::getInstance()->getCreatedNode<ImageObject>(to);
			fromIO->fadeOut();
			if (Params["fade"].asBool() == true)
			{
				//等待动画结束函数回调继续执行
				Engine->getStatus().EnableNextCommand = false;
			}
			else
			{
				Engine->getStatus().EnableNextCommand = true;
			}
			io.ChangeImage(path,
						   float.Parse(Params["fadetime"]));

			base.Excute();

		}
		void after() override
		{
			//base.After();
		}
		void onFinishAnimation() override
		{
			if (Params["fade"] == "true")
			{
				Debug.Log("Finish Animation!");
				Engine.Status.EnableNextCommand = true;
				Engine.NextCommand();
			}
		}
	};
	TagRegitser<Image_changeTag> _imagechangeTag("image_change");
	*/

}