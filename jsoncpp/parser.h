#pragma once
#include <string>
#include "Entry.h"
namespace Json
{
	class Parser
	{
	public:
		Parser() = default;
		static bool parse(const string& s, Entry::Ptr res);
	private:
		static bool _parse(const string& s, int& p, Entry::Ptr res);
		static bool _parseNull(const string& s, int& p, Entry::Ptr res);
		static bool _parseNumber(const string& s, int& p, Entry::Ptr res);
		static bool _parseBool(const string& s, int& p, Entry::Ptr res);
		static bool _parseStr(const string& s, int& p, Entry::Ptr res);
		static bool _parseArray(const string& s, int& p, Entry::Ptr res);
		static bool _parseObject(const string& s, int& p, Entry::Ptr res);
	};
}
