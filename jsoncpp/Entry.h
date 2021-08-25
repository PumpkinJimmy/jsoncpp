#pragma once
/*
 * @brief JSON对象
 * 
 * 可能是以下六种中的一种：
 * null、布尔、数字、字符串、列表、对象
 * 类型是自省的
 */
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>

namespace Json {

using std::shared_ptr;
using std::string;
using std::vector;
using std::pair;
using std::make_shared;

class Entry;
class EntryProxy;

std::ostream& operator<<(std::ostream& out, const Entry& etry);
std::ostream& operator<<(std::ostream& out, const EntryProxy etry);

class Entry;

/*  experimental  */
class EntryProxy : public shared_ptr<Entry> {
public:
	EntryProxy() : shared_ptr() {}
	EntryProxy(const shared_ptr<Entry>& p) : shared_ptr<Entry>(p) {}
	/* Subscript Operation */
	EntryProxy& operator[](int idx);
	EntryProxy operator[](int idx) const;
	EntryProxy operator[](const string& key) const;
	EntryProxy& operator[](const string& key);
	EntryProxy& operator=(int i);
	EntryProxy& operator=(double f);
	EntryProxy& operator=(const string& s);
	EntryProxy& operator=(string&& s);
};

class Entry
{

public:
	enum Type { Null, Number, Bool, Str, Array, Object };
	typedef vector<EntryProxy> arrType;
	typedef vector<pair<string, EntryProxy>> objType;

	
	friend class EntryProxy;
	friend std::ostream& operator<<(std::ostream& out, const Entry& etry);
	typedef EntryProxy Ptr;
	typedef const EntryProxy ConstPtr;

	static const Entry True;
	static const Entry False;
	static const Entry _Null;
	/* Constructors */

	Entry() : type(Null), isInt(false) {
		data.iNum = 0;
	}

	Entry(const Entry& etry) = default;

	Entry(Entry&& etry) = default;

	Entry(int i) : type(Number), isInt(true) {
		data.iNum = i;
	}

	Entry& operator=(int i) {
		type = Number;
		isInt = true;
		data.iNum = i;
		str.clear();
		arr.clear();
		obj.clear();
		return *this;
	}

	Entry(double f) : type(Number), isInt(false) {
		data.fNum = f;
	}

	Entry& operator=(double f) {
		type = Number;
		isInt = false;
		data.fNum = f;
		str.clear();
		arr.clear();
		obj.clear();
		return *this;
	}

	Entry(bool b, Type t) {
		if (t == Bool) {
			type = Bool;
			data.bNum = b;
		}
		else if (t == Number) {
			type = Number;
			isInt = true;
			data.iNum = b;
		}
		else {
			throw "Construct with invalid type";
		}
	}

	Entry(const string& s): type(Str), str(s){}

	Entry& operator=(const string& s) {
		type = Str;
		str = s;
		arr.clear();
		obj.clear();
		return *this;
	}

	Entry(string&& s) : type(Str), str(s) {}

	Entry& operator=(string&& s) {
		type = Str;
		str = std::move(s);
		arr.clear();
		obj.clear();
		return *this;
	}

	Entry(const arrType& ar) : type(Array), arr(ar) {}

	Entry(const vector<Entry>& ar) : type(Array) {
		arr.resize(ar.size());
		for (int i = 0; i < ar.size(); i++) {
			arr[i] = std::make_shared<Entry>(ar[i]);
		}
	}

	Entry(const objType& o) : type(Object), obj(o){}

	Entry(const vector<pair<string, Entry>>& o): type(Object) {
		obj.resize(o.size());
		for (int i = 0; i < o.size(); i++) {
			obj[i] = make_pair(o[i].first, std::make_shared<Entry>(o[i].second));
		}
	}

	/* Getters */

	Type getType() const {
		return type;
	}
	
	int getInt() const {
		if (type != Number) {
			throw "Get with invalid type";
		}
		else {
			return isInt ? data.iNum : int(data.fNum);
		}
	}

	double getFloat() const {
		if (type != Number) {
			throw "Get with invalid type";
		}
		else {
			return isInt ? data.iNum : data.fNum;
		}
	}

	bool getBool() const {
		if (type != Bool) {
			throw "Get with invalid type";
		}
		else return data.bNum;
	}

	string getStr() const {
		if (type != Str) { throw "Get with invalid type"; }
		else return str;
	}

	arrType getArray() const {
		if (type != Array) { throw "Get with invalid type"; }
		else return arr;
	}

	objType getObj() const {
		if (type != Object) { throw "Get with invalid type"; }
		else return obj;
	}
	/* Array Methods */
	/* Apply delegation through ref */
	arrType& arrProxy() {
		if (type != Array) { throw "Access array proxy on non-array entry"; }
		return arr;
	}
	const arrType& arrProxy() const {
		if (type != Array) { throw "Access array proxy on non-array entry"; }
		return arr;
	}

	/* Object Methods */
	bool hasKey(const string& key) const {
		if (type != Object) { throw "Access key on non-object entry"; }
		for (const auto& p : obj) {
			if (p.first == key) {
				return true;
			}
		}
		return false;
	}
	Entry::Ptr& get(const string& key) {
		if (type != Object) { throw "Access key on non-object entry";}
		else {
			for (auto& p : obj) {
				if (p.first == key) {
					return p.second;
				}
			}
			obj.push_back(make_pair(key, make_shared<Entry>()));
			return obj.back().second;
		}
	}

	Entry::ConstPtr get(const string& key) const {
		if (type != Object) { throw "Access key on non-object entry"; }
		else {
			for (auto& p : obj) {
				if (p.first == key) {
					return p.second;
				}
			}
			return make_shared<Entry>();
		}
	}

	Entry::Ptr set(const string& key, Entry::ConstPtr nv) {
		if (type != Object) { throw "Access key on non-object entry"; }
		else {
			get(key) = nv;
			return make_shared<Entry>(*this);
		}
	}

	/* Subscript Operation */
	Entry::ConstPtr operator[](const string& key) const {
		return get(key);
	}

	Entry::Ptr& operator[](const string& key) {
		return get(key);
	}

	Entry::Ptr& operator[](int idx) {
		return arr[idx];
	}

	Entry::Ptr operator[](int idx) const {
		return arr[idx];
	}

	string stringfy() const ;
	string pretty_stringfy() const;
	


private:
	union {
		int iNum;
		double fNum;
		bool bNum;
	} data;
	string str;
	arrType arr;
	objType obj;
	Type type;
	bool isInt;
};


}

