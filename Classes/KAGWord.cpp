#include "KAGWord.h"
#if defined(TEST_KAGWORD) \
	|| defined(DEBUG_ALL)

KAGWord::KAGWord(Type type, const string& attribute, const string& value):
_type(type),
_name(attribute),
_value(value)
{
	_value = value;
}

#endif