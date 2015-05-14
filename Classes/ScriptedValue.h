#pragma once

#include "cocos2d.h"
USING_NS_CC;


class ScriptedValue
{
public:
	static const ScriptedValue Null;

	ScriptedValue();
	ScriptedValue(const char *valueName, std::vector<ScriptedValue>& params);
	//ScriptedValue(const char *valueName);
	explicit ScriptedValue(unsigned char v);
	explicit ScriptedValue(int v);
	explicit ScriptedValue(float v);
	explicit ScriptedValue(bool v);
	explicit ScriptedValue(const char*);
	explicit ScriptedValue(const std::string& v);
	
	explicit ScriptedValue(const ValueVector& v);
	explicit ScriptedValue(ValueVector&& v);

	explicit ScriptedValue(const ValueMap& v);
	explicit ScriptedValue(ValueMap&& v);

	explicit ScriptedValue(const ValueMapIntKey& v);
	explicit ScriptedValue(ValueMapIntKey&& v);

	explicit ScriptedValue(const Value& other);
//	explicit ScriptedValue(Value&& other);

	ScriptedValue(const ScriptedValue& other);
	ScriptedValue(ScriptedValue&& other);

	

	~ScriptedValue();



	// assignment operator
	ScriptedValue& operator= (const ScriptedValue& other);
	ScriptedValue& operator= (ScriptedValue&& other);
	ScriptedValue& operator= (const Value& other);
	ScriptedValue& operator= (Value&& other);
	ScriptedValue& operator= (unsigned char v);
	ScriptedValue& operator= (int v);
	ScriptedValue& operator= (float v);
	ScriptedValue& operator= (double v);
	ScriptedValue& operator= (bool v);
	ScriptedValue& operator= (const char* v);
	ScriptedValue& operator= (const std::string& v);

	ScriptedValue& operator= (const ValueVector& v);
	ScriptedValue& operator= (ValueVector&& v);

	ScriptedValue& operator= (const ValueMap& v);
	ScriptedValue& operator= (ValueMap&& v);

	ScriptedValue& operator= (const ValueMapIntKey& v);
	ScriptedValue& operator= (ValueMapIntKey&& v);

	//ScriptedValue& operator= (const Value& v);
	//ScriptedValue& operator= (Value&& v);

	// equal operator
	bool operator!= (const ScriptedValue& v);
	bool operator!= (const ScriptedValue& v) const;
	bool operator== (const ScriptedValue& v);
	bool operator== (const ScriptedValue& v) const;

	unsigned char asByte() const;
	int asInt() const;
	float asFloat() const;
	double asDouble() const;
	bool asBool() const;
	std::string asString() const;
	
	ValueVector& asValueVector();
	const ValueVector& asValueVector() const;

	ValueMap& asValueMap();
	const ValueMap& asValueMap() const;

	ValueMapIntKey& asIntKeyMap();
	const ValueMapIntKey& asIntKeyMap() const;

	inline bool isNull() const { return _type == Type::NONE; }

	enum class Type
	{
		NONE = 0,
		BYTE,
		INTEGER,
		FLOAT,
		DOUBLE,
		BOOLEAN,
		STRING,
		VECTOR,
		MAP,
		INT_KEY_MAP
	};

	inline Type getType() const { return _type; };

	std::string getDescription();

	const std::string& getName() { return _valueName; }

private:
	void clear();
	void reset(Type type);

	union
	{
		unsigned char byteVal;
		int intVal;
		float floatVal;
		double doubleVal;
		bool boolVal;

		std::string* strVal;
		ValueVector* vectorVal;
		ValueMap* mapVal;
		ValueMapIntKey* intKeyMapVal;
	}_field;

	Type _type;

	std::string _valueName;
};