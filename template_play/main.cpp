#include <iostream>
#include <type_traits>
#include <typeinfo>
using namespace std;

void func1() {
	cout << "This is func1" << endl;
}

void func2(int i) {
	cout << "This is func2: int ver." << endl;
}

void func2(bool b) {
	cout << "This is func2: bool ver." << endl;
}
enum Type { Null, Number, Bool };

void func3(const int& x) {
	cout << "Func3 const& ver; " << typeid(x).name() << endl;
}

void func3(int&& x) {
	cout << "Func3 &&ver; " << typeid(x).name() << endl;
}

template <typename T>
enable_if_t<!is_array_v<remove_reference_t<T>>> func4(T data) {
	cout << typeid(T).name() << endl;
	cout << "This is <T> ver." << endl;
	auto p = new T(data);
	cout << typeid(p).name() << endl;
}

template <typename T>
enable_if_t<is_array_v<remove_reference_t<T>>> func4(T data) {
	cout << typeid(T).name() << endl;
	cout << "This is array ver." << endl;
	auto p = new T(data);
	cout << typeid(p).name() << endl;

}

template <typename T>
void func5(const T& data) {
	cout << typeid(T).name() << endl;
	cout << "This is array ver." << endl;
	cout << is_same_v<char[20], T> << endl;
	//auto p = new T(data);
	//cout << typeid(p).name() << endl;

}

template <typename T>
enable_if_t<is_class_v<T>> func6(const T& data) {
	cout << "This is const& ver." << endl;
	auto p = new T(data);
}

template <typename T>
enable_if_t<is_class_v<T>> func6(T&& data) {
	cout << "This is && ver." << endl;
	auto p = new T(std::move(data));
}

template <typename T>
enable_if_t<!is_class_v<T>> func6(T data) {
	cout << "This is general ver." << endl;
	auto p = new T(data);
}

template <typename T, size_t N>
void func6(T(&data)[N] ) {
	cout << "This is array ver." << endl;
	auto p = new T[N];
}

int main()
{
	cout << typeid("This is a C-style string").name() << endl;
	cout << typeid(func1).name() << endl;
	cout << typeid(&func1).name() << endl;
	cout << typeid(true).name() << endl;
	cout << endl << endl;
	auto lambda_func = []() {cout << "This is a lambda func" << endl; };
	cout << typeid(lambda_func).name() << endl;
	cout << typeid(Null).name() << endl;
	cout << typeid(nullptr).name() << endl;
	func2(10);
	func2(true);
	func3(10);
	int x = 20;
	func3(x);
	cout << is_array_v<char[23]> << ' ' << is_array_v<char const [23]> << ' ' << is_array_v<const char [23]> << endl;
	cout << typeid(decltype("This is C-style string")).name() << endl;
	cout << is_array_v<decltype("This is C-style string")>  << endl;
	cout << is_array_v<decltype(string("This is C-style string"))> << endl;
	
	cout << is_pointer_v<decltype("This is C-style string")> << endl;
	cout << is_class_v<decltype("This is C-style string")> << endl;
	cout << is_compound_v<decltype("This is C-style string")> << endl;
	cout << is_const_v<decltype("This is C-style string")> << endl;
	cout << is_object_v<decltype("This is C-style string")> << endl;
	cout << is_lvalue_reference_v<decltype("This is C-style string")> << endl;
	cout << is_rvalue_reference_v<decltype("This is C-style string")> << endl;
	using t1 = decltype("This is C-style string");
	cout << typeid(t1).name() << endl;
	using t2 = remove_reference_t<decltype("This is C-style string")>;
	cout << typeid(t2).name() << endl;
	using t3 = decay_t<decltype("This is C-style string")>;
	cout << typeid(t3).name() << endl;
	cout << endl << endl;

	func4(string("This is std::string"));
	func4("This is C string");
	
	func5(string("This is std::string"));
	func5("This is C string");

	cout << endl << endl;

	string s = "This is std::string";
	func6(string("This is std::string"));
	func6("This is C string");
	func6(3);
	func6(s);
	return 0;
}