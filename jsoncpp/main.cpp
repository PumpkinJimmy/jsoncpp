#include <iostream>
#include "Entry.h"
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
	// e6["String"] = "New String Value";
	cout << e6["String"]->getStr() << endl;
	cout << e6 << endl;
	return 0;
}