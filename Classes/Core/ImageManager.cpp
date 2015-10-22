#include "ImageManager.h"

namespace SNovel
{
	static ImageManager* _sharedImageManager = nullptr;
	ImageManager* ImageManager::getInstance()
	{
		if (_sharedImageManager == nullptr)
		{
			_sharedImageManager = new ImageManager();
		}
		return _sharedImageManager;
	}

	void ImageManager::addToBgLayer(ImageObject* io, int z_order)
	{
		if (BgRoot)
		{
			BgRoot->addChild(io->getNode(), z_order);
			_objectInScene.insert({ io->getName(), io });
		}
		else
			CCLOG("set BgRoot first!");
	}

	void ImageManager::addToTextLayer(ImageObject* io, int z_order)
	{
		if (TextRoot)
		{
			TextRoot->addChild(io->getNode(), z_order);
			_objectInScene.insert({ io->getName(), io });
		}
		else
			CCLOG("set TextRoot first!");
	}

	void ImageManager::addToActorLayer(ImageObject* io, int z_order)
	{
		if (ActorRoot)
		{
			ActorRoot->addChild(io->getNode(), z_order);
			_objectInScene.insert({ io->getName(), io });
		}
		else
			CCLOG("set ActorRoot first!");
	}

	void ImageManager::removeFromScene(ImageObject* io)
	{
		io->getNode()->removeFromParent();
		_objectInScene.erase(io->getName());
	}
	void ImageManager::removeFromScene(string name)
	{
		if (_objectInScene.find(name) == _objectInScene.end())
		{
			char str[40];
			sprintf(str, "Node:%s is not in Scene, cnnnot remove");
			CCAssert(_objectInScene.find(name) == _objectInScene.end(),
					 str);
		}
		else
		{
			auto io = _objectInScene[name];
			removeFromScene(io);
		}
	}
}