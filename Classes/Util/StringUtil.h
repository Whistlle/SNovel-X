#include "Debug\TestMacro.h"
#if defined(TEST_STRING_UTIL) \

#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <cwctype>
#include <algorithm>

using namespace std;
/* 
 * StringUtil:
 * provide some func to operate string
 * e,g, split£¬trim£¬replace next word
 */
namespace SNovel
{
	class StringUtil
	{
	public:
		static const char BLANKS[];

		/*
		 * split the string
		 * @param const string& str  the string needed to split
		 * @param const string& word  the word, e.g. '\n' to split the str
		 * @param vector<string>& strs  return the splited str
		 */
		static void split(const string& str, const char word, vector<string>& strs);

		/*
		 * read string stop until read notes given
		 * @param note  the stop char
		 */
		static string nextStringStopUntil(const string& str, const char* note, int pos, int* npos);

		static  string nextStringStopUntil(const string& str, char note, int pos, int* npos)
		{
			return nextStringStopUntil(str, &note, pos, npos);
		}

		/*
		* read next string stop when read blanks
		* @param int pos current pos in str
		* @param int* npos pos after func
		*/
		static string nextString(const string& str, int pos, int* npos)
		{
			string s = nextStringStopUntil(str, BLANKS, pos, npos);
			return s;
		}



		static string nextString(const string& str, int pos = 0)
		{
			int npos;
			return nextString(str, pos, &npos);
		}

		//static int nextInt(string str);

		static string trim(string &s) {
			if (s.length() == 0) return s;
			size_t beg = s.find_first_not_of(" \a\b\f\n\r\t\v");
			size_t end = s.find_last_not_of(" \a\b\f\n\r\t\v");
			if (beg == string::npos) return "";
			return string(s, beg, end - beg + 1);
		}

		
		static string& tolower(string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), std::tolower);
		
			return str;
		}
		static wstring& towlower(wstring& wstr)
		{
			
			std::transform(wstr.begin(), wstr.end(), wstr.begin(), std::towlower);
			return wstr;
		}

		static string& toupper(string& wstr)
		{
			std::transform(wstr.begin(), wstr.end(), wstr.begin(), std::toupper);
			return wstr;
		}
		static wstring& towupper(wstring& wstr)
		{
			std::transform(wstr.begin(), wstr.end(), wstr.begin(), std::towupper);
			return wstr;
		}
	};
}
#endif