#include "StringUtil.h"


#if    defined(TEST_STRING_UTIL) \
	|| defined(DEBUG_ALL)


namespace SNovel
{
	/* define constants */
	const char StringUtil::BLANKS[] = { ' ', '\n' };

	void StringUtil::split(const string& str, const char word, vector<string>& strs)
	{
		size_t last = 0;
		size_t index = str.find_first_of(word, last);
		while (index != string::npos)
		{
			strs.push_back(str.substr(last, index - last + 1));
			last = index + 1;
			index = str.find_first_of(word, last);
		}
		if (index - last > 0)
		{
			strs.push_back(str.substr(last, index - last));
		}
	}

	string StringUtil::nextStringStopUntil(const string& str, const char* note, int pos, int* npos)
	{
		int head = pos;
		auto tempN = string(note);
		//string tempStr;
		bool success = false;
		for (auto ch = str[pos]; pos < str.size(); ch = str[pos])
		{
			for (auto n : tempN)
			{
				if (n == ch)
				{
					success = true;
					break;
				}
			}
			if (success)
				break;
			//tempStr.push_back(ch);
			++pos;
		}
		*npos = pos;
		string s = str.substr(head, pos - head);
		return s;
	}
}
#endif