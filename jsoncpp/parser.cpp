#include <cctype>
#include "Entry.h"
#include "parser.h"
namespace Json {
	bool Parser::parse(const string& s, Entry::Ptr res)
	{
		int p = 0;
		bool ok = _parse(s, p, res);
		while (p < s.size() && isspace(s[p])) p++;
		return ok && (p == s.size());
	}
	bool Parser::_parse(const string& s, int& p, Entry::Ptr res)
	{
		while (p < s.size() && isspace(s[p])) p++;
		if (p >= s.size()) {
			return false;
		}
		char c = s[p];
		if (c == 'n') {
			return _parseNull(s, p, res);
		}
		else if (isdigit(c) || c == '-') {
			return _parseNumber(s, p, res);
		}
		else if (c == 't' || c == 'f') {
			return _parseBool(s, p, res);
		}
		else if (c == '"') {
			return _parseStr(s, p, res);
		}
		else if (c == '[') {
			return _parseArray(s, p, res);
		}
		else if (c == '{') {
			return _parseObject(s, p, res);
		}
		else {
			return false;
		}
	}
	bool Parser::_parseNull(const string& s, int& p, Entry::Ptr res) {
		if (p + 3 < s.size() && s[p] == 'n' && s[p + 1] == 'u' && s[p + 2] == 'l' && s[p + 3] == 'l') {
			p += 4;
			res = Entry::_Null;
			return true;
		}
		return false;
	}
	bool Parser::_parseNumber(const string& s, int& p, Entry::Ptr res)
	{
		int flag = 1;
		if (s[p] == '-') {
			flag = -1;
			p++;
		}
		int num = 0, old_p = p;
		while (p < s.size() && isdigit(s[p])) {
			num = num * 10 + (s[p] - '0');
			p++;
		}
		if (old_p == p) return false;

		if (s[p] >= s.size()) {
			num *= flag;
			res = num;
			return true;
		}
		
		if (s[p] == '.') {
			double sig = 0, mask = 0.1;
			p++;
			while (p < s.size() && isdigit(s[p])) {
				sig += mask * (s[p] - '0');
				mask *= 0.1;
				p++;
			}
			res = flag * (sig + num);
			return true;
		}
		else {
			res = num;
			return true;
		}


	}
	bool Parser::_parseBool(const string& s, int& p, Entry::Ptr res)
	{
		if (p + 3 < s.size() && s[p] == 't' && s[p + 1] && s[p + 2] == 'u' && s[p + 3] == 'e') {
			p += 4;
			res = Entry::True;
			return true;
		}
		else if (p + 4 < s.size() && s[p] == 'f' && s[p + 1] == 'a' && s[p + 2] == 'l' && s[p + 3] == 's' && s[p + 4] == 'e') {
			p += 5;
			res = Entry::False;
			return true;
		}
		return false;
	}
	bool Parser::_parseStr(const string& s, int& p, Entry::Ptr res)
	{
		int r = s.find_first_of('"', p + 1);
		if (r != string::npos) {
			res = s.substr(p + 1, r - p - 1);
			p = r + 1;
			return true;
		}
		else {
			return false;
		}
	}
	bool Parser::_parseArray(const string& s, int& p, Entry::Ptr res)
	{
		p++;
		res = Entry::EmptyArray;
		Entry::Ptr item;
		while (p < s.size() && isspace(s[p])) p++;
		if (p < s.size() && s[p] == ']') {
			p++;
			return true;
		}
		while (p < s.size()) {
			if (_parse(s, p, item)) {
				res->arrProxy().push_back(item.clone());
			}
			else return false;

			while (p < s.size() && isspace(s[p])) p++;
			if (p >= s.size()) {
				return false;
			}
			else if (s[p] == ']') {
				p++;
				return true;
			}
			else if (s[p] == ',') {
				p++;
				while (p < s.size() && isspace(s[p])) p++;
			}
			else {
				return false;
			}
		}
		return false;
	}
	bool Parser::_parseObject(const string& s, int& p, Entry::Ptr res) {
		p++;
		res = Entry::EmptyObject;
		Entry::Ptr key, value;
		while (p < s.size() && isspace(s[p])) p++;
		if (p < s.size() && s[p] == '}') {
			p++;
			return true;
		}
		while (p < s.size()) {
			if (_parseStr(s, p, key)) {
				while (p < s.size() && isspace(s[p])) p++;
				if (p < s.size() && s[p] == ':') {
					p++;
					while (p < s.size() && isspace(s[p])) p++;
					if (_parse(s, p, value)) {
						res[key->getStr()] = value.clone();
						while (p < s.size() && isspace(s[p])) p++;
						if (p >= s.size()) return false;
						else if (s[p] == '}') {
							p++;
							return true;
						}
						else if (s[p] == ',') {
							p++;
							while (p < s.size() && isspace(s[p])) p++;
						}
						else {
							return false;
						}
					}
					else return false;
				}
				else return false;
			}
			else {
				return false;
			}
		}
		return false;
	}
}
