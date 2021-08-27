#include "Entry.h"


std::ostream& Json::operator<<(std::ostream& out, const Json::Entry& etry)
{
	out << etry.stringfy();
	return out;
}



std::ostream& Json::operator<<(std::ostream& out, const EntryProxy etry)
{
	out << *etry;
	return out;
}

namespace Json {
	const Entry Entry::True(true, Entry::Bool);
	const Entry Entry::False(false, Entry::Bool);
	const Entry Entry::_Null;
	const Entry Entry::EmptyArray = Entry::arrType();
	const Entry Entry::EmptyObject = Entry::objType();

	string Entry::stringfy() const
	{
		std::stringstream out;
		switch (type) {
		case Json::Entry::Null:
			out << "null";
			break;
		case Json::Entry::Number:
			out << (isInt ? data.iNum : data.fNum);
			break;
		case Json::Entry::Bool:
			out << (data.bNum ? "true" : "false");
			break;
		case Json::Entry::Str:
			out << '"' << str << '"';
			break;
		case Json::Entry::Array:
			out << '[';
			if (!arr.empty()) {
				out << arr[0];
			}
			for (int i = 1; i < arr.size(); i++) {
				out << ',' << arr[i];
			}
			out << ']';
			break;
		case Json::Entry::Object:
			out << '{';
			if (!obj.empty()) {
				out << '"' << obj[0].first << '"'
					<< ": "
					<< obj[0].second;
			}
			for (int i = 1; i < obj.size(); i++) {
				out << ','
					<< '"' << obj[i].first << '"'
					<< ": "
					<< obj[i].second;
			}
			out << '}';
			break;
		default:
			out << "<error-type>";
		}
		return out.str();
	}

	string Entry::pretty_stringfy() const
	{
		std::stringstream out;
		switch (type) {
		case Json::Entry::Null:
			out << "null";
			break;
		case Json::Entry::Number:
			out << (isInt ? data.iNum : data.fNum);
			break;
		case Json::Entry::Bool:
			out << (data.bNum ? "true" : "false");
			break;
		case Json::Entry::Str:
			out << '"' << str << '"';
			break;
		case Json::Entry::Array:
			out << '[';
			if (!arr.empty()) {
				out << arr[0];
			}
			for (int i = 1; i < arr.size(); i++) {
				out << ',' << arr[i];
			}
			out << ']';
			break;
		case Json::Entry::Object:
			out << '{';
			if (!obj.empty()) {
				out << '"' << obj[0].first << '"'
					<< ": "
					<< obj[0].second;
			}
			for (int i = 1; i < obj.size(); i++) {
				out << ','
					<< '"' << obj[i].first << '"'
					<< ": "
					<< obj[i].second;
			}
			out << '}';
			break;
		default:
			out << "<error-type>";
		}
		return out.str();
	}

	EntryProxy& EntryProxy::operator[](int idx) {
		return (*this)->arr[idx];
	}

	EntryProxy EntryProxy::operator[](int idx) const {
		return (*this)->arr[idx];
	}

	EntryProxy EntryProxy::operator[](const string& key) const
	{
		return (*this)->get(key);
	}

	EntryProxy& EntryProxy::operator[](const string& key)
	{
		return (*this)->get(key);
	}
	EntryProxy& EntryProxy::operator=(const Entry& etry)
	{
		*(*this) = etry;
		return *this;
	}
	EntryProxy& EntryProxy::operator=(int i)
	{
		*(*this) = i;
		return *this;
	}
	EntryProxy& EntryProxy::operator=(double f)
	{
		*(*this) = f;
		return *this;
	}
	EntryProxy& EntryProxy::operator=(const string& s)
	{
		*(*this) = s;
		return *this;
	}
	EntryProxy& EntryProxy::operator=(string&& s)
	{
		*(*this) = std::move(s);
		return *this;
	}
}


