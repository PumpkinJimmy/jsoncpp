#include "Entry.h"


std::ostream& Json::operator<<(std::ostream& out, const Json::Entry& etry)
{
	switch (etry.type) {
	case Json::Entry::Null:
		out << "null";
		break;
	case Json::Entry::Number:
		out << etry.isInt ? etry.data.iNum : etry.data.fNum;
		break;
	case Json::Entry::Bool:
		out << etry.data.bNum ? "true" : "false";
		break;
	case Json::Entry::Str:
		out << '"' << etry.str  << '"';
		break;
	case Json::Entry::Array:
		out << '[';
		if (!etry.arr.empty()) {
			out << etry.arr[0];
		}
		for (int i = 1; i < etry.arr.size(); i++) {
			out << ',' << etry.arr[i];
		}
		out << ']';
		break;
	case Json::Entry::Object:
		out << '{';
		if (!etry.obj.empty()) {
			out << '"' << etry.obj[0].first << '"'
				<< ": "
				<< etry.obj[0].second;
		}
		for (int i = 1; i < etry.obj.size(); i++) {
			out << ','
				<< '"' << etry.obj[i].first << '"'
				<< ": "
				<< etry.obj[i].second;
		}
		out << '}';
		break;
	default:
		out << "<error-type>";
	}
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
}


