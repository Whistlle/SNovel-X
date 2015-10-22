#include "ScriptedValue.h"
#include <sstream>
#include <iomanip>

ScriptedValue::ScriptedValue(const char *valueName, std::vector<ScriptedValue>& params)
{
	ScriptedValue();
	params.push_back(*this);
	_valueName = valueName;
}


ScriptedValue::ScriptedValue() :_type(Type::NONE)
{
	memset(&_field, 0, sizeof(_field));
}

ScriptedValue::ScriptedValue(unsigned char v) : _type(Type::BYTE)
{
	_field.byteVal = v;
}

ScriptedValue::ScriptedValue(int v) : _type(Type::INTEGER)
{
	_field.intVal = v;
}

ScriptedValue::ScriptedValue(float v) : _type(Type::FLOAT)
{
	_field.floatVal = v;
}

ScriptedValue::ScriptedValue(bool v) : _type(Type::BOOLEAN)
{
	_field.boolVal = v;
}

ScriptedValue::ScriptedValue(const char* v) : _type(Type::STRING)
{
	_field.strVal = new std::string();
	if (v)
		*_field.strVal = v;
}

ScriptedValue::ScriptedValue(const std::string& v): _type(Type::STRING)
{
	_field.strVal = new std::string();
	*_field.strVal = v;
}

ScriptedValue::ScriptedValue(const ValueVector& v) : _type(Type::VECTOR)
{
	_field.vectorVal = new (std::nothrow) ValueVector();
	*_field.vectorVal = v;
}

ScriptedValue::ScriptedValue(ValueVector&& v) : _type(Type::VECTOR)
{
	_field.vectorVal = new (std::nothrow) ValueVector();
	*_field.vectorVal = std::move(v);
}

ScriptedValue::ScriptedValue(const ValueMap& v) : _type(Type::MAP)
{
	_field.mapVal = new (std::nothrow) ValueMap();
	*_field.mapVal = v;
}

ScriptedValue::ScriptedValue(ValueMap&& v) : _type(Type::MAP)
{
	_field.mapVal = new (std::nothrow) ValueMap();
	*_field.mapVal = std::move(v);
}

ScriptedValue::ScriptedValue(const ValueMapIntKey& v)
{
	_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
	*_field.intKeyMapVal = v;
}

ScriptedValue::ScriptedValue(ValueMapIntKey&& v)
{
	_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
	*_field.intKeyMapVal = std::move(v);
}

ScriptedValue::ScriptedValue(const Value& other)
{
	auto type = other.getType();

	switch (type) {
	case Value::Type::BYTE:
		_field.byteVal = other.asByte();
		_type = Type::BYTE;
		break;
	case Value::Type::INTEGER:
		_field.intVal = other.asInt();
		_type = Type::INTEGER;
		break;
	case Value::Type::FLOAT:
		_field.floatVal = other.asFloat();
		_type = Type::FLOAT;
		break;
	case Value::Type::DOUBLE:
		_field.doubleVal = other.asDouble();
		_type = Type::DOUBLE;
		break;
	case Value::Type::BOOLEAN:
		_field.boolVal = other.asBool();
		_type = Type::BOOLEAN;
		break;
	case Value::Type::STRING:
		if (_field.strVal == nullptr)
		{
			_field.strVal = new std::string();
		}
		*_field.strVal = other.asString();
		_type = Type::STRING;
		break;
	case Value::Type::VECTOR:
		if (_field.vectorVal == nullptr)
		{
			_field.vectorVal = new (std::nothrow) ValueVector();
		}
		*_field.vectorVal = other.asValueVector();
		_type = Type::VECTOR;
		break;
	case Value::Type::MAP:
		if (_field.mapVal == nullptr)
		{
			_field.mapVal = new (std::nothrow) ValueMap();
		}
		*_field.mapVal = other.asValueMap();
		_type = Type::MAP;
		break;
	case Value::Type::INT_KEY_MAP:
		if (_field.intKeyMapVal == nullptr)
		{
			_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
		}
		*_field.intKeyMapVal = other.asIntKeyMap();
		_type = Type::INT_KEY_MAP;
		break;
	default:
		break;
	}
}


ScriptedValue::ScriptedValue(const ScriptedValue& other) :_type(Type::NONE)
{
	*this = other;
}

ScriptedValue::ScriptedValue(ScriptedValue&& other) : _type(Type::NONE)
{
	*this = std::move(other);
}


ScriptedValue::~ScriptedValue()
{
	clear();
}


ScriptedValue& ScriptedValue::operator= (const ScriptedValue& other)
{
	if (this != &other) {
		reset(other._type);

		switch (other._type) {
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			if (_field.strVal == nullptr)
			{
				_field.strVal = new std::string();
			}
			*_field.strVal = *other._field.strVal;
			break;
		case Type::VECTOR:
			if (_field.vectorVal == nullptr)
			{
				_field.vectorVal = new (std::nothrow) ValueVector();
			}
			*_field.vectorVal = *other._field.vectorVal;
			break;
		case Type::MAP:
			if (_field.mapVal == nullptr)
			{
				_field.mapVal = new (std::nothrow) ValueMap();
			}
			*_field.mapVal = *other._field.mapVal;
			break;
		case Type::INT_KEY_MAP:
			if (_field.intKeyMapVal == nullptr)
			{
				_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
			}
			*_field.intKeyMapVal = *other._field.intKeyMapVal;
			break;
		default:
			break;
		}
	}
	return *this;
}

ScriptedValue& ScriptedValue::operator= (ScriptedValue&& other)
{
	if (this != &other)
	{
		clear();
		switch (other._type)
		{
		case Type::BYTE:
			_field.byteVal = other._field.byteVal;
			break;
		case Type::INTEGER:
			_field.intVal = other._field.intVal;
			break;
		case Type::FLOAT:
			_field.floatVal = other._field.floatVal;
			break;
		case Type::DOUBLE:
			_field.doubleVal = other._field.doubleVal;
			break;
		case Type::BOOLEAN:
			_field.boolVal = other._field.boolVal;
			break;
		case Type::STRING:
			_field.strVal = other._field.strVal;
			break;
		case Type::VECTOR:
			_field.vectorVal = other._field.vectorVal;
			break;
		case Type::MAP:
			_field.mapVal = other._field.mapVal;
			break;
		case Type::INT_KEY_MAP:
			_field.intKeyMapVal = other._field.intKeyMapVal;
			break;
		default:
			break;
		}
		_type = other._type;

		memset(&other._field, 0, sizeof(other._field));
		other._type = Type::NONE;
	}

	return *this;
}

ScriptedValue& ScriptedValue::operator= (unsigned char v)
{
	reset(Type::BYTE);
	_field.byteVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (int v)
{
	reset(Type::INTEGER);
	_field.intVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (float v)
{
	reset(Type::FLOAT);
	_field.floatVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (double v)
{
	reset(Type::DOUBLE);
	_field.doubleVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (bool v)
{
	reset(Type::BOOLEAN);
	_field.boolVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (const char* v)
{
	reset(Type::STRING);
	*_field.strVal = v ? v : "";
	return *this;
}

ScriptedValue& ScriptedValue::operator= (const std::string& v)
{
	reset(Type::STRING);
	*_field.strVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (const ValueVector& v)
{
	reset(Type::VECTOR);
	*_field.vectorVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (ValueVector&& v)
{
	reset(Type::VECTOR);
	*_field.vectorVal = std::move(v);
	return *this;
}

ScriptedValue& ScriptedValue::operator= (const ValueMap& v)
{
	reset(Type::MAP);
	*_field.mapVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (ValueMap&& v)
{
	reset(Type::MAP);
	*_field.mapVal = std::move(v);
	return *this;
}

ScriptedValue& ScriptedValue::operator= (const ValueMapIntKey& v)
{
	reset(Type::INT_KEY_MAP);
	*_field.intKeyMapVal = v;
	return *this;
}

ScriptedValue& ScriptedValue::operator= (ValueMapIntKey&& v)
{
	reset(Type::INT_KEY_MAP);
	*_field.intKeyMapVal = std::move(v);
	return *this;
}

bool ScriptedValue::operator!= (const ScriptedValue& v)
{
	return !(*this == v);
}
bool ScriptedValue::operator!= (const ScriptedValue& v) const
{
	return !(*this == v);
}

bool ScriptedValue::operator== (const ScriptedValue& v)
{
	const auto &t = *this;
	return t == v;
}
bool ScriptedValue::operator== (const ScriptedValue& v) const
{
	if (this == &v) return true;
	if (v._type != this->_type) return false;
	if (this->isNull()) return true;
	switch (_type)
	{
	case Type::BYTE:    return v._field.byteVal == this->_field.byteVal;
	case Type::INTEGER: return v._field.intVal == this->_field.intVal;
	case Type::BOOLEAN: return v._field.boolVal == this->_field.boolVal;
	case Type::STRING:  return *v._field.strVal == *this->_field.strVal;
	case Type::FLOAT:   return fabs(v._field.floatVal - this->_field.floatVal) <= FLT_EPSILON;
	case Type::DOUBLE:  return fabs(v._field.doubleVal - this->_field.doubleVal) <= FLT_EPSILON;
	case Type::VECTOR:
	{
		const auto &v1 = *(this->_field.vectorVal);
		const auto &v2 = *(v._field.vectorVal);
		const auto size = v1.size();
		if (size == v2.size())
		{
			for (size_t i = 0; i < size; i++)
			{
				if (v1[i] != v2[i]) return false;
			}
		}
		return true;
	}
	case Type::MAP:
	{
		const auto &map1 = *(this->_field.mapVal);
		const auto &map2 = *(v._field.mapVal);
		for (const auto &kvp : map1)
		{
			auto it = map2.find(kvp.first);
			if (it == map2.end() || it->second != kvp.second)
			{
				return false;
			}
		}
		return true;
	}
	case Type::INT_KEY_MAP:
	{
		const auto &map1 = *(this->_field.intKeyMapVal);
		const auto &map2 = *(v._field.intKeyMapVal);
		for (const auto &kvp : map1)
		{
			auto it = map2.find(kvp.first);
			if (it == map2.end() || it->second != kvp.second)
			{
				return false;
			}
		}
		return true;
	}
	default:
		break;
	};

	return false;
}

/// Convert value to a specified type
unsigned char ScriptedValue::asByte() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<unsigned char>(_field.intVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<unsigned char>(atoi(_field.strVal->c_str()));
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<unsigned char>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<unsigned char>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}

int ScriptedValue::asInt() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::INTEGER)
	{
		return _field.intVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal;
	}

	if (_type == Type::STRING)
	{
		return atoi(_field.strVal->c_str());
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<int>(_field.floatVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<int>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1 : 0;
	}

	return 0;
}

float ScriptedValue::asFloat() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::FLOAT)
	{
		return _field.floatVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<float>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		return utils::atof(_field.strVal->c_str());
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<float>(_field.intVal);
	}

	if (_type == Type::DOUBLE)
	{
		return static_cast<float>(_field.doubleVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0f : 0.0f;
	}

	return 0.0f;
}

double ScriptedValue::asDouble() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal;
	}

	if (_type == Type::BYTE)
	{
		return static_cast<double>(_field.byteVal);
	}

	if (_type == Type::STRING)
	{
		return static_cast<double>(utils::atof(_field.strVal->c_str()));
	}

	if (_type == Type::INTEGER)
	{
		return static_cast<double>(_field.intVal);
	}

	if (_type == Type::FLOAT)
	{
		return static_cast<double>(_field.floatVal);
	}

	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal ? 1.0 : 0.0;
	}

	return 0.0;
}

bool ScriptedValue::asBool() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");
	if (_type == Type::BOOLEAN)
	{
		return _field.boolVal;
	}

	if (_type == Type::BYTE)
	{
		return _field.byteVal == 0 ? false : true;
	}

	if (_type == Type::STRING)
	{
		return (*_field.strVal == "0" || *_field.strVal == "false") ? false : true;
	}

	if (_type == Type::INTEGER)
	{
		return _field.intVal == 0 ? false : true;
	}

	if (_type == Type::FLOAT)
	{
		return _field.floatVal == 0.0f ? false : true;
	}

	if (_type == Type::DOUBLE)
	{
		return _field.doubleVal == 0.0 ? false : true;
	}

	return false;
}

std::string ScriptedValue::asString() const
{
	CCASSERT(_type != Type::VECTOR && _type != Type::MAP && _type != Type::INT_KEY_MAP, "Only base type (bool, string, float, double, int) could be converted");

	if (_type == Type::STRING)
	{
		return *_field.strVal;
	}

	std::stringstream ret;

	switch (_type)
	{
	case Type::BYTE:
		ret << _field.byteVal;
		break;
	case Type::INTEGER:
		ret << _field.intVal;
		break;
	case Type::FLOAT:
		ret << std::fixed << std::setprecision(7) << _field.floatVal;
		break;
	case Type::DOUBLE:
		ret << std::fixed << std::setprecision(16) << _field.doubleVal;
		break;
	case Type::BOOLEAN:
		ret << (_field.boolVal ? "true" : "false");
		break;
	default:
		break;
	}
	return ret.str();
}

ValueVector& ScriptedValue::asValueVector()
{
	CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
	return *_field.vectorVal;
}

const ValueVector& ScriptedValue::asValueVector() const
{
	CCASSERT(_type == Type::VECTOR, "The value type isn't Type::VECTOR");
	return *_field.vectorVal;
}

ValueMap& ScriptedValue::asValueMap()
{
	CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
	return *_field.mapVal;
}

const ValueMap& ScriptedValue::asValueMap() const
{
	CCASSERT(_type == Type::MAP, "The value type isn't Type::MAP");
	return *_field.mapVal;
}

ValueMapIntKey& ScriptedValue::asIntKeyMap()
{
	CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
	return *_field.intKeyMapVal;
}

const ValueMapIntKey& ScriptedValue::asIntKeyMap() const
{
	CCASSERT(_type == Type::INT_KEY_MAP, "The value type isn't Type::INT_KEY_MAP");
	return *_field.intKeyMapVal;
}

static std::string getTabs(int depth)
{
	std::string tabWidth;

	for (int i = 0; i < depth; ++i)
	{
		tabWidth += "\t";
	}

	return tabWidth;
}

static std::string visit(const ScriptedValue& v, int depth);
static std::string visitVector(const ValueVector& v, int depth)
{
	std::stringstream ret;

	if (depth > 0)
		ret << "\n";

	ret << getTabs(depth) << "[\n";

	int i = 0;
	for (const auto& child : v)
	{
		ret << getTabs(depth + 1) << i << ": " << visit(ScriptedValue(child), depth + 1);
		++i;
	}

	ret << getTabs(depth) << "]\n";

	return ret.str();
}

template <class T>
static std::string visitMap(const T& v, int depth)
{
	std::stringstream ret;

	if (depth > 0)
		ret << "\n";

	ret << getTabs(depth) << "{\n";

	for (auto iter = v.begin(); iter != v.end(); ++iter)
	{
		ret << getTabs(depth + 1) << iter->first << ": ";
		ret << visit(ScriptedValue(iter->second), depth + 1);
	}

	ret << getTabs(depth) << "}\n";

	return ret.str();
}

static std::string visit(const ScriptedValue& v, int depth)
{
	std::stringstream ret;

	switch (v.getType())
	{
	case ScriptedValue::Type::NONE:
	case ScriptedValue::Type::BYTE:
	case ScriptedValue::Type::INTEGER:
	case ScriptedValue::Type::FLOAT:
	case ScriptedValue::Type::DOUBLE:
	case ScriptedValue::Type::BOOLEAN:
	case ScriptedValue::Type::STRING:
		ret << v.asString() << "\n";
		break;
	case ScriptedValue::Type::VECTOR:
		ret << visitVector(v.asValueVector(), depth);
		break;
	case ScriptedValue::Type::MAP:
		ret << visitMap(v.asValueMap(), depth);
		break;
	case ScriptedValue::Type::INT_KEY_MAP:
		ret << visitMap(v.asIntKeyMap(), depth);
		break;
	default:
		CCASSERT(false, "Invalid type!");
		break;
	}

	return ret.str();
}

std::string ScriptedValue::getDescription()
{
	std::string ret("\n");
	ret += visit(*this, 0);
	return ret;
}

void ScriptedValue::clear()
{
	// Free memory the old value allocated
	switch (_type)
	{
	case Type::BYTE:
		_field.byteVal = 0;
		break;
	case Type::INTEGER:
		_field.intVal = 0;
		break;
	case Type::FLOAT:
		_field.floatVal = 0.0f;
		break;
	case Type::DOUBLE:
		_field.doubleVal = 0.0;
		break;
	case Type::BOOLEAN:
		_field.boolVal = false;
		break;
	case Type::STRING:
		CC_SAFE_DELETE(_field.strVal);
		break;
	case Type::VECTOR:
		CC_SAFE_DELETE(_field.vectorVal);
		break;
	case Type::MAP:
		CC_SAFE_DELETE(_field.mapVal);
		break;
	case Type::INT_KEY_MAP:
		CC_SAFE_DELETE(_field.intKeyMapVal);
		break;
	default:
		break;
	}

	_type = Type::NONE;
}

void ScriptedValue::reset(Type type)
{
	if (_type == type)
		return;

	clear();

	// Allocate memory for the new value
	switch (type)
	{
	case Type::STRING:
		_field.strVal = new std::string();
		break;
	case Type::VECTOR:
		_field.vectorVal = new (std::nothrow) ValueVector();
		break;
	case Type::MAP:
		_field.mapVal = new (std::nothrow) ValueMap();
		break;
	case Type::INT_KEY_MAP:
		_field.intKeyMapVal = new (std::nothrow) ValueMapIntKey();
		break;
	default:
		break;
	}

	_type = type;
}