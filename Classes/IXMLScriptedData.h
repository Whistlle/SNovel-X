#ifdef TEST_IXML_SCRIPTED_DATA \
	|| DEBUG_ALL


#pragma once
#include <vector>
#include "ScriptedValue.h"

class IXMLScriptedData
{
	///////////////////////////////////////////
	//声明一个特性
#define DeclAttr(name) \
	ScriptedValue* name = new ScriptedValue(#name, attributes); 

	//声明一个属性
#define DeclProp(name) \
	IXMLScriptedData* name = new IXMLScriptedData(#name, params); \
	

    //声明一个自定义属性：继承自IXMLScriptedData
#define DeclCustomProp(name, type)\
	type* name = new type(#name, params);
	///////////////////////////////////////////
public:
	//IXMLScriptedData() {};
	IXMLScriptedData(const char *name);
	IXMLScriptedData(const char *valueName, std::vector<IXMLScriptedData*>& params);

	std::vector<ScriptedValue*> attributes;
	std::vector<IXMLScriptedData*> params;

	virtual void setAttribute(const char* name, const char* value);
	//virtual void setParam(const char* name, const char* value);
	virtual void setValue(const char* name, const char*  Value);
	virtual void setName(const char* Name) { _name = Name;  }

	bool hasChildElement();
	bool hasChildElement(const char* paramName);
	const std::string& getName() const { return _name; }
	const ScriptedValue& getValue() const { return _value; }

	virtual IXMLScriptedData* FirstChildElement();
	virtual IXMLScriptedData* NextSiblingElement();
	virtual IXMLScriptedData* getChildElement(const char* name);

protected:

	std::string _name;
	ScriptedValue _value;
	int _childCount;
};

#endif