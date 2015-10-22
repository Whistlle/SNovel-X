#pragma once
#define IMAGE_MANAGER
#ifdef IMAGE_MANAGER

#include <string>
#include <unordered_map>

#include "base\CCValue.h"
#include "math\Vec2.h"

#include "UI\ImageObject.h"

using std::string;
using std::unordered_map;

using cocos2d::ValueMap;

namespace SNovel
{

	class AbstractNode;

	class ImageManager
	{
	public:
		static ImageManager* getInstance();

		template<typename TNode, typename TInfo>
		TNode* createNode(TInfo& info)
		{
			//bool isDerNode = std::is_base_of<AbstractNode, TNode>::value;
			//bool isDerInfo = std::is_base_of<ImageInfo, TInfo>::value;
			//CCASSERT((isDerNode) && (isDerInfo), "TNode isnot a derived class of AbsNode");

			TNode* tNode = new TNode(info);

			//_objectInScene[info.Name];
			_cachedObject[info.Name] = tNode;
			return tNode;
		}

		template<typename TNode>
		TNode* getCreatedNode(string name)
		{
			if (_cachedObject.find(name) != _cachedObject.end())
			{
				return dynamic_cast<TNode*>(_cachedObject[name]);
			}
			else
			{
				CCLOG("Object:%s hasn't add to the manager!", name);
			}
			return nullptr;
		}

		cocos2d::Node* BgRoot;
		cocos2d::Node* TextRoot;
		cocos2d::Node* ActorRoot;
		
		void addToBgLayer(ImageObject* io, int z_order = 0);
		void addToTextLayer(ImageObject* io, int z_order = 0);
		void addToActorLayer(ImageObject* io, int z_order = 0);

		void removeFromScene(ImageObject* io);
		void removeFromScene(string name);

		;
	private:
		ImageManager() {};
		unordered_map<string, ImageObject*> _objectInScene;
		unordered_map<string, ImageObject*> _cachedObject;
	};
}

#endif