#ifdef TEST_IXML_SCRIPTED_DATA \
	|| DEBUG_ALL

#include "IXMLScriptedData.h"

IXMLScriptedData::IXMLScriptedData(const char *valueName, std::vector<IXMLScriptedData*>& params)
{
	_name = valueName;
	params.push_back(this);
}

IXMLScriptedData::IXMLScriptedData(const char *valueName)
{
	_name = valueName;
}


void IXMLScriptedData::setAttribute(const char* name, const char* value)
{
	for (auto attr : attributes)
	{
		if (attr->getName().compare(name) == 0){
			CCLOG("[setAttribute] %s = %s", name, value);
			*attr = value;
		}
	}
}

/*
void IXMLScriptedData::setParam(const char* name, const char* value)
{
	for (auto param : params)
	{
		if (param->getName().compare(name) == 0){
			CCLOG("[setParam] %s = %s", name, value);
			param->setValue(name, value);
		}
	}
}*/

void IXMLScriptedData::setValue(const char* name, const char* Value)
{
	for (auto param : params)
	{
		if (param->getName().compare(name) == 0)
		{
			CCLOG("[setValue] %s = %s", name, Value);
			param->_value = Value;
			return;
		}
	}
	CCLOG("set Value wrong! cannot find param name: %s", name);
}


IXMLScriptedData* IXMLScriptedData::FirstChildElement()
{
	_childCount = 0;
	IXMLScriptedData* data = nullptr;
	try{
		data = params.at(_childCount++);
	}
	catch (const std::out_of_range& oor){
		return nullptr;
	}
	return data;
}

IXMLScriptedData* IXMLScriptedData::NextSiblingElement()
{
	IXMLScriptedData* data = nullptr;
	try{
		data = params.at(_childCount++);
	}
	catch (const std::out_of_range& oor){
		return nullptr;
	}
	return data;
}

bool IXMLScriptedData::hasChildElement()
{
	return !params.empty();
}

bool IXMLScriptedData::hasChildElement(const char* paramName)
{
	if (params.empty())
		return false;
	else
	{
		//似乎遍历的话效率不高
		for (auto param : params)
		{
			if (param->getName().compare(paramName) == 0)
			{
				if(!param->params.empty())
					return true;
			}
		}
	}
	return false;

}


IXMLScriptedData* IXMLScriptedData::getChildElement(const char* name)
{
	for (auto param : params)
	{
		if (param->getName().compare(name) == 0)
		{
			return param;
		}
	}
	CCLOG("can not find child element: %s", name);
	return nullptr;
}

#endif