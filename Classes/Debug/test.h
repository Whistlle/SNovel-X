/*
#include "cocos2d.h"

#define PERSON_PROPERTY_LIST \
DeclProp(std::string, name) \
DeclProp(int, age) \
DeclProp(double, weight)

struct PropertyInfo
{
	//////////////////////////////////////////////////////////////////////////
	//类型枚举
	enum
	{
#define DeclProp(type, name) en##name,
		PERSON_PROPERTY_LIST
#undef DeclProp
		enCount,
	};

	//////////////////////////////////////////////////////////////////////////
	//变量定义
#define DeclProp(type, name) type name;
	PERSON_PROPERTY_LIST
#undef DeclProp

		//////////////////////////////////////////////////////////////////////////
		//GetType模板声明
		template<int propType>
	std::string GetType(void);
	//GetType模板定义
#define DeclProp(type, name) \
    template<>\
    std::string GetType<en##name>(void)\
	    {\
        return #type;\
	    }
	PERSON_PROPERTY_LIST
#undef DeclProp

		//////////////////////////////////////////////////////////////////////////
		//GetName模板声明
		template<int propType>
	std::string GetName(void);
	//GetName模板定义
#define DeclProp(type, name) \
    template<>\
    std::string GetName<en##name>(void)\
	    {\
        return #name;\
	    }
	PERSON_PROPERTY_LIST
#undef DeclProp

		//////////////////////////////////////////////////////////////////////////
		//GetValue模板声明
		template<int propType>
	std::string GetValue(void);
	//GetValue模板定义
#define DeclProp(type, name) \
    template<>\
    std::string GetValue<en##name>(void)\
	    {\
        std::stringstream stream;\
        stream << name;\
        return stream.str();\
	    }
	PERSON_PROPERTY_LIST
#undef DeclProp

		//////////////////////////////////////////////////////////////////////////
		//遍历用的辅助函数
		std::string GetInfoType(int typeEnum)
	{
		return GetInfo(typeEnum, 0);
	}
	std::string GetInfoName(int typeEnum)
	{
		return GetInfo(typeEnum, 1);
	}
	std::string GetInfoValue(int typeEnum)
	{
		return GetInfo(typeEnum, 2);
	}
	std::string GetInfo(int typeEnum, int getWhat)
	{
		switch (typeEnum)
		{
#define DeclProp(type, name) case en##name: \
					{ if (getWhat == 0) return GetType<en##name>(); \
			  if (getWhat == 1) return GetName<en##name>(); \
			  if (getWhat == 2) return GetValue<en##name>();}
			PERSON_PROPERTY_LIST
#undef DeclProp
default:
	return std::string();
		}
	}
};

int main()
{
	PropertyInfo info;
	info.age = 10;
	info.name = "something";
	info.weight = 20;
	for (int index = 0; index < PropertyInfo::enCount; ++index)
	{
	//	std::cout << info.GetInfoValue(index) << std::endl;
		CCLOG("%s", info.GetInfoValue(index));;
	}
	system("pause");
	return 0;
}*/