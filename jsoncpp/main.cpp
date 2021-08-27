#include <iostream>
#include "Entry.h"
#include "any.h"
#include "parser.h"
using namespace std;
using Json::Entry;
int main()
{
	Entry
		e1(),
		e2(10),
		e2f(3.5),
		e3(true, Entry::Bool),
		e4("This is a test string"),
		e5({
			Entry(16.4),
			Entry(),
			Entry::False,
			Entry("Stella!")
			});
	Entry e6({
		{	"null", Entry()},
		{"Number", Entry(4.7) },
		{"Bool", Entry::False},
		{"String", Entry("The string")},
		{"Array", e5},
		});

	cout << e6["String"]->getStr() << endl;
	cout << e6["Array"]->arrProxy()[0]->getFloat() << endl;
	cout << e6["Array"][0]->getFloat() << endl;
	cout << e6["String"]->getStr() << endl;
	cout << e6 << endl;

	e6["String"] = "New String Value";
	cout << e6 << endl;


	Any any = 10;
	cout << any.get<int>() << endl;
	any = "Any: Integer to String";
	cout << any.get<char[]>() << endl;
	cout << any.get<string>() << endl;

	Entry::Ptr etry1;
	cout << Json::Parser::parse(
R"(
	{
	  "null": null,
	  "Number": -114514.1998,
	  "Bool": true,
	  "String": "parse from string",
	  "Array": [ 251, false, 996, "Fu Bao!" ]\
	}
)", 
		etry1) << endl;
	cout << etry1 << endl;
	return 0;
}